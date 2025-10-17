#include <catch2/catch_test_macros.hpp>

#include <cctype>
#include <limits>
#include <string>

static int myAtoiFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2962/
    //!
    //!          Time complexity O(N) where N = s.size().
    //!          Space complexity O(1).

    constexpr int min_int {std::numeric_limits<int>::min()};
    constexpr int max_int {std::numeric_limits<int>::max()};

    long s_long {};
    char prev_char {};
    int  num_signs {};
    bool is_negative {};

    for (const char ch : s)
    {
        //! Current character is a letter or period
        if (std::isalpha(static_cast<unsigned char>(ch)) != 0 || ch == '.')
        {
            return (is_negative && s_long != 0L)
                ? static_cast<int>(-1L * s_long)
                : static_cast<int>(s_long);
        }

        //! Previous character was a digit and current character is space or +/-
        if (0 != std::isdigit(static_cast<unsigned char>(prev_char))
            && (ch == ' ' || ch == '+' || ch == '-'))
        {
            return (is_negative && s_long != 0L)
                ? static_cast<int>(-1L * s_long)
                : static_cast<int>(s_long);
        }

        if (ch == ' ')
        {
            if (prev_char == '+' || prev_char == '-')
            {
                return 0;
            }

            prev_char = ch;
            continue;
        }

        if (ch == '0' && s_long == 0L)
        {
            prev_char = ch;
            continue;
        }

        if (ch == '+' || ch == '-')
        {
            if (++num_signs > 1)
            {
                return (is_negative && s_long != 0L)
                    ? static_cast<int>(-1L * s_long)
                    : static_cast<int>(s_long);
            }

            if (ch == '-')
            {
                is_negative = true;
            }

            prev_char = ch;
            continue;
        }

        s_long *= 10L;
        s_long += static_cast<long>(ch - '0');

        if (is_negative && s_long != 0L && s_long * -1L < min_int)
        {
            return min_int;
        }

        if (!is_negative && s_long > max_int)
        {
            return max_int;
        }

        prev_char = ch;
    }

    return (is_negative && s_long != 0L)
        ? static_cast<int>(-1L * s_long)
        : static_cast<int>(s_long);

} // static int myAtoiFA( ...

static int myAtoiDS1(std::string s)
{
    //! @details https://leetcode.com/problems/string-to-integer-atoi/editorial
    //!
    //!          Time complexity O(N) where N = s.size(). We visit each char in
    //!          s at most once and processing each char takes O(1).
    //!          Space complexity O(1) for constant space to store the sign and
    //!          result.

    //! Stores the 32-bit integer result
    int result {};

    //! Store the sign of the final result
    int sign {1};

    int        index {};
    const auto num_chars = static_cast<int>(std::ssize(s));

    //! Discard all spaces from the beginning of the input string
    while (index < num_chars && s[index] == ' ')
    {
        ++index;
    }

    //! sign = +1 if it is a positive number, else sign = -1
    if (index < num_chars)
    {
        if (s[index] == '+')
        {
            sign = 1;
            ++index;
        }
        else if (s[index] == '-')
        {
            sign = -1;
            ++index;
        }
    }

    constexpr int int_min {std::numeric_limits<int>::min()};
    constexpr int int_max {std::numeric_limits<int>::max()};

    //! Traverse subsequent chars of s and stop when the char is not a digit
    while (index < num_chars
           && std::isdigit(static_cast<unsigned char>(s[index])))
    {
        const auto digit = static_cast<int>(s[index] - '0');

        //! Check overflow and underflow conditions
        if ((result > int_max / 10)
            || (result == int_max / 10 && digit > int_max % 10))
        {
            //! If integer overflowed then return 2^31 - 1
            //! Otherwise, if integer underflowed then return -2^31
            return sign == 1 ? int_max : int_min;
        }

        //! Append current digit
        result = 10 * result + digit;
        ++index;

    } // while (index < num_chars && ...

    //! We formed a valid number without any overflow/underflow.
    //! Multiply it by sign and return it
    return sign * result;

} // static int myAtoiDS1( ...

TEST_CASE("Example 1", "[myAtoi]")
{
    REQUIRE(42 == myAtoiFA("42"));
    REQUIRE(42 == myAtoiDS1("42"));
}

TEST_CASE("Example 2", "[myAtoi]")
{
    REQUIRE(-42 == myAtoiFA(" -042"));
    REQUIRE(-42 == myAtoiDS1(" -042"));
}

TEST_CASE("Example 3", "[myAtoi]")
{
    REQUIRE(1337 == myAtoiFA("1337c0d3"));
    REQUIRE(1337 == myAtoiDS1("1337c0d3"));
}

TEST_CASE("Example 4", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("0-1"));
    REQUIRE(0 == myAtoiDS1("0-1"));
}

TEST_CASE("Example 5", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("words and 987"));
    REQUIRE(0 == myAtoiDS1("words and 987"));
}

TEST_CASE("Example 6", "[myAtoi]")
{
    REQUIRE(-2147483648 == myAtoiFA("-2147483648"));
    REQUIRE(-2147483648 == myAtoiDS1("-2147483648"));
}

TEST_CASE("Example 7", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("  +  413");)
    REQUIRE(0 == myAtoiDS1("  +  413");)
}
