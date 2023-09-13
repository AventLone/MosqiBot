#include "Task.h"
#include <filesystem>

namespace MosqiBot
{
Task::Task()
{
    node = std::make_shared<RosClient>("test_vib");
}

Task::~Task()
{
    for (uint8_t i = 0; i < 2; ++i)
    {
        if (my_threads[i].joinable())
        {
            my_threads[i].join();
        }
    }
}

void Task::start()
{
    my_threads[0] = std::thread(&Task::task_sendMsg, this);
    my_threads[1] = std::thread(&Task::task_spinNode, this);
}

void Task::sendAndWait(uint8_t vib_motor_index)
{
    node->send_request(vib_motor_index);
    while (!node->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    node->taskflag = false;
}

void Task::vibratePlat()
{
    cv::Mat tmp_img;
    static uint8_t n_vib = 10;   // The maximm number of vibrations of the vibration plate.
    std::unordered_set<uint8_t> area_marks = node->locateHeap();
    if (area_marks.empty() || --n_vib == 0)
    {
        n_vib = 10;
        return;
    }
    uint8_t temp = 0;
    for (uint8_t i : area_marks)
    {
        temp |= 1 << i;
    }
    sendAndWait(temp);
    vibratePlat();
}

void Task::task_sendMsg()
{
    std::this_thread::sleep_for(std::chrono::seconds(3));   // Waiting for camera prepared
    while (rclcpp::ok())
    {
        if (node->img.empty())
        {
            continue;
        }
        vibratePlat();
        // uint8_t a = 1;
        // sendAndWait(a);
        // RCLCPP_INFO(node->get_logger(), "Send!");
        break;
    }
}

void Task::task_spinNode()
{
    rclcpp::spin(node);
    rclcpp::shutdown();
}
}   // namespace MosqiBot