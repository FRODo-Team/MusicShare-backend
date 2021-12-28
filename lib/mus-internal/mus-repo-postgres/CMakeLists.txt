cmake_minimum_required(VERSION 3.16)

project(mus-repo-postgres CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

add_library(mus-repo-postgres STATIC ${SOURCES})

if(WITH_TESTS)
    add_subdirectory(tests)
endif()

target_link_libraries(mus-repo-postgres mus-irepo -lpqxx -lpq)
target_include_directories(mus-repo-postgres PUBLIC include)
target_include_directories(mus-repo-postgres PRIVATE src)
