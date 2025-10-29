#include <catch2/catch_test_macros.hpp>

#include <array>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

static std::string intToRomanDS1(int num)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2964/
    //!          https://leetcode.com/problems/integer-to-roman/editorial/
    //!
    //!          Time complexity O(1). There is a finite set of roman numerals
    //!          so there is a hard upper limit on how many times the loop can
    //!          iterate. This upper limit is 15 times, and it occurs for the
    //!          number 3888, which has the representation MMMDCCCLXXXVIII.
    //!          Therefore, we say the time complexity is constant.
    //!          Space complexity O(1). The amount of memory used does not
    //!          change with the size of the input integer.

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

static std::string intToRomanDS2(int num)
{
    //! @details https://leetcode.com/problems/integer-to-roman/editorial/

    constexpr std::array<std::string_view, 4U> thousands {"", "M", "MM", "MMM"};

    constexpr std::array<std::string_view, 10U> hundreds {
        "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};

    constexpr std::array<std::string_view, 10U> tens {
        "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};

    constexpr std::array<std::string_view, 10U> ones {
        "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    return std::string {thousands[num / 1000]}
        + std::string {hundreds[num % 1000 / 100]}
        + std::string {tens[num % 100 / 10]}
        + std::string {ones[num % 10]};
}

TEST_CASE("Example 1", "[intToRoman]")
{
    //! 3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
    //!  700 = DCC as 500 (D) + 100 (C) + 100 (C)
    //!   40 = XL as 10 (X) less than 50 (L)
    //!    9 = IX as 1 (I) less than 10 (X)
    REQUIRE("MMMDCCXLIX" == intToRomanDS1(3749));
    REQUIRE("MMMDCCXLIX" == intToRomanDS2(3749));
}

TEST_CASE("Example 2", "[intToRoman]")
{
    //! 50 = L
    //!  8 = VIII
    REQUIRE("LVIII" == intToRomanDS1(58));
    REQUIRE("LVIII" == intToRomanDS2(58));
}

TEST_CASE("Example 3", "[intToRoman]")
{
    //! 1000 = M
    //!  900 = CM
    //!   90 = XC
    REQUIRE("MCMXCIV" == intToRomanDS1(1994));
    REQUIRE("MCMXCIV" == intToRomanDS2(1994));
}
