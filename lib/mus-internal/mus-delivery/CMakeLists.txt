cmake_minimum_required(VERSION 3.16)

project(mus-delivery CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-delivery STATIC ${SOURCES})

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

target_link_libraries(mus-delivery PUBLIC http mus-usecase mus-repo-postgres)
target_include_directories(mus-delivery PUBLIC include)
target_include_directories(mus-delivery PRIVATE src)
