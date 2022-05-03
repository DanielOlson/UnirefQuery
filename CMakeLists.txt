cmake_minimum_required(VERSION 3.21)
project(UnirefQuery)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnirefQuery main.cpp UnirefHeap.cpp UnirefHeap.h)
