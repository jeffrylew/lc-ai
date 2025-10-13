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
        if (std::isalpha(ch) != 0 || ch == '.')
        {
            return static_cast<int>(s_long);
        }

        if (ch == ' ' || (ch == '0' && s_long == 0L))
        {
            // if (prev_char != '\0' && prev_char)
            {

            }
            continue;
        }

        if (ch == '+' || ch == '-')
        {
            if (++num_signs > 1)
            {
                return static_cast<int>(s_long);
            }

            if (ch == '-')
            {
                is_negative = true;
            }
        }

        s_long *= 10L;
        s_long += static_cast<long>(ch - '0');

        if (is_negative && s_long != 0L)
        {
            s_long *= -1L;
            is_negative = false;
        }

        if (s_long < min_int)
        {
            return min_int;
        }

        if (s_long > max_int)
        {
            return max_int;
        }

        prev_char = ch;
    }

    return static_cast<int>(s_long);

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
