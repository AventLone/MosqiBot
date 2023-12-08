#include "Task.h"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    MosqiBot::Task my_task;
    my_task.start();
    return 0;
}
