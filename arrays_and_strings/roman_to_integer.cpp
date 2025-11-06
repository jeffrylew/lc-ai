#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

static int romanToIntFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2965/
    //!
    //!          Time complexity O(N) where N = s.size(). We iterate through
    //!          each character or pairs of characters in s and check if there
    //!          is a match in the symbols_and_values vector, which has a fixed
    //!          size.
    //!          Space complexity O(1). symbols_and_values remains constant even
    //!          as the size of the input grows and the roman_numerals
    //!          string_view uses O(1) space.

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

static int romanToIntDS1(std::string s)
{
    //! @details https://leetcode.com/problems/roman-to-integer/editorial/
    //!
    //!          Time complexity O(1). There is a finite set of Roman numerals
    //!          with a maximum possible value of 3999 (MMMCMXCIX). If there
    //!          were an arbitrary number of symbols then the time complexity
    //!          would be proportional to the length of the input s, i.e. O(N)
    //!          where N = s.size().
    //!          Space complexity O(1) since a constant number of single-value
    //!          variables are used.

    int roman_numeral_to_num {};

    const std::unordered_map<char, int> symbols_to_values {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}};

    const auto s_size = static_cast<int>(std::ssize(s));
    int        idx {};

    while (idx < s_size)
    {
        const char curr_symbol {s[idx]};
        const int  curr_value {symbols_to_values.at(curr_symbol)};

        //! Check if a next value exists
        if (idx + 1 < s_size)
        {
            const char next_symbol {s[idx + 1]};
            const int  next_value {symbols_to_values.at(next_symbol)};

            if (curr_value < next_value)
            {
                //! The current and next symbols satisfy the subtractive case
                roman_numeral_to_num += next_value - curr_value;
                idx += 2;
                continue;
            }
        }

        //! The current symbol and next symbol (if it exists)
        //! do not satisfy the subtractive case
        roman_numeral_to_num += curr_value;
        ++idx;
    }

    return roman_numeral_to_num;
}

static int romanToIntDS2(std::string s)
{
    //! @details https://leetcode.com/problems/roman-to-integer/editorial/
    //!
    //!          Time complexity O(1)
    //!          Space complexity O(1)

    const std::unordered_map<std::string, int> symbols_to_values {
        {"I", 1},
        {"V", 5},
        {"X", 10},
        {"L", 50},
        {"C", 100},
        {"D", 500},
        {"M", 1000},
        {"IV", 4},
        {"IX", 9},
        {"XL", 40},
        {"XC", 90},
        {"CD", 400},
        {"CM", 900}};

    const auto s_size = static_cast<int>(std::ssize(s));

    int roman_numeral_to_num {};
    int idx {};

    while (idx < s_size)
    {
        if (idx < s_size - 1)
        {
            const auto double_symbol = s.substr(idx, 2);

            //! Check if this is the size() - 2 symbol case
            if (symbols_to_values.contains(double_symbol))
            {
                roman_numeral_to_num += symbols_to_values.at(double_symbol);
                idx += 2;
                continue;
            }
        }

        //! Otherwise, this is the size() - 1 symbol case
        const auto single_symbol = s.substr(idx, 1);
        roman_numeral_to_num += symbols_to_values.at(single_symbol);
        ++idx;
    }

    return roman_numeral_to_num;
}

static int romanToIntDS3(std::string s)
{
    //! @details https://leetcode.com/problems/roman-to-integer/editorial/
    //!
    //!          Time complexity O(1).
    //!          Space complexity O(1).

    const std::unordered_map<char, int> symbols_to_values {
        {'M', 1000},
        {'D', 500},
        {'C', 100},
        {'L', 50},
        {'X', 10},
        {'V', 5},
        {'I', 1}};

    const auto s_size = static_cast<int>(std::ssize(s));

    int last_value {symbols_to_values.at(s.back())};
    int roman_numeral_to_num {last_value};

    for (int idx = s_size - 2; idx >= 0; --idx)
    {
        const int curr_value {symbols_to_values.at(s[idx])};

        if (curr_value < last_value)
        {
            roman_numeral_to_num -= curr_value;
        }
        else
        {
            roman_numeral_to_num += curr_value;
        }

        last_value = curr_value;
    }

    return roman_numeral_to_num;
}

TEST_CASE("Example 1", "[romanToInt]")
{
    REQUIRE(3 == romanToIntFA("III"));
    REQUIRE(3 == romanToIntDS1("III"));
    REQUIRE(3 == romanToIntDS2("III"));
    REQUIRE(3 == romanToIntDS3("III"));
}

TEST_CASE("Example 2", "[romanToInt]")
{
    REQUIRE(58 == romanToIntFA("LVIII"));
    REQUIRE(58 == romanToIntDS1("LVIII"));
    REQUIRE(58 == romanToIntDS2("LVIII"));
    REQUIRE(58 == romanToIntDS3("LVIII"));
}

TEST_CASE("Example 3", "[romanToInt]")
{
    REQUIRE(1994 == romanToIntFA("MCMXCIV"));
    REQUIRE(1994 == romanToIntDS1("MCMXCIV"));
    REQUIRE(1994 == romanToIntDS2("MCMXCIV"));
    REQUIRE(1994 == romanToIntDS3("MCMXCIV"));
}
