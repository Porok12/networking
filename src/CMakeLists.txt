set(FILES
    main.cpp
    udp_server.cpp udp_server.h
    )

if (WIN32)
    set(Boost_NO_SYSTEM_PATHS TRUE)
    if (Boost_NO_SYSTEM_PATHS)
      set(BOOST_ROOT "${BOOST_ROOT}")
      message("+++ ${BOOST_ROOT}")
      set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
      message("+++ ${BOOST_INCLUDEDIR}")
      set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
      message("+++ ${BOOST_LIBRARYDIR}")
    endif (Boost_NO_SYSTEM_PATHS)
    
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
    set(Boost_USE_STATIC_LIBS   ON)
    set(Boost_ARCHITECTURE "-x64")
endif (WIN32)

find_package(Boost 1.60.0 COMPONENTS REQUIRED program_options serialization system)

message("  >${Boost_FOUND}")
message("  >${Boost_INCLUDE_DIR}")
message("  >${Boost_LIBRARIES}")

include_directories(${Boost_INCLUDE_DIR})

add_executable(Server ${FILES})

target_link_libraries(Server ${Boost_LIBRARIES} pthread Catch CLI json pqxx_shared) # log4cplus

configure_file(${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)
