// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_interface:srv/CleanUp.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_HPP_
#define MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_interface__srv__CleanUp_Request __attribute__((deprecated))
#else
# define DEPRECATED__my_interface__srv__CleanUp_Request __declspec(deprecated)
#endif

namespace my_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CleanUp_Request_
{
  using Type = CleanUp_Request_<ContainerAllocator>;

  explicit CleanUp_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->shutdown = false;
    }
  }

  explicit CleanUp_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->shutdown = false;
    }
  }

  // field types and members
  using _shutdown_type =
    bool;
  _shutdown_type shutdown;

  // setters for named parameter idiom
  Type & set__shutdown(
    const bool & _arg)
  {
    this->shutdown = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interface::srv::CleanUp_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interface::srv::CleanUp_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::CleanUp_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::CleanUp_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interface__srv__CleanUp_Request
    std::shared_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interface__srv__CleanUp_Request
    std::shared_ptr<my_interface::srv::CleanUp_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CleanUp_Request_ & other) const
  {
    if (this->shutdown != other.shutdown) {
      return false;
    }
    return true;
  }
  bool operator!=(const CleanUp_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CleanUp_Request_

// alias to use template instance with default allocator
using CleanUp_Request =
  my_interface::srv::CleanUp_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace my_interface


#ifndef _WIN32
# define DEPRECATED__my_interface__srv__CleanUp_Response __attribute__((deprecated))
#else
# define DEPRECATED__my_interface__srv__CleanUp_Response __declspec(deprecated)
#endif

namespace my_interface
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CleanUp_Response_
{
  using Type = CleanUp_Response_<ContainerAllocator>;

  explicit CleanUp_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->done = false;
    }
  }

  explicit CleanUp_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->done = false;
    }
  }

  // field types and members
  using _done_type =
    bool;
  _done_type done;

  // setters for named parameter idiom
  Type & set__done(
    const bool & _arg)
  {
    this->done = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_interface::srv::CleanUp_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_interface::srv::CleanUp_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::CleanUp_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_interface::srv::CleanUp_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_interface__srv__CleanUp_Response
    std::shared_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_interface__srv__CleanUp_Response
    std::shared_ptr<my_interface::srv::CleanUp_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CleanUp_Response_ & other) const
  {
    if (this->done != other.done) {
      return false;
    }
    return true;
  }
  bool operator!=(const CleanUp_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CleanUp_Response_

// alias to use template instance with default allocator
using CleanUp_Response =
  my_interface::srv::CleanUp_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace my_interface

namespace my_interface
{

namespace srv
{

struct CleanUp
{
  using Request = my_interface::srv::CleanUp_Request;
  using Response = my_interface::srv::CleanUp_Response;
};

}  // namespace srv

}  // namespace my_interface

#endif  // MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_HPP_
