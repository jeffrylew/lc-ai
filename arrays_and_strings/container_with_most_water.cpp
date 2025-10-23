#include <catch2/catch_test_macros.hpp"

#include <algorithm>
#include <vector>

static int maxAreaDS2(const std::vector<int>& height)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2963/

    int max_water {};

    int left {};
    int right {static_cast<int>(std::ssize(height)) - 1};

    while (left < right)
    {
        const int width {right - left};

        max_water =
            std::max(max_water, width * std::min(height[left], height[right]));

        if (height[left] <= height[right])
        {
            ++left;
        }
        else
        {
            --right;
        }
    }

    return max_water;
}

TEST_CASE("Example 1", "[maxArea]")
{
    const std::vector<int> height {1, 8, 6, 2, 5, 4, 8, 3, 7};

    REQUIRE(49 == maxAreaDS2(height));
}

TEST_CASE("Example 2", "[maxArea]")
{
    const std::vector<int> height {1, 1};

    REQUIRE(1 == maxAreaDS2(height));
}
