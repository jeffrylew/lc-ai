#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <utility>
#include <vector>

static std::string intToRomanDS1(int num)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2964/
    //!          https://leetcode.com/problems/integer-to-roman/editorial/

    std::string num_to_roman_numeral;

    std::vector<std::pair<int, std::string_view>> values_and_symbols {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"}};

    //! Loop through each symbol, stopping when num is 0
    for (const auto& [roman_numeral_value, roman_numeral] : values_and_symbols)
    {
        if (num == 0)
        {
            break;
        }

        //! Repeat while the current symbol fits into num
        while (roman_numeral_value <= num)
        {
            num -= roman_numeral_value;
            num_to_roman_numeral += std::string {roman_numeral};
        }
    }

    return num_to_roman_numeral;
}

TEST_CASE("Example 1", "[intToRoman]")
{
    //! 3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
    //!  700 = DCC as 500 (D) + 100 (C) + 100 (C)
    //!   40 = XL as 10 (X) less than 50 (L)
    //!    9 = IX as 1 (I) less than 10 (X)
    REQUIRE("MMMDCCXLIX" == intToRomanDS1(3749));
}

TEST_CASE("Example 2", "[intToRoman]")
{
    //! 50 = L
    //!  8 = VIII
    REQUIRE("LVIII" == intToRomanDS1(58));
}

TEST_CASE("Example 3", "[intToRoman]")
{
    //! 1000 = M
    //!  900 = CM
    //!   90 = XC
    REQUIRE("MCMXCIV" == intToRomanDS1(1994));
}
