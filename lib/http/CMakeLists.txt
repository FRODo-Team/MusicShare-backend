cmake_minimum_required(VERSION 3.16)

project(http-server CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(examples)

#if(WITH_TESTS)
    #add_subdirectory(tests)
#endif()

add_library(http SHARED ${SOURCES})

target_include_directories(http PUBLIC include)
target_include_directories(http PRIVATE src)
target_link_libraries(http ${Boost_LIBRARIES} Threads::Threads)
