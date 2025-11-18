#include <catch2/catch_test_macros.hpp>

#include <vector>

static int threeSumClosestFA(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2967/

    //! @todo
}

TEST_CASE("Example 1", "[threeSumClosest]")
{
    const std::vector<int> nums {-1, 2, 1, -4};
    constexpr int          target {1};

    REQUIRE(2 == threeSumClosestFA(nums, target));
}

TEST_CASE("Example 2", "[threeSumClosest]")
{
    const std::vector<int> nums {0, 0, 0};
    constexpr int          target {1};

    REQUIRE(0 == threeSumClosestFA(nums, target));
}
