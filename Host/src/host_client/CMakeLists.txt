cmake_minimum_required(VERSION 3.8)
project(host_client)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set sub directory
set(API_LIB api)
add_subdirectory(api)

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
set(DEPENDENT_PACKAGES
    rclcpp
    my_interface
    OpenCV
    cv_bridge
)

foreach(DEPENDENCY IN ITEMS ${DEPENDENT_PACKAGES})
    find_package(${DEPENDENCY} REQUIRED)
endforeach()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17
ament_target_dependencies(${PROJECT_NAME} ${DEPENDENT_PACKAGES})
target_link_libraries(${PROJECT_NAME} ${API_LIB})

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib/${PROJECT_NAME}
)
install(DIRECTORY launch config model
    DESTINATION share/${PROJECT_NAME}
)

ament_package()
