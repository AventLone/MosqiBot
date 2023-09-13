#include "nodes.h"

namespace MosqiBot
{
RosClient::RosClient(std::string name) : Node(name), taskflag(false)
{
    RCLCPP_INFO(this->get_logger(), "Node has been activated: %s.", name.c_str());

    client_mega = this->create_client<my_interface::srv::MegaMsg>("mega_server");

    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image_raw", 10, std::bind(&RosClient::callback_subsription, this, std::placeholders::_1));

    projector = std::make_unique<Projector>(
        "/home/avent/Public/MyProjects/MosqiBot/ROS2-QT/src/camera_client/param/camera_info.yaml", tvec, depth);

    /*** Waiting until server is online ***/
    while (!client_mega->wait_for_service(std::chrono::milliseconds(100)))
    {
        if (!rclcpp::ok())
        {
            RCLCPP_ERROR(this->get_logger(), "The waiting for service was interrupted!");
            break;
        }
        RCLCPP_INFO(this->get_logger(), "Waiting for the server to go online...");
        rclcpp::sleep_for(std::chrono::milliseconds(100));
    }
}

void RosClient::send_request(const cv::Point2f& point)
{
    /*** Construct a request ***/
    req_mega->command = static_cast<uint8_t>(command::Mega::XY);
    req_mega->point_xy = {point.x, point.y};

    /***
     *  Send an asynchronous request, wait for the response,
     *  and call a callback function upon receiving the response
     */
    client_mega->async_send_request(req_mega, std::bind(&RosClient::callback_client_mega, this, std::placeholders::_1));
}

void RosClient::send_request(command::Mega command)
{
    req_mega->command = static_cast<uint8_t>(command);
    req_mega->point_xy = {0.0f, 0.0f};
    client_mega->async_send_request(req_mega, std::bind(&RosClient::callback_client_mega, this, std::placeholders::_1));
}

void RosClient::send_request(uint8_t vib_motor_index)
{
    req_mega->command = static_cast<uint8_t>(command::Mega::VIB);
    req_mega->point_xy = {static_cast<float>(vib_motor_index), 0.0f};
    client_mega->async_send_request(req_mega, std::bind(&RosClient::callback_client_mega, this, std::placeholders::_1));
}

void RosClient::callback_client_mega(rclcpp::Client<my_interface::srv::MegaMsg>::SharedFuture result)
{
    auto response = result.get();
    if (!response)
    {
        RCLCPP_ERROR(this->get_logger(), "Task failed!");
    }
    taskflag = true;
}

void RosClient::callback_subsription(const sensor_msgs::msg::Image::ConstSharedPtr msg)
{

    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        // cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    /***
     *  Make sure this image is protected
     *  using thread-safe techniques by mutex
     */
    {
        std::unique_lock<std::mutex> lock(mtx);
        this->img = cv_ptr->image;
    }
}
}   // namespace MosqiBot
