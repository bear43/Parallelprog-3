cmake_minimum_required(VERSION 3.13)
project(untitled3)

set(CMAKE_CXX_STANDARD 17)

link_libraries(-lmpi)

add_executable(untitled3 main.cpp)