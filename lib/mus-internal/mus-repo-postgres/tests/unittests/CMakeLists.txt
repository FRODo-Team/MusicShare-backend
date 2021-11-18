cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(run_unittests_mus_repo_postgres ${SOURCES})
target_link_libraries(run_unittests_mus_repo_postgres mus-repo-postgres GTest::Main Threads::Threads gmock)

add_test(NAME mus_repo_postgres_unittests COMMAND run_unittests_mus_repo_postgres)
