#include <catch2/catch_test_macros.hpp>

#include <string>

static bool isValidFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2972/

    
}

TEST_CASE("Example 1", "[isValid]")
{
    REQUIRE(isValidFA("()"));
}

TEST_CASE("Example 2", "[isValid]")
{
    REQUIRE(isValidFA("()[]{}"));
}

TEST_CASE("Example 3", "[isValid]")
{
    REQUIRE(!isValidFA("(]"));
}

TEST_CASE("Example 4", "[isValid]")
{
    REQUIRE(isValidFA("([])"));
}

TEST_CASE("Example 5", "[isValid]")
{
    REQUIRE(!isValidFA("([)]"));
}
