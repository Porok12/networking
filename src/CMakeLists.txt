set(FILES
    main.cpp
    udp_server.cpp udp_server.h
    )

#include(${CMAKE_SOURCE_DIR}/conan-build/conanbuildinfo.cmake)
#conan_basic_setup()
#find_package(Boost COMPONENTS REQUIRED regex system date_time asio)
#target_link_libraries(${PROJECT_NAME} PUBLIC Boost::Boost)

set(BOOST_INCLUDEDIR "C:\boost\include")
set(BOOST_LIBRARYDIR "C:\boost\lib")
set(BOOST_ROOT "C:\boost")

message("${BOOST_ROOT}")
message("${BOOST_LIBRARYDIR}")
message("${BOOST_INCLUDEDIR}")

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost 1.68.0 COMPONENTS REQUIRED program_options serialization system)

message(">${Boost_FOUND}")
message(">${Boost_INCLUDE_DIR}")
message(">${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIR})

add_executable(Server ${FILES})

target_link_libraries(Server ${Boost_LIBRARIES} pthread Catch CLI json pqxx_shared) # log4cplus

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)
