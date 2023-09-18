cmake_minimum_required(VERSION 3.8)
project(qt_ui_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find Qt dependencies
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(my_interface REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB UI_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB RESOURCES_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resource/*.qrc)
file(GLOB_RECURSE WINDOW_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS window/*.cpp)

include_directories(include window)

add_executable(MosqiBot_test
    main.cpp
    ${UI_DIR}
    ${RESOURCES_DIR}
    ${WINDOW_DIR}
)

ament_target_dependencies(MosqiBot_test
    rclcpp
    std_msgs
    cv_bridge
    my_interface
)

target_link_libraries(MosqiBot_test Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS MosqiBot_test
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
