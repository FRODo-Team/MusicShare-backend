cmake_minimum_required(VERSION 3.16)

project(http-server CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

add_library(http-server SHARED ${SOURCES})

target_include_directories(http-server PUBLIC include)
target_include_directories(http-server PRIVATE src)
target_link_libraries(http-server ${Boost_LIBRARIES})
