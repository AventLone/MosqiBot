// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_interface:srv/UnoMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__UNO_MSG__TRAITS_HPP_
#define MY_INTERFACE__SRV__DETAIL__UNO_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_interface/srv/detail/uno_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const UnoMsg_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: shutdown
  {
    out << "shutdown: ";
    rosidl_generator_traits::value_to_yaml(msg.shutdown, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UnoMsg_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: shutdown
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "shutdown: ";
    rosidl_generator_traits::value_to_yaml(msg.shutdown, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UnoMsg_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace my_interface

namespace rosidl_generator_traits
{

[[deprecated("use my_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_interface::srv::UnoMsg_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const my_interface::srv::UnoMsg_Request & msg)
{
  return my_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<my_interface::srv::UnoMsg_Request>()
{
  return "my_interface::srv::UnoMsg_Request";
}

template<>
inline const char * name<my_interface::srv::UnoMsg_Request>()
{
  return "my_interface/srv/UnoMsg_Request";
}

template<>
struct has_fixed_size<my_interface::srv::UnoMsg_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_interface::srv::UnoMsg_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_interface::srv::UnoMsg_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace my_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const UnoMsg_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: done
  {
    out << "done: ";
    rosidl_generator_traits::value_to_yaml(msg.done, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UnoMsg_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: done
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "done: ";
    rosidl_generator_traits::value_to_yaml(msg.done, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UnoMsg_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace my_interface

namespace rosidl_generator_traits
{

[[deprecated("use my_interface::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_interface::srv::UnoMsg_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const my_interface::srv::UnoMsg_Response & msg)
{
  return my_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<my_interface::srv::UnoMsg_Response>()
{
  return "my_interface::srv::UnoMsg_Response";
}

template<>
inline const char * name<my_interface::srv::UnoMsg_Response>()
{
  return "my_interface/srv/UnoMsg_Response";
}

template<>
struct has_fixed_size<my_interface::srv::UnoMsg_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_interface::srv::UnoMsg_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_interface::srv::UnoMsg_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<my_interface::srv::UnoMsg>()
{
  return "my_interface::srv::UnoMsg";
}

template<>
inline const char * name<my_interface::srv::UnoMsg>()
{
  return "my_interface/srv/UnoMsg";
}

template<>
struct has_fixed_size<my_interface::srv::UnoMsg>
  : std::integral_constant<
    bool,
    has_fixed_size<my_interface::srv::UnoMsg_Request>::value &&
    has_fixed_size<my_interface::srv::UnoMsg_Response>::value
  >
{
};

template<>
struct has_bounded_size<my_interface::srv::UnoMsg>
  : std::integral_constant<
    bool,
    has_bounded_size<my_interface::srv::UnoMsg_Request>::value &&
    has_bounded_size<my_interface::srv::UnoMsg_Response>::value
  >
{
};

template<>
struct is_service<my_interface::srv::UnoMsg>
  : std::true_type
{
};

template<>
struct is_service_request<my_interface::srv::UnoMsg_Request>
  : std::true_type
{
};

template<>
struct is_service_response<my_interface::srv::UnoMsg_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MY_INTERFACE__SRV__DETAIL__UNO_MSG__TRAITS_HPP_
