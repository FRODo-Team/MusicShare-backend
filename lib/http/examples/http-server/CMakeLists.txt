cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
add_executable(http_examples_http-server ${SOURCES})

target_link_libraries(http_examples_http-server http)
