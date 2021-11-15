cmake_minimum_required(VERSION 3.16)

project(mus-controller CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-controller STATIC ${SOURCES})

target_link_libraries(mus-controller PUBLIC mus-usecase mus-repo-postgres)
target_include_directories(mus-controller PUBLIC include)
target_include_directories(mus-controller PRIVATE src)
