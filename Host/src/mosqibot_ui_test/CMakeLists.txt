cmake_minimum_required(VERSION 3.8)
project(mosqibot_ui_test)

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
set(DEPENDENT_PACKAGES
    rclcpp
    cv_bridge
    std_msgs
    mosqibot_srv_interface
)

foreach(DEPENDENCY IN ITEMS ${DEPENDENT_PACKAGES})
    find_package(${DEPENDENCY} REQUIRED)
endforeach()

# set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui)
file(GLOB RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc)
file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h) # Need to add headers into executable in Qt
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(NODE_NAME MosqiBot)

add_executable(${NODE_NAME}
    ${UI_FILES}
    ${RESOURCE_FILES}
    ${HEADER_FILES}
    ${SRC_FILES}
)

ament_target_dependencies(${NODE_NAME} ${DEPENDENT_PACKAGES})
target_link_libraries(${NODE_NAME} Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${NODE_NAME}
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
