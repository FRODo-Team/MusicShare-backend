cmake_minimum_required(VERSION 3.16)

project(ws-server CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(ws-server SHARED ${SOURCES})

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

target_include_directories(ws-server PUBLIC include)
target_include_directories(ws-server PRIVATE src)
