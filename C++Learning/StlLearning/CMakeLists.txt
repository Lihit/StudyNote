cmake_minimum_required(VERSION 3.6)
project(StlLearning)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp jjalloc.h)
add_executable(StlLearning ${SOURCE_FILES})