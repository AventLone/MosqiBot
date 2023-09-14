cmake_minimum_required(VERSION 3.8)
project(test_vibration)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(my_interface REQUIRED)
find_package(OpenCV REQUIRED)
find_package(cv_bridge REQUIRED)

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# file(GLOB_RECURSE LIB_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS lib/*.cpp)
# file(GLOB_RECURSE INCLUDE_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/*.cpp)
# file(GLOB_RECURSE SOURCE_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)
# file(GLOB TENSORRT_LIBS "${TENSORRT_LIB_PATH}/*.so")
file(GLOB INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp)
file(GLOB SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_executable(${PROJECT_NAME}
    ${INCLUDE_DIR}
    ${SOURCE_DIR}
    ${LIBS_DIR}
)

# add_executable(undistort_node
# src/undistort_node.cpp
# )
target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17
ament_target_dependencies(${PROJECT_NAME}
    "rclcpp"
    "my_interface"
    "OpenCV"
    "cv_bridge"
)
# target_link_libraries(${PROJECT_NAME}
#     ${LIBS}
# )

install(TARGETS
    ${PROJECT_NAME}
    DESTINATION lib/${PROJECT_NAME}
)

# add relevant directory to the project
install(DIRECTORY
    launch
    param
    DESTINATION share/${PROJECT_NAME}
)

ament_package()
