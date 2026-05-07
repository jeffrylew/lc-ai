#include <catch2/catch_test_macros.hpp>

#include <vector>

static std::vector<int> twoSumFA(const std::vector<int>& numbers, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/79
    //!          /sorting-and-searching/2994/

    //! @todo
}

TEST_CASE("Example 1", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 2};
    const std::vector<int> numbers {2, 7, 11, 15};
    constexpr int          target {9};

    REQUIRE(expected_output == twoSumFA(numbers, target));
}

TEST_CASE("Example 2", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 3};
    const std::vector<int> numbers {2, 3, 4};
    constexpr int          target {6};

    REQUIRE(expected_output == twoSumFA(numbers, target));
}

TEST_CASE("Example 3", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 2};
    const std::vector<int> numbers {-1, 0};
    constexpr int          target {-1};

    REQUIRE(expected_output == twoSumFA(numbers, target));
}
