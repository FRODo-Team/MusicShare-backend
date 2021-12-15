cmake_minimum_required(VERSION 3.16)

project(mus-usecase CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-usecase STATIC ${SOURCES})

target_link_libraries(mus-usecase INTERFACE mus-iusecase)
target_include_directories(mus-usecase PUBLIC include)
target_include_directories(mus-usecase PRIVATE src)
