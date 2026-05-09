#include <catch2/catch_test_macros.hpp>

#include <vector>

static std::vector<int> twoSumFA(const std::vector<int>& numbers, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/79
    //!          /sorting-and-searching/2994/
    //!
    //!          First attempt solution does not pass Example 4.

    const auto num_size = static_cast<int>(std::ssize(numbers));

    //! Find largest number less than target
    int left_max_idx {};
    int right_max_idx {num_size - 1};

    while (left_max_idx <= right_max_idx)
    {
        const int mid_max_idx {
            left_max_idx + (right_max_idx - left_max_idx) / 2};

        if (numbers[mid_max_idx] > target)
        {
            right_max_idx = mid_max_idx - 1;
        }
        else
        {
            left_max_idx = mid_max_idx + 1;
        }
    }

    //! right_max_idx is for the largest number less than or equal to target
    //! Now use two pointers to find indices of numbers that add to target
    int left_idx {};
    int right_idx {right_max_idx};
    if (left_idx == right_idx && right_idx < num_size - 1)
    {
        ++right_idx;
    }

    while (left_idx < right_idx)
    {
        const int curr_sum {numbers[left_idx] + numbers[right_idx]};

        if (curr_sum == target)
        {
            return {left_idx + 1, right_idx + 1};
        }
        else if (curr_sum < target)
        {
            ++left_idx;
        }
        else
        {
            --right_idx;
        }
    }

    //! Should not reach this point
    return {};
}

static std::vector<int> twoSumDS(const std::vector<int>& numbers, int target)
{
    //! @details https://leetcode.com/problems/two-sum-ii-input-array-is-sorted

    int low {};
    int high {static_cast<int>(std::ssize(numbers)) - 1};

    while (low < high)
    {
        const int sum {numbers[low] + numbers[high]};

        if (sum == target)
        {
            return {low + 1, high + 1};
        }

        if (sum < target)
        {
            ++low;
        }
        else
        {
            --high;
        }
    }

    //! In case there is no solution return {-1, -1}
    return {-1, -1};
}

TEST_CASE("Example 1", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 2};
    const std::vector<int> numbers {2, 7, 11, 15};
    constexpr int          target {9};

    REQUIRE(expected_output == twoSumFA(numbers, target));
    REQUIRE(expected_output == twoSumDS(numbers, target));
}

TEST_CASE("Example 2", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 3};
    const std::vector<int> numbers {2, 3, 4};
    constexpr int          target {6};

    REQUIRE(expected_output == twoSumFA(numbers, target));
    REQUIRE(expected_output == twoSumDS(numbers, target));
}

TEST_CASE("Example 3", "[twoSumII]")
{
    const std::vector<int> expected_output {1, 2};
    const std::vector<int> numbers {-1, 0};
    constexpr int          target {-1};

    REQUIRE(expected_output == twoSumFA(numbers, target));
    REQUIRE(expected_output == twoSumDS(numbers, target));
}

TEST_CASE("Example 4", "[twoSumII]")
{
    const std::vector<int> expected_output {2, 7};
    const std::vector<int> numbers {-5, -3, 0, 2, 4, 6, 8};
    constexpr int          target {5};

    REQUIRE_FALSE(expected_output == twoSumFA(numbers, target));
    REQUIRE_FALSE(expected_output == twoSumDS(numbers, target));
}
