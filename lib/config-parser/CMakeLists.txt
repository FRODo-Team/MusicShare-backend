cmake_minimum_required(VERSION 3.16)

project(http-server CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_subdirectory(src)

add_library(config-parser SHARED ${SOURCES})

target_include_directories(config-parser PUBLIC include)
target_include_directories(config-parser PRIVATE src)
target_link_libraries(config-parser PUBLIC nlohmann_json::nlohmann_json)
