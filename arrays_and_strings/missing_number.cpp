#include <catch2/catch_test_macros.hpp>

#include <vector>

static int missingNumberFA(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2971/

    //! @todo
}

TEST_CASE("Example 1", "[missingNumber]")
{
    const std::vector<int> nums {3, 0, 1};

    REQUIRE(2 == missingNumberFA(nums));
}

TEST_CASE("Example 2", "[missingNumber]")
{
    const std::vector<int> nums {0, 1};

    REQUIRE(2 == missingNumberFA(nums));
}

TEST_CASE("Example 3", "[missingNumber]")
{
    const std::vector<int> nums {9, 6, 4, 2, 3, 5, 7, 0, 1};

    REQUIRE(8 == missingNumberFA(nums));
}
