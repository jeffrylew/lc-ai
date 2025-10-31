#include <catch2/catch_test_macros.hpp>

#include <string>

static int romanToIntFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2965/

    //! @todo
}

TEST_CASE("Example 1", "[romanToInt]")
{
    REQUIRE(3 == romanToIntFA("III"));
}

TEST_CASE("Example 2", "[romanToInt]")
{
    REQUIRE(58 == romanToIntFA("LVIII"));
}

TEST_CASE("Example 3", "[romanToInt]")
{
    REQUIRE(1994 == romainToIntFA("MCMXCIV"));
}
