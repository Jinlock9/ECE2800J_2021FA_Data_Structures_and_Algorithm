cmake_minimum_required(VERSION 3.20)
project(demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(demo
        calc.cpp
        dlist.h
        dlist_impl.h)
