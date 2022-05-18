cmake_minimum_required(VERSION 3.21)
project(MyList)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyList main.cpp List.h reverse_iterator.h)
