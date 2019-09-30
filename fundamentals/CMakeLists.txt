cmake_minimum_required(VERSION 3.5)
project(ArrayBasedLists)

set(CMAKE_CXX_FLAGS "-std=c++14 -g -O0 -Werror -Wno-unused-variable -Wno-sign-compare")

include_directories(include)
file(GLOB SRCS "src/*.cc")

foreach (src IN LISTS SRCS)
  message(STATUS "${src}")
  get_filename_component(filename ${src} NAME)
  string(REPLACE "." ";" temp ${filename})
  list(GET temp 0 target)
  # add_library(${target} ${src})
  add_executable(${target} ${src})
  target_link_libraries(${target} rt)
  list(APPEND TARGET_LIST ${target})
endforeach()
