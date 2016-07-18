cmake_minimum_required(VERSION 3.3)
project(PatternArg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ZparTree.cpp DepGraph.cpp)
add_executable(PatternArg ${SOURCE_FILES})