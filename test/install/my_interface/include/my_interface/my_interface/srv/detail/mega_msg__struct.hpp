// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interface:srv/MegaMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_HPP_
#define MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_interface__srv__MegaMsg_Request __attribute__((deprecated))
#else
# define DEPRECATED__my_interface__srv__MegaMsg_Request __declspec(deprecated)
#endif

namespace my_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MegaMsg_Request_
{
  using Type = MegaMsg_Request_<ContainerAllocator>;

  explicit MegaMsg_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = 0;
      std::fill<typename std::array<float, 2>::iterator, float>(this->point_xy.begin(), this->point_xy.end(), 0.0f);
    }
  }

  explicit MegaMsg_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : point_xy(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->command = 0;
      std::fill<typename std::array<float, 2>::iterator, float>(this->point_xy.begin(), this->point_xy.end(), 0.0f);
    }
  }

  // field types and members
  using _command_type =
    uint8_t;
  _command_type command;
  using _point_xy_type =
    std::array<float, 2>;
  _point_xy_type point_xy;

  // setters for named parameter idiom
  Type & set__command(
    const uint8_t & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__point_xy(
    const std::array<float, 2> & _arg)
  {
    this->point_xy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interface::srv::MegaMsg_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interface::srv::MegaMsg_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::MegaMsg_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::MegaMsg_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interface__srv__MegaMsg_Request
    std::shared_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interface__srv__MegaMsg_Request
    std::shared_ptr<my_interface::srv::MegaMsg_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MegaMsg_Request_ & other) const
  {
    if (this->command != other.command) {
      return false;
    }
    if (this->point_xy != other.point_xy) {
      return false;
    }
    return true;
  }
  bool operator!=(const MegaMsg_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MegaMsg_Request_

// alias to use template instance with default allocator
using MegaMsg_Request =
  my_interface::srv::MegaMsg_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace my_interface


#ifndef _WIN32
# define DEPRECATED__my_interface__srv__MegaMsg_Response __attribute__((deprecated))
#else
# define DEPRECATED__my_interface__srv__MegaMsg_Response __declspec(deprecated)
#endif

namespace my_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MegaMsg_Response_
{
  using Type = MegaMsg_Response_<ContainerAllocator>;

  explicit MegaMsg_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->flag = false;
    }
  }

  explicit MegaMsg_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->flag = false;
    }
  }

  // field types and members
  using _flag_type =
    bool;
  _flag_type flag;

  // setters for named parameter idiom
  Type & set__flag(
    const bool & _arg)
  {
    this->flag = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interface::srv::MegaMsg_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interface::srv::MegaMsg_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::MegaMsg_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::MegaMsg_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interface__srv__MegaMsg_Response
    std::shared_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interface__srv__MegaMsg_Response
    std::shared_ptr<my_interface::srv::MegaMsg_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MegaMsg_Response_ & other) const
  {
    if (this->flag != other.flag) {
      return false;
    }
    return true;
  }
  bool operator!=(const MegaMsg_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MegaMsg_Response_

// alias to use template instance with default allocator
using MegaMsg_Response =
  my_interface::srv::MegaMsg_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace my_interface

namespace my_interface
{

namespace srv
{

struct MegaMsg
{
  using Request = my_interface::srv::MegaMsg_Request;
  using Response = my_interface::srv::MegaMsg_Response;
};

}  // namespace srv

}  // namespace my_interface

#endif  // MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_HPP_
