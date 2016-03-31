cmake_minimum_required(VERSION 2.8.0)

project(declfn)

file(GLOB test_src "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(declfn ${test_src})



