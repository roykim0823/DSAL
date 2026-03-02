cmake_minimum_required(VERSION 3.5)
project(BinaryTree)

set(CMAKE_CXX_FLAGS "-g -Wall")
include_directories(../common)
include_directories(../02_ArrayBasedLists/include)
include_directories(include)
file(GLOB SRC "src/*.cpp")

add_executable(tests ${SRC})
