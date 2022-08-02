cmake_minimum_required(VERSION 3.16)

set(NAME cpp_tools)
project(${NAME})

set(CMAKE_CXX_STANDARD 14)
set(ZMQ_USE_LIBSODIUM 1)
set(ZMQ_STATIC 1)
## load in pkg-config support
find_package(PkgConfig)

find_package(ZeroMQ REQUIRED)
#find_package(OpenSSL REQUIRED)
link_libraries(libzmq.a libsodium.a)
add_executable(${NAME}  test_subscribe.cpp zmq_publish.h zmq_subscribe.h )
TARGET_LINK_LIBRARIES(${NAME} dl pthread)

#test_publish.cpp