#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE main

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite)

    BOOST_AUTO_TEST_CASE(test_case) {
        BOOST_CHECK_EQUAL(0, 0);
    }

BOOST_AUTO_TEST_SUITE_END()