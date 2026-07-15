# Top-level build for the modernized chapter reference.
#
#   cmake -S . -B build
#   cmake --build build -j
#
# Each chapter is an independent sub-project that also builds on its own
# (see chNN_*/CMakeLists.txt).  Every chapter produces one executable named
# <chapter_dir>_main, e.g. build/ch01_introduction/ch01_introduction_main.

cmake_minimum_required(VERSION 3.10)
project(algorithm_ref_cpp CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ch01_introduction)
add_subdirectory(ch02_analysis)
add_subdirectory(ch03_elementary_ds)
add_subdirectory(ch04_abstract_data_types)
add_subdirectory(ch05_recursion_trees)
add_subdirectory(ch06_elementary_sorting)
add_subdirectory(ch07_quicksort)
add_subdirectory(ch08_mergesort)
add_subdirectory(ch09_priority_queues_heapsort)
add_subdirectory(ch10_radix_sorting)
add_subdirectory(ch11_special_purpose_sorts)
add_subdirectory(ch12_symbol_tables_bst)
add_subdirectory(ch13_balanced_trees)
add_subdirectory(ch14_hashing)
add_subdirectory(ch15_radix_search)
add_subdirectory(ch16_external_searching)
add_subdirectory(ch17_graph_properties)
add_subdirectory(ch18_graph_search)
add_subdirectory(ch19_digraphs_dags)
add_subdirectory(ch20_mst)
add_subdirectory(ch21_shortest_paths)
add_subdirectory(ch22_network_flow)
