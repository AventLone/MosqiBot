# Add dependencies
find_package(CUDA REQUIRED)
find_package(OpenCV REQUIRED)

# Find tensorRT lib
set(TENSORRT_LIB_PATH /home/avent/.CppLib/TensorRT-8.5.3.1/lib)
file(GLOB TENSORRT_LIBS ${TENSORRT_LIB_PATH}/*.so)

# Add library
file(GLOB API_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(${API_LIB} STATIC ${API_SOURCE_FILES}) # Build a static library.

target_compile_features(${API_LIB} PUBLIC c_std_99 cxx_std_17) # Require C99 and C++17
target_include_directories(${API_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /home/avent/.CppLib/TensorRT-8.5.3.1/include
    ${CUDA_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(${API_LIB}
    ${TENSORRT_LIBS}
    ${CUDA_LIBRARIES}
)
