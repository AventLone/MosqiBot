// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_interface:srv/UnoMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__UNO_MSG__BUILDER_HPP_
#define MY_INTERFACE__SRV__DETAIL__UNO_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_interface/srv/detail/uno_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_interface
{

namespace srv
{

namespace builder
{

class Init_UnoMsg_Request_shutdown
{
public:
  Init_UnoMsg_Request_shutdown()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interface::srv::UnoMsg_Request shutdown(::my_interface::srv::UnoMsg_Request::_shutdown_type arg)
  {
    msg_.shutdown = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interface::srv::UnoMsg_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interface::srv::UnoMsg_Request>()
{
  return my_interface::srv::builder::Init_UnoMsg_Request_shutdown();
}

}  // namespace my_interface


namespace my_interface
{

namespace srv
{

namespace builder
{

class Init_UnoMsg_Response_done
{
public:
  Init_UnoMsg_Response_done()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_interface::srv::UnoMsg_Response done(::my_interface::srv::UnoMsg_Response::_done_type arg)
  {
    msg_.done = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_interface::srv::UnoMsg_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_interface::srv::UnoMsg_Response>()
{
  return my_interface::srv::builder::Init_UnoMsg_Response_done();
}

}  // namespace my_interface

#endif  // MY_INTERFACE__SRV__DETAIL__UNO_MSG__BUILDER_HPP_
