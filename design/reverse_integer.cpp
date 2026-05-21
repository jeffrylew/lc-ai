#include <catch2/catch_test_macros.hpp>

#include <limits>

static int reverseFA(int x)
{
    //! @details leetcode.com/explore/interview/card/amazon/82/design/3002
    //!
    //!          Time complexity O(N) where N = number of digits that x has.
    //!          Function can be made constexpr and evaluated at compile time.
    //!          Space complexity O(1).

    if (x == std::numeric_limits<int>::lowest())
    {
        return 0;
    }

    const bool is_negative {x < 0};
    int        reversed_x {};

    while (x != 0)
    {
        const int digit_to_append {is_negative ? -x % 10 : x % 10};

        if ((is_negative && -reversed_x <
                (std::numeric_limits<int>::lowest() + digit_to_append) / 10)
            || reversed_x >
                (std::numeric_limits<int>::max() - digit_to_append) / 10)
        {
            return 0;
        }

        reversed_x *= 10;
        reversed_x += digit_to_append;

        x /= 10;
    }

    return is_negative ? -reversed_x : reversed_x;
}

static int reverseDS(int x)
{
    //! @details https://leetcode.com/problems/reverse-integer/editorial/
    //!
    //!          Time complexity O(log x). x has roughly log_10(x) digits.
    //!          Space complexity O(1).

    int reversed_x {};

    while (x != 0)
    {
        const int digit_to_append {x % 10};
        x /= 10;

        if (reversed_x > std::numeric_limits<int>::max() / 10
            || (reversed_x == std::numeric_limits<int>::max() / 10
                && digit_to_append > 7))
        {
            return 0;
        }

        if (reversed_x < std::numeric_limits<int>::lowest() / 10
            || (reversed_x == std::numeric_limits<int>::lowest() / 10
                && digit_to_append < -8))
        {
            return 0;
        }

        reversed_x = 10 * reversed_x + digit_to_append;
    }

    return reversed_x;
}

TEST_CASE("Example 1", "[reverse]")
{
    REQUIRE(321 == reverseFA(123));
    REQUIRE(321 == reverseDS(123));
}

TEST_CASE("Example 2", "[reverse]")
{
    REQUIRE(-321 == reverseFA(-123));
    REQUIRE(-321 == reverseDS(-123));
}

TEST_CASE("Example 3", "[reverse]")
{
    REQUIRE(21 == reverseFA(120));
    REQUIRE(21 == reverseDS(120));
}

TEST_CASE("Example 4", "[reverse]")
{
    REQUIRE(0 == reverseFA(-2147483648));
    REQUIRE(0 == reverseDS(-2147483648));
}

TEST_CASE("Example 5", "[reverse]")
{
    REQUIRE(-1 == reverseFA(-10));
    REQUIRE(-1 == reverseDS(-10));
}

TEST_CASE("Example 6", "[reverse]")
{
    REQUIRE(-2147483651 == reverseFA(-1563847412));
    REQUIRE(-2147483651 == reverseDS(-1563847412));
}
