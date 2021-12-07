cmake_minimum_required(VERSION 3.16)

project(mus CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)

add_compile_options(-Wall -Werror -pedantic)
add_compile_options("$<$<CONFIG:DEBUG>:-g3;-gdb>")

option(WITH_COVERAGE "Add coverage estimation")
if(WITH_COVERAGE)
    add_compile_options("$<$<CONFIG:DEBUG>:--coverage>")
    add_link_options("$<$<CONFIG:DEBUG>:--coverage>")
endif()

option(WITH_SANS "Add sanitizers")
if (WITH_SANS)
    add_compile_options("$<$<CONFIG:DEBUG>:-fno-omit-frame-pointer;-fsanitize=address,memory,undefiend,thread>")
    add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address,memory,undefiend,thread>")
endif()

option(WITH_TESTS "Build tests" ON)
if(WITH_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif()

add_subdirectory(lib)
add_subdirectory(src)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

add_executable(run_mus ${SOURCES})

target_link_libraries(run_mus PUBLIC http-server ws-server mus-controller)
target_include_directories(run_mus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
