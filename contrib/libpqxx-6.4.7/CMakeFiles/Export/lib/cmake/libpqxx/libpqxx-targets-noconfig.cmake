#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libpqxx::pqxx_shared" for configuration ""
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libpqxx.so"
  IMPORTED_SONAME_NOCONFIG "libpqxx.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS libpqxx::pqxx_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_libpqxx::pqxx_shared "${_IMPORT_PREFIX}/lib/libpqxx.so" )

# Import target "libpqxx::pqxx_static" for configuration ""
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libpqxx.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libpqxx::pqxx_static )
list(APPEND _IMPORT_CHECK_FILES_FOR_libpqxx::pqxx_static "${_IMPORT_PREFIX}/lib/libpqxx.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
