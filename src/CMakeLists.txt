set(FILES
        main.cpp
        udp_server.cpp udp_server.h
        )

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options serialization system REQUIRED)
#find_package(libpqxx REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/contrib/libpqxx-6.4.7/include)
add_library(libpqxx SHARED IMPORTED)
set_target_properties(libpqxx PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/contrib/libpqxx-6.4.7/libpqxx.so)

#find_library(log4cplus log4cplus REQUIRED)
#message(${log4cplus})
include_directories(${CMAKE_SOURCE_DIR}/contrib/log4cplus/include)
add_library(log4cplus SHARED IMPORTED)
set_target_properties(log4cplus PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/contrib/log4cplus/liblog4cplus.so)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/contrib/nlohmann/includes)
include_directories(${CMAKE_SOURCE_DIR}/contrib/cli11/include)

set(NLOHMANN_HEADER ${CMAKE_SOURCE_DIR}/contrib/nlohmann/includes/nlohmann/json.hpp)
set(CLI11_HEADER ${CMAKE_SOURCE_DIR}/contrib/cli11/include/cli11/CLI11.hpp)
add_executable(Server ${FILES} ${NLOHMANN_HEADER} ${CLI11_HEADER})

target_link_libraries(Server ${Boost_LIBRARIES} libpqxx log4cplus)
configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)