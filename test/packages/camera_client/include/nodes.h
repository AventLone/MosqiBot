#pragma once
#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>
#include <my_interface/srv/mega_msg.hpp>
// #include <my_interface/srv/uno_msg.hpp>
#include <opencv2/opencv.hpp>
// #include "mosqibot_protocol.h"
#include "Projector.h"

namespace MosqiBot
{
/*** Commands required to send to embedded computer ***/
namespace command
{
enum class Mega : uint8_t
{
    VIB,
    POWER_ON,
    INIT,
    Z,
    FLIP,
    XY,
    READY_CAMERA,
    POWER_OFF,
    /*** For Camera ***/
    INIT_CAMERA,
    GLOB_CAMERA,
    LOCAL_CAMERA
};
}   // namespace command

class RosClient : public rclcpp::Node
{
public:
    RosClient(std::string name);

    void send_request(const cv::Point2f& point);
    void send_request(command::Mega command);
    void send_request(uint8_t vib_motor_index);

    inline std::vector<cv::Point2f> locateTarget()
    {
        return projector->detect(img);
    }
    inline std::unordered_set<uint8_t> locateHeap()
    {
        return projector->locateHeap(img);
    }

public:
    cv::Mat img;
    bool taskflag;

private:
    /*** Camera extrinsics, unit: mm ***/
    const float depth{203.5f};
    const float width_base{206.0f - (22.1 * 2)};
    const float height_base{183.0f};
    const cv::Point2f tvec{width_base / 2.0f, height_base / 2.0f};

    /*** Used for locate the coordinates of mosquitos and heaps of mosquitos. ***/
    std::unique_ptr<Projector> projector{nullptr};

    std::mutex mtx;

    /*** Declare a client and a subscription ***/
    rclcpp::Client<my_interface::srv::MegaMsg>::SharedPtr client_mega{nullptr};
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_{nullptr};
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr target_img_publisher{nullptr};
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr heap_img_publisher{nullptr};

    sensor_msgs::msg::Image target_img_msg, heap_img_msg;

    std::shared_ptr<my_interface::srv::MegaMsg::Request> req_mega =
        std::make_shared<my_interface::srv::MegaMsg::Request>();

private:
    void callback_client_mega(rclcpp::Client<my_interface::srv::MegaMsg>::SharedFuture result);
    void callback_subsription(const sensor_msgs::msg::Image::ConstSharedPtr msg);
};
}   // namespace MosqiBot
