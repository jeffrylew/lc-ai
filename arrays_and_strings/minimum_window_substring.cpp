#include <catch2/catch_test_macros.hpp>

#include <string>

static std::string minWindowFA(std::string s, std::string t)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/902/
}

TEST_CASE("Example 1", "[minWindow]")
{
    REQUIRE("BANC" == minWindowFA("ADOBECODEBANC", "ABC"));
}

TEST_CASE("Example 2", "[minWindow]")
{
    REQUIRE("a" == minWindowFA("a", "a"));
}

TEST_CASE("Example 3", "[minWindow]")
{
    REQUIRE(minWindowFA("a", "aa").empty());
}
