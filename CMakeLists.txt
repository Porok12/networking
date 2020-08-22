set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0092 NEW)
cmake_minimum_required(VERSION 3.1)
project(Server VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(SERVER_TESTING "Run tests." ON)

set(INSTALL_DESTINATION bin)

message(">>>> ${INSTALL_DESTINATION} <<<<")
message(">>>> ${CMAKE_INSTALL_PREFIX} <<<<")

# Catch2
execute_process(COMMAND git submodule update --init -- contrib/Catch2
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

unset(Catch_INCLUDE_DIR CACHE)
set(Catch_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib/Catch2/single_include
CACHE PATH "Catch2 include directory")

install(DIRECTORY ${Catch_INCLUDE_DIR}/Catch2 DESTINATION ${INSTALL_DESTINATION})

add_library(Catch INTERFACE)

target_include_directories(Catch INTERFACE
    $<BUILD_INTERFACE:${Catch_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INSTALL_DESTINATION}>)

install(TARGETS Catch EXPORT my_export_set DESTINATION ${INSTALL_DESTINATION})

# CLI11
execute_process(COMMAND git submodule update --init -- contrib/CLI11
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

unset(CLI_INCLUDE_DIR CACHE)
set(CLI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CLI11/include
        CACHE PATH "CLI11 include directory")

install(DIRECTORY ${CLI_INCLUDE_DIR}/CLI11 DESTINATION ${INSTALL_DESTINATION})

add_library(CLI INTERFACE)
target_include_directories(CLI INTERFACE
        $<BUILD_INTERFACE:${CLI_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${INSTALL_DESTINATION}>)

install(TARGETS CLI EXPORT my_export_set DESTINATION ${INSTALL_DESTINATION})

# json
execute_process(COMMAND git submodule update --init -- contrib/json
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

unset(json_INCLUDE_DIR CACHE)
set(json_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib/json/single_include
        CACHE PATH "json include directory")

install(DIRECTORY ${json_INCLUDE_DIR}/json DESTINATION ${INSTALL_DESTINATION})

add_library(json INTERFACE)
target_include_directories(json INTERFACE
        $<BUILD_INTERFACE:${json_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${INSTALL_DESTINATION}>)

install(TARGETS json EXPORT my_export_set DESTINATION ${INSTALL_DESTINATION})

## log4cplus
#find_path(log4cplus_INCLUDE_DIR ...)
#find_library(log4cplus_LIBRARY ...)
#message(">>>> ${log4cplus_LIBRARY}  ${log4cplus_INCLUDE_DIR} <<<<")
#
#if((NOT log4cplus_LIBRARY) OR (NOT EXISTS ${log4cplus_INCLUDE_DIR}))
#    message("Unable to find log4cplus")
#
#    execute_process(COMMAND git submodule update --init -- contrib/log4cplus
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#
##    set(WITH_UNIT_TESTS OFF CACHE BOOL "Enable unit tests" FORCE)
#    add_subdirectory(contrib/log4cplus)
#    message("${log4cplus}")
#else()
#    # see above, setup target as well
#endif()

# libpqxx
execute_process(COMMAND git submodule update --init -- contrib/libpqxx
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(contrib/libpqxx)
message("${pqxx_shared}")

# Source directory
set(SKIP_BUILD_TEST ON)
set(BUILD_TEST OFF)
add_subdirectory (src)

if (SERVER_TESTING)
    add_subdirectory(test)
endif()


#if (WIN32)
#    target_link_libraries(Server ws2_32)
#endif ()
