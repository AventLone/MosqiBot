#pragma once
#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>
#include <my_interface/srv/mega_msg.hpp>
// #include <my_interface/srv/uno_msg.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/byte.hpp>
#include <opencv2/opencv.hpp>
// #include "mosqibot_protocol.h"
#include "api/include/Projecting.h"

namespace MosqiBot
{
/*** Commands required to send to embedded computer ***/
namespace command
{
enum class Mega : uint8_t
{
    /*** LureDevice ***/
    FAN_ON,
    FAN_OFF,
    MOSQUITO_KILLER_ON,
    MOSQUITO_KILLER_OFF,
    OUTLET_OPEN,
    OUTLET_CLOSE,
    /*** Stepper ***/
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
    LOCAL_CAMERA_1,
    LOCAL_CAMERA_2,
    LOCAL_CAMERA_3
};
}   // namespace command

class RosClient : public rclcpp::Node
{
public:
    RosClient(std::string name);

    void send_request(const cv::Point2f& point);
    void send_request(command::Mega command);
    void send_request(uint8_t vib_motor_index);

    std::vector<cv::Point2f> locateTarget()
    {
        return mProjector->locateTarget(img);
    }
    std::unordered_set<uint8_t> locateHeap()
    {
        return mProjector->locateHeap(img);
    }

public:
    cv::Mat img;
    bool taskflag;

private:
    /*** Camera extrinsics, unit: mm ***/
    // const float depth{203.5f};
    // const float width_base{206.0f - (22.1 * 2)};
    // const float height_base{183.0f};
    // const cv::Point2f tvec{width_base / 2.0f, height_base / 2.0f};

    /*** Used for locate the coordinates of mosquitos and heaps of mosquitos. ***/
    std::unique_ptr<avent::Projecting> mProjector;

    std::mutex mImgMutex;

    /*** Declare a client and a subscription ***/
    rclcpp::Client<my_interface::srv::MegaMsg>::SharedPtr mMegaClient;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr mCameraSub;

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr mTargetImgPub;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr mHeapImgPub;

    sensor_msgs::msg::Image mTargetImgMsg, mHeapImgMsg;

    std::shared_ptr<my_interface::srv::MegaMsg::Request> mReqMega =
        std::make_shared<my_interface::srv::MegaMsg::Request>();

private:
    void callback_client_mega(rclcpp::Client<my_interface::srv::MegaMsg>::SharedFuture result);
    void callback_subsription(const sensor_msgs::msg::Image::ConstSharedPtr msg);
};
}   // namespace MosqiBot
