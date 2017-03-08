cmake_minimum_required(VERSION 2.8)
project(rayK)
subdirs(src)
include_directories(${CMAKE_SOURCE_DIR}/include)

message(STATUS "CXX Flags:" ${CMAKE_CXX_FLAGS})

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

