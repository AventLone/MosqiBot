// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from my_interface:srv/CleanUp.idl
// generated code does not contain a copyright notice
#include "my_interface/srv/detail/clean_up__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "my_interface/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "my_interface/srv/detail/clean_up__struct.h"
#include "my_interface/srv/detail/clean_up__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _CleanUp_Request__ros_msg_type = my_interface__srv__CleanUp_Request;

static bool _CleanUp_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _CleanUp_Request__ros_msg_type * ros_message = static_cast<const _CleanUp_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: shutdown
  {
    cdr << (ros_message->shutdown ? true : false);
  }

  return true;
}

static bool _CleanUp_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _CleanUp_Request__ros_msg_type * ros_message = static_cast<_CleanUp_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: shutdown
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->shutdown = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interface
size_t get_serialized_size_my_interface__srv__CleanUp_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CleanUp_Request__ros_msg_type * ros_message = static_cast<const _CleanUp_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name shutdown
  {
    size_t item_size = sizeof(ros_message->shutdown);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _CleanUp_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_my_interface__srv__CleanUp_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interface
size_t max_serialized_size_my_interface__srv__CleanUp_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: shutdown
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _CleanUp_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_my_interface__srv__CleanUp_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_CleanUp_Request = {
  "my_interface::srv",
  "CleanUp_Request",
  _CleanUp_Request__cdr_serialize,
  _CleanUp_Request__cdr_deserialize,
  _CleanUp_Request__get_serialized_size,
  _CleanUp_Request__max_serialized_size
};

static rosidl_message_type_support_t _CleanUp_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_CleanUp_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interface, srv, CleanUp_Request)() {
  return &_CleanUp_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "my_interface/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "my_interface/srv/detail/clean_up__struct.h"
// already included above
// #include "my_interface/srv/detail/clean_up__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _CleanUp_Response__ros_msg_type = my_interface__srv__CleanUp_Response;

static bool _CleanUp_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _CleanUp_Response__ros_msg_type * ros_message = static_cast<const _CleanUp_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: done
  {
    cdr << (ros_message->done ? true : false);
  }

  return true;
}

static bool _CleanUp_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _CleanUp_Response__ros_msg_type * ros_message = static_cast<_CleanUp_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: done
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->done = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interface
size_t get_serialized_size_my_interface__srv__CleanUp_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CleanUp_Response__ros_msg_type * ros_message = static_cast<const _CleanUp_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name done
  {
    size_t item_size = sizeof(ros_message->done);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _CleanUp_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_my_interface__srv__CleanUp_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_interface
size_t max_serialized_size_my_interface__srv__CleanUp_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: done
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _CleanUp_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_my_interface__srv__CleanUp_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_CleanUp_Response = {
  "my_interface::srv",
  "CleanUp_Response",
  _CleanUp_Response__cdr_serialize,
  _CleanUp_Response__cdr_deserialize,
  _CleanUp_Response__get_serialized_size,
  _CleanUp_Response__max_serialized_size
};

static rosidl_message_type_support_t _CleanUp_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_CleanUp_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interface, srv, CleanUp_Response)() {
  return &_CleanUp_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "my_interface/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "my_interface/srv/clean_up.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t CleanUp__callbacks = {
  "my_interface::srv",
  "CleanUp",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interface, srv, CleanUp_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interface, srv, CleanUp_Response)(),
};

static rosidl_service_type_support_t CleanUp__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &CleanUp__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_interface, srv, CleanUp)() {
  return &CleanUp__handle;
}

#if defined(__cplusplus)
}
#endif
