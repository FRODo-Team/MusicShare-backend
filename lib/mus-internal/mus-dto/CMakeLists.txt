cmake_minimum_required(VERSION 3.16)

project(mus-dto CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(mus-dto INTERFACE)

target_link_libraries(mus-dto INTERFACE reflectable)
target_include_directories(mus-dto INTERFACE include/)
