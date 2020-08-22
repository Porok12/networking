set(FILES
    main.cpp
    udp_server.cpp udp_server.h
    )

#include(${CMAKE_SOURCE_DIR}/conan-build/conanbuildinfo.cmake)
#conan_basic_setup()
#find_package(Boost COMPONENTS REQUIRED regex system date_time asio)
#target_link_libraries(${PROJECT_NAME} PUBLIC Boost::Boost)

message("+++ ${BOOST_ROOT}")
message("+++ ${BOOST_INCLUDEDIR}")
message("+++ ${BOOST_LIBRARYDIR}")

set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${BOOST_ROOT}")
  message("+++ ${BOOST_ROOT}")
  set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
  message("+++ ${BOOST_INCLUDEDIR}")
  set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
  message("+++ ${BOOST_LIBRARYDIR}")
endif (Boost_NO_SYSTEM_PATHS)
set(Boost_USE_STATIC_LIBS   ON)
# set(Boost_COMPILER "-x32")
set(Boost_ARCHITECTURE "-x32")
find_package(Boost 1.68.0 COMPONENTS REQUIRED program_options serialization system)

message(">${Boost_FOUND}")
message(">${Boost_INCLUDE_DIR}")
message(">${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIR})

add_executable(Server ${FILES})

target_link_libraries(Server ${Boost_LIBRARIES} pthread Catch CLI json pqxx_shared) # log4cplus

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)
