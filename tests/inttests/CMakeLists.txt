cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(run_inttests_mus ${SOURCES})
target_link_libraries(run_inttests_mus mus-usecase mus-repo-postgres GTest::Main Threads::Threads)

add_test(NAME mus_inttests COMMAND run_inttests_mus)
