cmake_minimum_required(VERSION 3.16)

project(mus-irepo CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(mus-irepo INTERFACE)

target_link_libraries(mus-irepo INTERFACE mus-models)
target_include_directories(mus-irepo INTERFACE include/)
