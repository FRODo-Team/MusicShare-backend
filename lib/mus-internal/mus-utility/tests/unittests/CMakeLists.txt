cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_executable(run_unittests_mus_utility ${SOURCES})
target_link_libraries(run_unittests_mus_utility mus-utility GTest::Main Threads::Threads -lgmock -lstdc++)

add_test(NAME run_unittests_mus_utility COMMAND run_unittests_mus_utility)
