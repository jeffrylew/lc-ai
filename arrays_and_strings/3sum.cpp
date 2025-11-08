#include <catch2/catch_test_macros.hpp>

#include <vector>

static std::vector<std::vector<int>> threeSumFA(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2966/

    //! @todo
}

TEST_CASE("Example 1", "[threeSum]")
{
    const std::vector<int> nums {-1, 0, 1, 2, -1, -4};

    const std::vector<std::vector<int>> expected_output {
        {-1, -1, 2}, {-1, 0, 1}};

    REQUIRE(expected_output == threeSumFA(nums));
}

TEST_CASE("Example 2", "[threeSum]")
{
    const std::vector<int> nums {0, 1, 1};

    REQUIRE(threeSumFA(nums).empty());
}

TEST_CASE("Example 3", "[threeSum]")
{
    const std::vector<int> nums {0, 0, 0};

    const std::vector<std::vector<int>> expected_output {{0, 0, 0}};
}
