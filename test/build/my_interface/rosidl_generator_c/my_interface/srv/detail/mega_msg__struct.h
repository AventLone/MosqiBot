// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interface:srv/MegaMsg.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_H_
#define MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/MegaMsg in the package my_interface.
typedef struct my_interface__srv__MegaMsg_Request
{
  uint8_t command;
  float point_xy[2];
} my_interface__srv__MegaMsg_Request;

// Struct for a sequence of my_interface__srv__MegaMsg_Request.
typedef struct my_interface__srv__MegaMsg_Request__Sequence
{
  my_interface__srv__MegaMsg_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interface__srv__MegaMsg_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/MegaMsg in the package my_interface.
typedef struct my_interface__srv__MegaMsg_Response
{
  bool flag;
} my_interface__srv__MegaMsg_Response;

// Struct for a sequence of my_interface__srv__MegaMsg_Response.
typedef struct my_interface__srv__MegaMsg_Response__Sequence
{
  my_interface__srv__MegaMsg_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interface__srv__MegaMsg_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACE__SRV__DETAIL__MEGA_MSG__STRUCT_H_
