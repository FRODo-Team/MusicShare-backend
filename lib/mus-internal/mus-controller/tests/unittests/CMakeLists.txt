cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(run_unittests_mus_controller ${SOURCES})
target_link_libraries(run_unittests_mus_controller mus-controller GTest::Main Threads::Threads)

add_test(NAME mus_controller_unittests COMMAND run_unittests_mus_controller)
