cmake_minimum_required(VERSION 2.8.0)

project(declfn)

file(GLOB test_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(declfn ${test_src})



