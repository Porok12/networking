cmake_minimum_required(VERSION 3.0)
project(Server VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(SERVER_TESTING "Run tests." ON)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

add_subdirectory (src)

if (SERVER_TESTING)
    add_subdirectory(test)
endif()

