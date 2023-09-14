// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_interface:srv/CleanUp.idl
// generated code does not contain a copyright notice

#ifndef MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_H_
#define MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/CleanUp in the package my_interface.
typedef struct my_interface__srv__CleanUp_Request
{
  bool shutdown;
} my_interface__srv__CleanUp_Request;

// Struct for a sequence of my_interface__srv__CleanUp_Request.
typedef struct my_interface__srv__CleanUp_Request__Sequence
{
  my_interface__srv__CleanUp_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interface__srv__CleanUp_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/CleanUp in the package my_interface.
typedef struct my_interface__srv__CleanUp_Response
{
  bool done;
} my_interface__srv__CleanUp_Response;

// Struct for a sequence of my_interface__srv__CleanUp_Response.
typedef struct my_interface__srv__CleanUp_Response__Sequence
{
  my_interface__srv__CleanUp_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_interface__srv__CleanUp_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_INTERFACE__SRV__DETAIL__CLEAN_UP__STRUCT_H_
