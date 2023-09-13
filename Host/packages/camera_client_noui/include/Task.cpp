#include "Task.h"
#include <filesystem>

namespace MosqiBot
{
Task::Task() : group_index(0)
{
    node = std::make_shared<RosClient>("ros_client");

    /*************** Create picture folder ******************/
    std::filesystem::path dir_path = "/home/avent/Desktop/MosqiBot_Pictures";
    uint16_t count = 1;
    if (!std::filesystem::is_directory(dir_path))
    {
        std::filesystem::create_directory(dir_path);
    }
    for (const auto& entry : std::filesystem::directory_iterator(dir_path))
    {
        if (entry.is_directory())
        {
            ++count;
        }
    }
    picture_dir = dir_path.string() + "/Task_" + std::to_string(count);
    std::filesystem::create_directory(picture_dir);
    /********************************************************/
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

void Task::sendAndWait(command::Mega command)
{
    node->send_request(command);
    while (!node->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    node->taskflag = false;
}

void Task::sendAndWait(const cv::Point2f& point)
{
    node->send_request(point);
    while (!node->taskflag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    node->taskflag = false;
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

void Task::vibratePlate()
{
    cv::Mat tmp_img;
    static uint8_t n_vib = 6;   // The maximum number of vibrations.
    std::unordered_set<uint8_t> area_marks = node->locateHeap();
    if (area_marks.empty() || --n_vib == 0)
    {
        n_vib = 6;
        return;
    }
    uint8_t temp = 0;
    for (uint8_t i : area_marks)
    {
        temp |= 1 << i;
    }
    sendAndWait(temp);
    vibratePlate();
}

void Task::task_sendMsg()
{
    sendAndWait(command::Mega::INIT);
    sendAndWait(command::Mega::INIT_CAMERA);
    while (rclcpp::ok())
    {
        if (node->img.empty())
        {
            continue;
        }

        /*** 1.Move the camera to the right middel place ***/
        sendAndWait(command::Mega::GLOB_CAMERA);
        sendAndWait(command::Mega::READY_CAMERA);               // Make camera on the top center position.
        std::this_thread::sleep_for(std::chrono::seconds(6));   // Waiting for camera prepared
        /***************************************************/

        /*** 2.Scatter the mosquitoes with shaking/vibration ***/
        vibratePlate();
        /*******************************************************/

        /*** 3.Take pictures on mosquitos one by one. ***/
        auto points = node->locateTarget();
        if (points.size() >= this->target_num)
        {
            uint8_t picture_index = 0;
            std::string picture_path = picture_dir + "/Group_" + std::to_string(++group_index);
            std::filesystem::create_directory(picture_path);
            sendAndWait(command::Mega::LOCAL_CAMERA);
            sendAndWait(command::Mega::POWER_ON);
            sendAndWait(command::Mega::Z);
            for (const auto& coordinate : points)
            {
                sendAndWait(coordinate);
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                cv::imwrite(picture_path + "/" + std::to_string(++picture_index) + ".jpg", node->img);
            }
            sendAndWait(command::Mega::FLIP);
            sendAndWait(command::Mega::POWER_OFF);
        }
        /**********************************************************/

        /*** 4.Init the device. ***/
        sendAndWait(command::Mega::INIT);
        sendAndWait(command::Mega::INIT_CAMERA);
        /*****************************/

        break;
        std::this_thread::sleep_for(std::chrono::seconds(600));
    }
}

void Task::task_spinNode()
{
    rclcpp::spin(node);
    rclcpp::shutdown();
}
}   // namespace MosqiBot
