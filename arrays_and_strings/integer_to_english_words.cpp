#include <catch2/catch_test_macros.hpp>

#include <array>
#include <string>
#include <string_view>
#include <utility>
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
    //!
    //!          Time complexity O(log_10 N) because the number of recursive
    //!          calls is proportional to the number of digits in the number,
    //!          which grows logarithmically with the size of the number.
    //!          Space complexity O(log_10 N) because of the recursion stack.
    //!          Each recursive call adds a frame to the stack until the base
    //!          case is reached, leading to space usage proportional to the
    //!          number of digits in the number.

    if (num == 0)
    {
        return "Zero";
    }

    return convertToWords(num);
}

static std::string numberToWordsDS2(int num)
{
    //! @details leetcode.com/problems/integer-to-english-words/editorial
    //!
    //!          Time complexity O(log_10 N) because num is divided by 1000 each
    //!          iteration, making the number of iterations proportional to the
    //!          number of chunks, which is logarithmic.
    //!          Space complexity O(1).

    if (num == 0)
    {
        return "Zero";
    }

    const std::vector<std::string> ones {
        "",
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
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

    const std::vector<std::string> tens {
        "",
        "",
        "Twenty",
        "Thirty",
        "Forty",
        "Fifty",
        "Sixty",
        "Seventy",
        "Eighty",
        "Ninety"};

    const std::vector<std::string> thousands {
        "", "Thousand", "Million", "Billion"};

    std::string result;
    int         group_idx {};

    //! Process the number in chunks of 1000
    while (num > 0)
    {
        //! Process the last three digits
        if (num % 1000 != 0)
        {
            std::string group_result;
            int         part {num % 1000};

            //! Handle hundreds
            if (part >= 100)
            {
                group_result = ones[part / 100] + " Hundred ";
                part %= 100;
            }

            //! Handle tens and units
            if (part >= 20)
            {
                group_result += tens[part / 10] + " ";
                part %= 10
            }

            //! Handle units
            if (part > 0)
            {
                group_result += ones[part] + " ";
            }

            //! Append the scale (thousand, million, billion) for current group
            group_result += thousands[group_idx] + " ";

            //! Insert the group result at the beginning of the final result
            result = group_result + result;

        } // if (num % 1000 != 0)

        //! Move to the next chunk of 1000
        num /= 1000;
        ++group_idx;
    }

    //! Remove trailing spaces
    return result.substr(0, result.find_last_not_of(" ") + 1);
}

static std::string numberToWordsDS3(int num)
{
    //! @details leetcode.com/problems/integer-to-english-words/editorial
    //!
    //!          Time complexity O(K) where K = number of pairs in num_to_words
    //!          because the loop iterates through the pairs until it finds a
    //!          match.
    //!          Space complexity O(log_10 N) where N = num due to the recursion
    //!          stack.

    //! Array of numeric values to corresponding English words
    constexpr std::array<std::pair<int, std::string_view>, 31> num_to_words {
        {1000000000, "Billion"},
        {1000000, "Million"},
        {1000, "Thousand"},
        {100, "Hundred"},
        {90, "Ninety"},
        {80, "Eighty"},
        {70, "Seventy"},
        {60, "Sixty"},
        {50, "Fifty"},
        {40, "Forty"},
        {30, "Thirty"},
        {20, "Twenty"},
        {19, "Nineteen"},
        {18, "Eighteen"},
        {17, "Seventeen"},
        {16, "Sixteen"},
        {15, "Fifteen"},
        {14, "Fourteen"},
        {13, "Thirteen"},
        {12, "Twelve"},
        {11, "Eleven"},
        {10, "Ten"},
        {9, "Nine"},
        {8, "Eight"},
        {7, "Seven"},
        {6, "Six"},
        {5, "Five"},
        {4, "Four"},
        {3, "Three"},
        {2, "Two"},
        {1, "One"}};

    if (num == 0)
    {
        return "Zero";
    }

    for (const auto& [value, word] : num_to_words)
    {
        //! Check if the number is greater than or equal to the current unit
        if (num < value)
        {
            continue;
        }

        //! Convert the quotient to words if the current unit is 100 or greater
        std::string prefix {
            num >= 100 ? numberToWordsDS3(num / value) + " " : ""};

        //! Get the word for the current unit
        std::string unit {word};

        //! Convert the remainder to words if it's not zero
        std::string suffix {
            num % value == 0 ? "" : " " + numberToWordsDS3(num % value)};

        return prefix + unit + suffix;
    }

    return {};
}

TEST_CASE("Example 1", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Hundred Twenty Three"};

    REQUIRE(expected_output == numberToWordsDS1(123));
    REQUIRE(expected_output == numberToWordsDS2(123));
    REQUIRE(expected_output == numberToWordsDS3(123));
}

TEST_CASE("Example 2", "[numberToWords]")
{
    constexpr const char* expected_output {
        "Twelve Thousand Three Hundred Forty Five"};

    REQUIRE(expected_output == numberToWordsDS1(12345));
    REQUIRE(expected_output == numberToWordsDS2(12345));
    REQUIRE(expected_output == numberToWordsDS3(12345));
}

TEST_CASE("Example 3", "[numberToWords]")
{
    constexpr const char* expected_output {
        "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
    };

    REQUIRE(expected_output == numberToWordsDS1(1234567));
    REQUIRE(expected_output == numberToWordsDS2(1234567));
    REQUIRE(expected_output == numberToWordsDS3(1234567));
}
