#ifndef ROSNODE_HPP
#define ROSNODE_HPP

#include <cv_bridge/cv_bridge.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class RosNode : public rclcpp::Node
{
public:
    RosNode(std::string name);

private:
    //    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr   subscripstion_ = nullptr;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr target_img_sub{nullptr};
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr heap_img_sub{nullptr};

private:
    void callback_subscription(const std_msgs::msg::String::SharedPtr msg);
};

RosNode::RosNode(std::string name) : Node(name)
{
    //    target_img_sub = this->create_subscription<sensor_msgs::msg::Image>()
}

#endif
