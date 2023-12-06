cmake_minimum_required(VERSION 3.20)
project(Sort)

add_executable(Sort main.cpp)

target_include_directories(Sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QuickSort)
target_include_directories(Sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/BubbleSort)
target_include_directories(Sort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/InsertionSort)