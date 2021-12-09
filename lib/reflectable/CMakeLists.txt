cmake_minimum_required(VERSION 3.16)

project(reflectable CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(reflectable INTERFACE)

target_include_directories(reflectable INTERFACE include/)
