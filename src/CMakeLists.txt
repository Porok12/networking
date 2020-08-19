set(FILES
    main.cpp
    udp_server.cpp udp_server.h
    )

set(Boost_USE_STATIC_LIBS   OFF)
find_package(Boost COMPONENTS program_options serialization system REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(Server ${FILES})

target_link_libraries(Server ${Boost_LIBRARIES} Catch CLI json pqxx_shared) # log4cplus

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)