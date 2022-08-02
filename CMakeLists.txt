cmake_minimum_required(VERSION 3.22)
project(c___test)

set(CMAKE_CXX_STANDARD 14)

add_executable(c___test main.cpp zmq_publish.h zmq_subscribe.h test_publish.cpp test_subscribe.cpp)
