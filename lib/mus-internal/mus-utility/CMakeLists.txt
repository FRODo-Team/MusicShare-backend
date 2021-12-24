cmake_minimum_required(VERSION 3.16)

project(mus-utility CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-utility STATIC ${SOURCES})

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

target_link_libraries(mus-utility -lcrypto)
target_include_directories(mus-utility PUBLIC include)
target_include_directories(mus-utility PRIVATE src)
