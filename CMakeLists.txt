cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
PROJECT(asyncLoger VERSION 0.1)

#设置为debug
#set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++17 -O3")
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(test)
