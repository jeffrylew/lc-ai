#include <catch2/catch_test_macros.hpp>

#include <string>

static std::string numberToWordsFA(int num)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/481/

    //! @todo
}

TEST_CASE("Example 1", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Hundred Twenty Three"};

    REQUIRE(expected_output == numberToWordsFA(123));
}

TEST_CASE("Example 2", "[numberToWords]")
{
    constexpr const char* expected_output {
        "Twelve Thousand Three Hundred Forty Five"};

    REQUIRE(expected_output == numberToWordsFA(12345));
}

TEST_CASE("Example 3", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
    };

    REQUIRE(expected_output == numberToWordsFA(1234567));
}
