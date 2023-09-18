#pragma once
#include <my_interface/srv/clean_up.hpp>
#include "nodes.h"
// #include "api/include/Projector.h"
#include "api/include/FocusStacking.h"
#include "api/include/Yolo.h"

namespace MosqiBot
{
class Task
{
    /* Protocol with Qt_UI */
    enum Command : unsigned char
    {
        FAN_ON,
        FAN_OFF,
        MOSQUITO_KILLER_ON,
        MOSQUITO_KILLER_OFF,
        OUTLET_OPEN,
        OUTLET_CLOSE,
        START_SHOOT
    };

public:
    Task();
    ~Task();

    void start();

private:
    /*** Parameters ***/
    const unsigned char mTargetNum{2};

    std::string mPictureDir;
    uint16_t mGroupIndex;

    // cv::Mat camera_matrix;   // Camera matrix
    // cv::Mat dist_coeffs;     // Distortion coefficient

    /*** Multi-Threaded ***/
    std::thread mMyThreads[2];
    std::mutex mImgMutex;
    std::atomic<bool> mStartShootFlag{false};


    std::shared_ptr<RosClient> mNode;
    rclcpp::Subscription<std_msgs::msg::Byte>::SharedPtr mCommandSub;   // Receive the commands from Qt_UI
    std::unique_ptr<avent::FocusStacking> mFocusStacker{std::make_unique<avent::FocusStacking>()};
    std::unique_ptr<tensorRT::Yolo> mYoloer;


private:
    void cmdSubCallback(const std_msgs::msg::Byte::SharedPtr& msg);
    void sendAndWait(command::Mega command);
    void sendAndWait(const cv::Point2f& point);
    void sendAndWait(uint8_t vib_motor_index);

    void vibratePlate();

    void focusStackImgs(const std::string& path) const;
    void recognizeImgs(const std::string& path) const;

    /*** Tasks in threads ***/
    void task_sendMsg();
    void task_spinNode();
};
}   // namespace MosqiBot