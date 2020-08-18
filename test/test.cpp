//#define BOOST_TEST_MAIN
//#define BOOST_TEST_MODULE main
//
//#include <boost/test/unit_test.hpp>
//
//BOOST_AUTO_TEST_SUITE(test_suite)
//
//    BOOST_AUTO_TEST_CASE(test_case) {
//        BOOST_CHECK_EQUAL(0, 0);
//    }
//
//BOOST_AUTO_TEST_SUITE_END()
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}