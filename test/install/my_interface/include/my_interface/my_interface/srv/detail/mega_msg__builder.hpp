// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interface:srv/MegaMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__MEGA_MSG__BUILDER_HPP_
#define MY_INTERFACE__SRV__DETAIL__MEGA_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interface/srv/detail/mega_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interface
{

namespace srv
{

namespace builder
{

class Init_MegaMsg_Request_point_xy
{
public:
  explicit Init_MegaMsg_Request_point_xy(::my_interface::srv::MegaMsg_Request & msg)
  : msg_(msg)
  {}
  ::my_interface::srv::MegaMsg_Request point_xy(::my_interface::srv::MegaMsg_Request::_point_xy_type arg)
  {
    msg_.point_xy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interface::srv::MegaMsg_Request msg_;
};

class Init_MegaMsg_Request_command
{
public:
  Init_MegaMsg_Request_command()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MegaMsg_Request_point_xy command(::my_interface::srv::MegaMsg_Request::_command_type arg)
  {
    msg_.command = std::move(arg);
    return Init_MegaMsg_Request_point_xy(msg_);
  }

private:
  ::my_interface::srv::MegaMsg_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interface::srv::MegaMsg_Request>()
{
  return my_interface::srv::builder::Init_MegaMsg_Request_command();
}

}  // namespace my_interface


namespace my_interface
{

namespace srv
{

namespace builder
{

class Init_MegaMsg_Response_flag
{
public:
  Init_MegaMsg_Response_flag()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interface::srv::MegaMsg_Response flag(::my_interface::srv::MegaMsg_Response::_flag_type arg)
  {
    msg_.flag = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interface::srv::MegaMsg_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interface::srv::MegaMsg_Response>()
{
  return my_interface::srv::builder::Init_MegaMsg_Response_flag();
}

}  // namespace my_interface

#endif  // MY_INTERFACE__SRV__DETAIL__MEGA_MSG__BUILDER_HPP_
