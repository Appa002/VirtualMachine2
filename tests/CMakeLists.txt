cmake_minimum_required(VERSION 3.11)
project(instructions_check)

set(CMAKE_CXX_STANDARD 17)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/../source/*.cpp)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/../headers/*.h)

add_executable(instructions_check instructions_check.cpp  ${sources} ${headers} unit_framework.h)

