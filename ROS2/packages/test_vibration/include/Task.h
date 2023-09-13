#pragma once
#include <rclcpp/rclcpp.hpp>
#include "mosqibot_protocol.h"
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
    std::shared_ptr<RosClient> node;

    /*** Creat two threads ***/
    std::thread my_threads[2];
    std::mutex img_mutex;


private:
    void sendAndWait(uint8_t vib_motor_index);

    void vibratePlat();

    /*** Tasks in threads ***/
    void task_sendMsg();
    void task_spinNode();
};
}   // namespace MosqiBot