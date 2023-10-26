#include "nodes.h"
#include <ament_index_cpp/get_package_share_directory.hpp>

namespace MosqiBot
{
RosClient::RosClient(std::string name) : Node(name), taskflag(false)
{
    RCLCPP_INFO(this->get_logger(), "Node has been activated: %s.", name.c_str());

    mMegaClient = this->create_client<mosqibot_srv_interface::srv::MegaMsg>("mega_server");

    mCameraSub = this->create_subscription<sensor_msgs::msg::Image>(
        "image_raw",
        rclcpp::SensorDataQoS().reliable(),
        std::bind(&RosClient::cameraSubCallback, this, std::placeholders::_1));

    mTargetImgPub = this->create_publisher<sensor_msgs::msg::Image>("MosqiBot/target_img", 10);
    mHeapImgPub = this->create_publisher<sensor_msgs::msg::Image>("MosqiBot/heap_img", 10);

    std::string this_pkg_path = ament_index_cpp::get_package_share_directory("mosqibot_system");
    mProjector = std::make_unique<avent::Projecting>(this_pkg_path + "/config/settings/config.yaml");

    /*** Waiting until server is online ***/
    if (!mMegaClient->wait_for_service(std::chrono::milliseconds(160)))
    {
        RCLCPP_WARN(this->get_logger(), "Waiting for the server to go online...");
    }
    for (int i = 0; i < 10; ++i)
    {
        if (mMegaClient->wait_for_service(std::chrono::milliseconds(160))) break;
    }
    if (!mMegaClient->wait_for_service(std::chrono::milliseconds(160)))
    {
        RCLCPP_FATAL(this->get_logger(), "You need to connect to the embedded computer!");
        std::exit(EXIT_FAILURE);
    }
    // while (!mMegaClient->wait_for_service(std::chrono::milliseconds(100)))
    // {
    //     if (!rclcpp::ok())
    //     {
    //         RCLCPP_ERROR(this->get_logger(), "The waiting for service was interrupted!");
    //         break;
    //     }
    //     RCLCPP_WARN(this->get_logger(), "Waiting for the server to go online...");
    //     rclcpp::sleep_for(std::chrono::milliseconds(100));
    // }
}

void RosClient::send_request(const cv::Point2f& point)
{
    /*** Construct a request ***/
    mReqMega->command = static_cast<uint8_t>(command::Mega::XY);
    mReqMega->point_xy = {point.x, point.y};

    /***
     *  Send an asynchronous request, wait for the response,
     *  and call a callback function upon receiving the response
     */
    mMegaClient->async_send_request(mReqMega, std::bind(&RosClient::megaClientCallback, this, std::placeholders::_1));
}

void RosClient::send_request(command::Mega command)
{
    mReqMega->command = static_cast<uint8_t>(command);
    mReqMega->point_xy = {0.0f, 0.0f};
    mMegaClient->async_send_request(mReqMega, std::bind(&RosClient::megaClientCallback, this, std::placeholders::_1));
}

void RosClient::send_request(uint8_t vib_motor_index)
{
    mReqMega->command = static_cast<uint8_t>(command::Mega::VIB);
    mReqMega->point_xy = {static_cast<float>(vib_motor_index), 0.0f};
    mMegaClient->async_send_request(mReqMega, std::bind(&RosClient::megaClientCallback, this, std::placeholders::_1));
}

void RosClient::megaClientCallback(rclcpp::Client<mosqibot_srv_interface::srv::MegaMsg>::SharedFuture result)
{
    auto response = result.get();
    if (!response)
    {
        RCLCPP_ERROR(this->get_logger(), "Task failed!");
    }
    taskflag = true;
}

void RosClient::cameraSubCallback(const sensor_msgs::msg::Image::ConstSharedPtr msg)
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
        std::unique_lock<std::mutex> lock(mImgMutex);
        this->img = cv_ptr->image;
    }

    cv::Mat target_img, heap_img;
    mProjector->locateTarget(cv_ptr->image, target_img);
    mProjector->locateHeap(cv_ptr->image, heap_img);

    mTargetImgMsg = *cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", target_img).toImageMsg();
    mHeapImgMsg = *cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", heap_img).toImageMsg();

    mTargetImgPub->publish(mTargetImgMsg);
    mHeapImgPub->publish(mHeapImgMsg);
}
}   // namespace MosqiBot
