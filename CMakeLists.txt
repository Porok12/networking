cmake_minimum_required(VERSION 3.0)
project(Server VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options serialization system REQUIRED)
#find_package(Poco REQUIRED COMPONENTS Foundation Net Zip)
find_package(libpqxx REQUIRED PATHS ${CMAKE_SOURCE_DIR}/contrib/libpqxx-6.4.7)

include_directories(${Boost_INCLUDE_DIR})

add_executable(Server main.cpp udp_server.cpp udp_server.h)

target_link_libraries(Server ${Boost_LIBRARIES} libpqxx::pqxx_shared)

## set the POCO paths and libs
#set(POCO_PREFIX      "/home/przemek/poco/poco/cmake-build/") # the directory containing "include" and "lib"
#set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
#set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
#set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNetd.a"
#        "${POCO_LIB_DIR}/libPocoUtild.a"
#        "${POCO_LIB_DIR}/libPocoJSONd.a"
#        "${POCO_LIB_DIR}/libPocoXMLd.a"
#        "${POCO_LIB_DIR}/libPocoFoundationd.a"
#        "pthread")
#
## set the include path for the app
#target_include_directories(Server PRIVATE "${POCO_INCLUDE_DIR}")
#
## link the app against POCO
#target_link_libraries(Server "${POCO_LIBS}")