#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

static std::string convertToWords(int num)
{
    if (num < 10)
    {
        static const std::vector<std::string> belowTen {
            "",
            "One",
            "Two",
            "Three",
            "Four",
            "Five",
            "Six",
            "Seven",
            "Eight",
            "Nine"};
        return belowTen[num];
    }

    if (num < 20)
    {
        static const std::vector<std::string> belowTwenty {
            "Ten",
            "Eleven",
            "Twelve",
            "Thirteen",
            "Fourteen",
            "Fifteen",
            "Sixteen",
            "Seventeen",
            "Eighteen",
            "Nineteen"};
        return belowTwenty[num - 10];
    }

    if (num < 100)
    {
        static const std::vector<std::string> belowHundred {
            "",
            "Ten",
            "Twenty",
            "Thirty",
            "Forty",
            "Fifty",
            "Sixty",
            "Seventy",
            "Eighty",
            "Ninety"};
        return belowHundred[num / 10]
            + (num % 10 ? " " + convertToWords(num % 10) : "");
    }

    if (num < 1000)
    {
        return convertToWords(num / 100) + " Hundred"
            + (num % 100 ? " " + convertToWords(num % 100) : "");
    }

    if (num < 1000000)
    {
        return convertToWords(num / 1000) + " Thousand"
            + (num % 1000 ? " " + convertToWords(num % 1000) : "");
    }

    if (num < 1000000000)
    {
        return convertToWords(num / 1000000) + " Million"
            + (num % 1000000 ? " " + convertToWords(num % 1000000) : "");
    }

    return convertToWords(num / 1000000000) + " Billion"
        + (num % 1000000000 ? " " + convertToWords(num % 1000000000) : "");
}

static std::string numberToWordsDS1(int num)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/481/

    if (num == 0)
    {
        return "Zero";
    }

    return convertToWords(num);
}

TEST_CASE("Example 1", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Hundred Twenty Three"};

    REQUIRE(expected_output == numberToWordsDS1(123));
}

TEST_CASE("Example 2", "[numberToWords]")
{
    constexpr const char* expected_output {
        "Twelve Thousand Three Hundred Forty Five"};

    REQUIRE(expected_output == numberToWordsDS1(12345));
}

TEST_CASE("Example 3", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
    };

    REQUIRE(expected_output == numberToWordsDS1(1234567));
}
