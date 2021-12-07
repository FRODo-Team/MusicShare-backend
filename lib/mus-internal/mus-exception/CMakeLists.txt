cmake_minimum_required(VERSION 3.16)

project(mus-exception CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-exception STATIC ${SOURCES})

target_include_directories(mus-exception PUBLIC include/)