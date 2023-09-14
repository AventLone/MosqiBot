#include "Task.h"

// bool MosqiBot::Task::shutdown_request = false;

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    MosqiBot::Task my_task;

    my_task.start();

    return 0;
}
