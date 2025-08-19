#include <catch2/catch_test_macros.hpp>

#include <unordered_map>
#include <vector>

//! @brief First attempt to get indices of two numbers that add up to target
//! @param[in] nums   Reference to vector of integers
//! @param[in] target Target sum of two numbers
//! @return Vector of indices of two numbers that add up to target
static std::vector<int> twoSumFA(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/508/
    //!
    //!          Time complexity O(N) where N = nums.size().
    //!          Space complexity O(N) in the worst case where N - 1 numbers
    //!          need to be stored in the num_indices map.

    //! Map of <number, index>
    std::unordered_map<int, int> num_indices;
    num_indices.reserve(nums.size());

    for (int idx = 0; idx < std::ssize(nums); ++idx)
    {
        const int curr_number {nums[idx]};
        const int complement {target - curr_number};

        if (num_indices.contains(complement))
        {
            return {num_indices[complement], idx};
        }

        num_indices[curr_number] = idx;
    }

    return {-1, -1};
}

//! @brief Brute force discussion solution
//! @param[in] nums   Reference to vector of integers
//! @param[in] target Target sum of two numbers
//! @return Vector of indices of two numbers that add up to target
static std::vector<int> twoSumDS1(const std::vector<int>& nums, int target)
{
    for (int num1_idx = 0; num1_idx < std::ssize(nums); ++num1_idx)
    {
        for (int num2_idx = num1_idx + 1;
             num2_idx < std::ssize(nums);
             ++num2_idx)
        {
            if (nums[num2_idx] == target - nums[num1_idx])
            {
                return {num1_idx, num2_idx};
            }
        }
    }

    return {};
}

//! @brief Two-pass hash table discussion solution
//! @param[in] nums   Reference to vector of integers
//! @param[in] target Target sum of two numbers
//! @return Vector of indices of two numbers that add up to target
static std::vector<int> twoSumDS2(const std::vector<int>& nums, int target)
{
    std::unordered_map<int, int> num_idxs;

    for (int idx = 0; idx < std::ssize(nums); ++idx)
    {
        num_idxs[nums[idx]] = idx;
    }

    for (int idx = 0; idx < std::ssize(nums); ++idx)
    {
        const int complement {target - nums[idx]};

        if (num_idxs.contains(complement) && num_idx[complement] != idx)
        {
            return {idx, num_idxs[complement]};
        }
    }

    //! If no valid pair is found, return an empty vector
    return {};
}

TEST_CASE("Example 1", "[twoSum]")
{
    const std::vector<int> nums {2, 7, 11, 15};
    const std::vector<int> expected_output {0, 1};

    REQUIRE(expected_output == twoSumFA(nums, 9));
    REQUIRE(expected_output == twoSumDS1(nums, 9));
    REQUIRE(expected_output == twoSumDS2(nums, 9));
}

TEST_CASE("Example 2", "[twoSum]")
{
    const std::vector<int> nums {3, 2, 4};
    const std::vector<int> expected_output {1, 2};

    REQUIRE(expected_output == twoSumFA(nums, 6));
    REQUIRE(expected_output == twoSumDS1(nums, 6));
    REQUIRE(expected_output == twoSumDS2(nums, 6));
}

TEST_CASE("Example 3", "[twoSum]")
{
    const std::vector<int> nums {3, 3};
    const std::vector<int> expected_output {0, 1};

    REQUIRE(expected_output == twoSumFA(nums, 6));
    REQUIRE(expected_output == twoSumDS1(nums, 6));
    REQUIRE(expected_output == twoSumDS2(nums, 6));
}
