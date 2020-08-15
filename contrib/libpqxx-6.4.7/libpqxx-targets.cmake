# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget libpqxx::pqxx_shared libpqxx::pqxx_static)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target libpqxx::pqxx_shared
add_library(libpqxx::pqxx_shared SHARED IMPORTED)

set_target_properties(libpqxx::pqxx_shared PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "PQXX_SHARED"
  INTERFACE_INCLUDE_DIRECTORIES "/home/przemek/Downloads/libpqxx-6.4.7/build/include;/home/przemek/Downloads/libpqxx-6.4.7/include"
)

# Create imported target libpqxx::pqxx_static
add_library(libpqxx::pqxx_static STATIC IMPORTED)

set_target_properties(libpqxx::pqxx_static PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/home/przemek/Downloads/libpqxx-6.4.7/build/include;/home/przemek/Downloads/libpqxx-6.4.7/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib/x86_64-linux-gnu/libpq.so"
)

# Import target "libpqxx::pqxx_shared" for configuration ""
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/przemek/Downloads/libpqxx-6.4.7/build/src/libpqxx.so"
  IMPORTED_SONAME_NOCONFIG "libpqxx.so"
  )

# Import target "libpqxx::pqxx_static" for configuration ""
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "/home/przemek/Downloads/libpqxx-6.4.7/build/src/libpqxx.a"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
