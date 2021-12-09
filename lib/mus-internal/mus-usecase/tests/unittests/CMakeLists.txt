cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(run_unittests_mus_use_case ${SOURCES})
target_link_libraries(run_unittests_mus_use_case mus-usecase GTest::Main Threads::Threads -lgmock)

add_test(NAME run_unittests_mus_use_case COMMAND run_unittests_mus_use_case)
