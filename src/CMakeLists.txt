cmake_minimum_required(VERSION 2.8)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

file(GLOB rayK_SRC
    "*.cpp"
)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(rayK ${rayK_SRC})
