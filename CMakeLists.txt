cmake_minimum_required(VERSION 3.0)
project(Server VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options serialization system REQUIRED)
find_package(libpqxx REQUIRED PATHS ${CMAKE_SOURCE_DIR}/contrib/libpqxx-6.4.7)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/contrib/nlohmann/includes)

set(NLOHMANN_HEADER ${CMAKE_SOURCE_DIR}/contrib/nlohmann/includes/nlohmann/json.hpp)
add_executable(Server main.cpp udp_server.cpp udp_server.h ${NLOHMANN_HEADER})

target_link_libraries(Server ${Boost_LIBRARIES} libpqxx::pqxx_shared)
configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)