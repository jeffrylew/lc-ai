#include <catch2/catch_test_macros.hpp>

#include <vector>

static std::vector<int> twoSumFA(const std::vector<int>& nums, int target)
{

}

TEST_CASE("Example 1", "[twoSum]")
{
    const std::vector<int> nums {2, 7, 11, 15};
    const std::vector<int> expected_output {0, 1};

    REQUIRE(expected_output == twoSumFA(nums, 9));
}

TEST_CASE("Example 2", "[twoSum]")
{
    const std::vector<int> nums {3, 2, 4};
    const std::vector<int> expected_output {1, 2};

    REQUIRE(expected_output == twoSumFA(nums, 6));
}

TEST_CASE("Example 3", "[twoSum]")
{
    const std::vector<int> nums {3, 3};
    const std::vector<int> expected_output {0, 1};

    REQUIRE(expected_output == twoSumFA(nums, 6));
}
