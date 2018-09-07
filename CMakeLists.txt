cmake_minimum_required(VERSION 3.10)
project(vm2_0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB header ${CMAKE_SOURCE_DIR}/header/*.h)
file(GLOB source ${CMAKE_SOURCE_DIR}/source/*.cpp)

add_executable(vm2_0 main.cpp ${source} ${header})
add_subdirectory(tests)