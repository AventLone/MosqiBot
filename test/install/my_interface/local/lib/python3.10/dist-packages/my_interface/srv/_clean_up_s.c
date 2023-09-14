// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from my_interface:srv/CleanUp.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "my_interface/srv/detail/clean_up__struct.h"
#include "my_interface/srv/detail/clean_up__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool my_interface__srv__clean_up__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[43];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("my_interface.srv._clean_up.CleanUp_Request", full_classname_dest, 42) == 0);
  }
  my_interface__srv__CleanUp_Request * ros_message = _ros_message;
  {  // shutdown
    PyObject * field = PyObject_GetAttrString(_pymsg, "shutdown");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->shutdown = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * my_interface__srv__clean_up__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of CleanUp_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("my_interface.srv._clean_up");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "CleanUp_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  my_interface__srv__CleanUp_Request * ros_message = (my_interface__srv__CleanUp_Request *)raw_ros_message;
  {  // shutdown
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->shutdown ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "shutdown", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "my_interface/srv/detail/clean_up__struct.h"
// already included above
// #include "my_interface/srv/detail/clean_up__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool my_interface__srv__clean_up__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[44];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("my_interface.srv._clean_up.CleanUp_Response", full_classname_dest, 43) == 0);
  }
  my_interface__srv__CleanUp_Response * ros_message = _ros_message;
  {  // done
    PyObject * field = PyObject_GetAttrString(_pymsg, "done");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->done = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * my_interface__srv__clean_up__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of CleanUp_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("my_interface.srv._clean_up");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "CleanUp_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  my_interface__srv__CleanUp_Response * ros_message = (my_interface__srv__CleanUp_Response *)raw_ros_message;
  {  // done
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->done ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "done", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
