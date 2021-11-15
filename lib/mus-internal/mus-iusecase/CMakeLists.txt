cmake_minimum_required(VERSION 3.16)

project(mus-iusecase CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(mus-iusecase INTERFACE)

target_link_libraries(mus-iusecase mus-dto mus-irepo)
target_include_directories(mus-iusecase INTERFACE include/)
