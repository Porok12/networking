#find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

#include_directories (${Boost_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/contrib/catch/include)

#add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test test.cpp  ${CATCH_HEADER})

#target_link_libraries (Test ${Boost_LIBRARIES})