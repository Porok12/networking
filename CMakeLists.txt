cmake_minimum_required(VERSION 3.0)
project(Client VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options thread serialization system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(Client main.cpp udp_client.cpp udp_client.h)

target_link_libraries(Client ${Boost_LIBRARIES} pthread)

if (WIN32)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(Client ws2_32)
    endif()
endif()
