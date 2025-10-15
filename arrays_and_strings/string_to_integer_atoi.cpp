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

TEST_CASE("Example 1", "[myAtoi]")
{
    REQUIRE(42 == myAtoiFA("42"));
}

TEST_CASE("Example 2", "[myAtoi]")
{
    REQUIRE(-42 == myAtoiFA(" -042"));
}

TEST_CASE("Example 3", "[myAtoi]")
{
    REQUIRE(1337 == myAtoiFA("1337c0d3"));
}

TEST_CASE("Example 4", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("0-1"));
}

TEST_CASE("Example 5", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("words and 987"));
}

TEST_CASE("Example 6", "[myAtoi]")
{
    REQUIRE(-2147483648 == myAtoiFA("-2147483648"));
}

TEST_CASE("Example 7", "[myAtoi]")
{
    REQUIRE(0 == myAtoiFA("  +  413");)
}
