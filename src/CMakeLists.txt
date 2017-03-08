cmake_minimum_required(VERSION 2.8)

file(GLOB rayK_SRC
    "*.hpp" "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(rayK ${rayK_SRC})

set_property(TARGET rayK PROPERTY FOLDER "executables")

install(TARGETS rayK
        RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
