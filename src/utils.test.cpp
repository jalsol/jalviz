#define CATCH_CONFIG_MAIN
#include "utils.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Check the return value of returnOne", "[return_one]") {
    REQUIRE(returnOne() == 1);
}
