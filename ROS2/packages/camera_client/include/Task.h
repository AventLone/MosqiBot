#pragma once
#include <rclcpp/rclcpp.hpp>
// #include "mosqibot_protocol.h"
#include <my_interface/srv/clean_up.hpp>
#include "nodes.h"
#include "Projector.h"
// #include "FocusStacking.h"

namespace MosqiBot
{
class Task
{
public:
    Task();
    ~Task();

    void start();

private:
    // static bool shutdown_request;
    std::shared_ptr<RosClient> node{nullptr};
    rclcpp::Service<my_interface::srv::CleanUp>::SharedPtr mCleanUpServer;

    // cv::Mat pic;
    std::string picture_dir;
    uint16_t group_index;

    cv::Mat camera_matrix;   // Camera matrix
    cv::Mat dist_coeffs;     // Distortion coefficient

    /*** Creat two threads ***/
    std::thread my_threads[2];
    std::mutex img_mutex;

    // std::unique_ptr<FocusStacking> focusStacker = std::make_unique<FocusStacking>();

    /*** Parameters ***/
    const unsigned char target_num{10};

private:
    void sendAndWait(command::Mega command);
    void sendAndWait(const cv::Point2f& point);
    void sendAndWait(uint8_t vib_motor_index);

    void vibratePlate();

    void handle_cleanup(const std::shared_ptr<my_interface::srv::CleanUp::Request> request,
                        std::shared_ptr<my_interface::srv::CleanUp::Response> response);

    /*** Tasks in threads ***/
    void task_sendMsg();
    void task_spinNode();
};
}   // namespace MosqiBot