// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_interface:srv/MegaMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__MEGA_MSG__TRAITS_HPP_
#define MY_INTERFACE__SRV__DETAIL__MEGA_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_interface/srv/detail/mega_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const MegaMsg_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: command
  {
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << ", ";
  }

  // member: point_xy
  {
    if (msg.point_xy.size() == 0) {
      out << "point_xy: []";
    } else {
      out << "point_xy: [";
      size_t pending_items = msg.point_xy.size();
      for (auto item : msg.point_xy) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MegaMsg_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: command
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "command: ";
    rosidl_generator_traits::value_to_yaml(msg.command, out);
    out << "\n";
  }

  // member: point_xy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.point_xy.size() == 0) {
      out << "point_xy: []\n";
    } else {
      out << "point_xy:\n";
      for (auto item : msg.point_xy) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MegaMsg_Request & msg, bool use_flow_style = false)
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
  const my_interface::srv::MegaMsg_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const my_interface::srv::MegaMsg_Request & msg)
{
  return my_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<my_interface::srv::MegaMsg_Request>()
{
  return "my_interface::srv::MegaMsg_Request";
}

template<>
inline const char * name<my_interface::srv::MegaMsg_Request>()
{
  return "my_interface/srv/MegaMsg_Request";
}

template<>
struct has_fixed_size<my_interface::srv::MegaMsg_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_interface::srv::MegaMsg_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_interface::srv::MegaMsg_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace my_interface
{

namespace srv
{

inline void to_flow_style_yaml(
  const MegaMsg_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: flag
  {
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MegaMsg_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "flag: ";
    rosidl_generator_traits::value_to_yaml(msg.flag, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MegaMsg_Response & msg, bool use_flow_style = false)
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
  const my_interface::srv::MegaMsg_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_interface::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_interface::srv::to_yaml() instead")]]
inline std::string to_yaml(const my_interface::srv::MegaMsg_Response & msg)
{
  return my_interface::srv::to_yaml(msg);
}

template<>
inline const char * data_type<my_interface::srv::MegaMsg_Response>()
{
  return "my_interface::srv::MegaMsg_Response";
}

template<>
inline const char * name<my_interface::srv::MegaMsg_Response>()
{
  return "my_interface/srv/MegaMsg_Response";
}

template<>
struct has_fixed_size<my_interface::srv::MegaMsg_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_interface::srv::MegaMsg_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_interface::srv::MegaMsg_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<my_interface::srv::MegaMsg>()
{
  return "my_interface::srv::MegaMsg";
}

template<>
inline const char * name<my_interface::srv::MegaMsg>()
{
  return "my_interface/srv/MegaMsg";
}

template<>
struct has_fixed_size<my_interface::srv::MegaMsg>
  : std::integral_constant<
    bool,
    has_fixed_size<my_interface::srv::MegaMsg_Request>::value &&
    has_fixed_size<my_interface::srv::MegaMsg_Response>::value
  >
{
};

template<>
struct has_bounded_size<my_interface::srv::MegaMsg>
  : std::integral_constant<
    bool,
    has_bounded_size<my_interface::srv::MegaMsg_Request>::value &&
    has_bounded_size<my_interface::srv::MegaMsg_Response>::value
  >
{
};

template<>
struct is_service<my_interface::srv::MegaMsg>
  : std::true_type
{
};

template<>
struct is_service_request<my_interface::srv::MegaMsg_Request>
  : std::true_type
{
};

template<>
struct is_service_response<my_interface::srv::MegaMsg_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MY_INTERFACE__SRV__DETAIL__MEGA_MSG__TRAITS_HPP_
