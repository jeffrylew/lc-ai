#include <catch2/catch_test_macros.hpp"

#include <vector>

static int maxAreaFA(const std::vector<int>& height)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2963/

    
}

TEST_CASE("Example 1", "[maxArea]")
{
    const std::vector<int> height {1, 8, 6, 2, 5, 4, 8, 3, 7};

    REQUIRE(49 == maxAreaFA(height));
}

TEST_CASE("Example 2", "[maxArea]")
{
    const std::vector<int> height {1, 1};

    REQUIRE(1 == maxAreaFA(height));
}
