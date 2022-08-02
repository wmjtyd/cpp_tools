cmake_minimum_required(VERSION 3.22)

set(NAME cpp_tools)
project(${NAME})

set(CMAKE_CXX_STANDARD 14)

## load in pkg-config support
find_package(PkgConfig)

add_executable(${NAME} main.cpp zmq_publish.h zmq_subscribe.h test_publish.cpp test_subscribe.cpp)
