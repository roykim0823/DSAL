cmake_minimum_required(VERSION 3.10)
project(ch16_external_searching CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -O0 -Wall)

include_directories(include)
file(GLOB SRCS "src/*.cc")

foreach(src IN LISTS SRCS)
  get_filename_component(name ${src} NAME_WE)
  add_executable(${PROJECT_NAME}_${name} ${src})
endforeach()
