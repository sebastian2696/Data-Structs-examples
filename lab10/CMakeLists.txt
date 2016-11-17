cmake_minimum_required(VERSION 3.6)
project(Lab10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    GraphBFS.c)

add_executable(Lab10 ${SOURCE_FILES})