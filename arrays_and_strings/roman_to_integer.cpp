#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <utility>
#include <vector>

static int romanToIntFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2965/

    int              roman_numeral_to_num {};
    std::string_view roman_numerals {s};

    const std::vector<std::pair<std::string_view, int>> symbols_and_values {
        {"M", 1000},
        {"CM", 900},
        {"D", 500},
        {"CD", 400},
        {"C", 100},
        {"XC", 90},
        {"L", 50},
        {"XL", 40},
        {"X", 10},
        {"IX", 9},
        {"V", 5},
        {"IV", 4},
        {"I", 1}};

    for (const auto& [roman_numeral, roman_numeral_value] : symbols_and_values)
    {
        while (roman_numerals.starts_with(roman_numeral))
        {
            roman_numeral_to_num += roman_numeral_value;
            roman_numerals.remove_prefix(roman_numeral.size());
        }

        if (roman_numerals.empty())
        {
            break;
        }
    }

    return roman_numeral_to_num;
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
