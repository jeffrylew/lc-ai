#include <catch2/catch_test_macros.hpp>

#include <limits>

static int reverseFA(int x)
{
    //! @details leetcode.com/explore/interview/card/amazon/82/design/3002
    //!
    //!          First attempt does not pass Example 4 yet.

    const bool is_negative {x < 0};
    int        reversed_x {};

    while (x != 0)
    {
        const int digit_to_append {x > 0 ? x % 10 : -x % 10};

        if (reversed_x > std::numeric_limits<int>::max() / 10 - digit_to_append)
        {
            return 0;
        }

        reversed_x *= 10;
        reversed_x += digit_to_append;

        x /= 10;
    }

    return is_negative ? -reversed_x : reversed_x;
}

TEST_CASE("Example 1", "[reverse]")
{
    REQUIRE(321 == reverseFA(123));
}

TEST_CASE("Example 2", "[reverse]")
{
    REQUIRE(-321 == reverseFA(-123));
}

TEST_CASE("Example 3", "[reverse]")
{
    REQUIRE(21 == reverseFA(120));
}

TEST_CASE("Example 4", "[reverse]")
{
    REQUIRE(0 != reverseFA(-2147483648));
}
