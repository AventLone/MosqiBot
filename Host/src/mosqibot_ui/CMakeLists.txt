cmake_minimum_required(VERSION 3.22)
project(mosqibot_ui)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find Qt dependencies
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# find ROS2 dependencies
find_package(ament_cmake REQUIRED)
set(DEPENDENT_PACKAGES
    rclcpp
    cv_bridge
    sensor_msgs
    mosqibot_srv_interface
)

foreach(DEPENDENCY IN ITEMS ${DEPENDENT_PACKAGES})
    find_package(${DEPENDENCY} REQUIRED)
endforeach()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB UI_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB RESOURCES_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resource/*.qrc)
file(GLOB_RECURSE WINDOW_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS window/*.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/window
)

add_executable(MosqiBot
    main.cpp
    ${UI_DIR}
    ${RESOURCES_DIR}
    ${WINDOW_DIR}
)

ament_target_dependencies(MosqiBot ${DEPENDENT_PACKAGES})

target_link_libraries(MosqiBot Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS MosqiBot
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
