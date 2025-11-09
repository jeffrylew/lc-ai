#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

static std::vector<std::vector<int>> threeSumFA(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2966/
    //!
    //!          Time complexity O(N * log N) where N = nums.size()

    std::vector<std::vector<int>> three_sums;

    //! Map of <num, number of instances of num>
    std::unordered_map<int, int> num_count;
    for (const int num : nums)
    {
        ++num_count[num];
    }

    const auto nums_size   = static_cast<int>(std::ssize(nums));
    auto       sorted_nums = nums;
    std::sort(sorted_nums.begin(), sorted_nums.end());

    int left_idx {};
    int right_idx {nums_size - 1};

    while (left_idx < right_idx)
    {
        const int left_num {sorted_nums[left_idx]};
        const int right_num {sorted_nums[right_idx]};

        --num_count[left_num];
        --num_count[right_num];

        const int left_plus_right {left_num + right_num};
        const int target_num {left_plus_right == 0 ? 0 : -left_plus_right};

        if (num_count.contains(target_num) && num_count[target_num] > 0)
        {
            std::vector<int> three_sum {left_num, target_num, right_num};
            if (three_sums.empty() || three_sums.back() != three_sum)
            {
                three_sums.push_back(std::move(three_sum));
            }

            ++left_idx;
            --right_idx;
        }
        else if (target_num >= 0)
        {
            ++left_idx;
        }
        else
        {
            --right_idx;
        }

        ++num_count[left_num];
        ++num_count[right_num];
    }

    return three_sums;
}

TEST_CASE("Example 1", "[threeSum]")
{
    // indices:      0   1   2  3  4  5
    // sorted_nums: -4, -1, -1, 0, 1, 2
    //
    // num: count
    // -4: 1
    // -1: 2
    //  0: 1
    //  1: 1
    //  2: 1
    //
    // l = -4, r = 2 -> target: 2                 -> left_idx = 1, right_idx = 5
    // l = -1, r = 2 -> target: -1 -> {-1, -1, 2} -> left_idx = 2, right_idx = 4
    // l = -1, r = 1 -> target: 0  -> {-1,  0, 1} -> left_idx = 3, right_idx = 3
    const std::vector<int> nums {-1, 0, 1, 2, -1, -4};

    const std::vector<std::vector<int>> expected_output {
        {-1, -1, 2}, {-1, 0, 1}};

    REQUIRE(expected_output == threeSumFA(nums));
}

TEST_CASE("Example 2", "[threeSum]")
{
    // indices:     0  1  2
    // sorted_nums: 0, 1, 1
    //
    // num: count
    // 0: 1
    // 1: 2
    //
    // l = 0, r = 1 -> target: -1 -> left_idx = 0, right_idx = 1
    // l = 0, r = 1 -> target: -1 -> left_idx = 0, right_idx = 0
    const std::vector<int> nums {0, 1, 1};

    REQUIRE(threeSumFA(nums).empty());
}

TEST_CASE("Example 3", "[threeSum]")
{
    // indices:     0 1 2
    // sorted_nums: 0 0 0
    //
    // num: count
    // 0: 3
    //
    // l = 0, r = 0 -> target: 0 -> {0, 0, 0} -> left_idx = 1, right_idx = 1
    const std::vector<int> nums {0, 0, 0};

    const std::vector<std::vector<int>> expected_output {{0, 0, 0}};

    REQUIRE(expected_output == threeSumFA(nums))
}

TEST_CASE("Example 4", "[threeSum]")
{
    const std::vector<int> nums {0, 0, 0, 0};

    const std::vector<std::vector<int>> expected_output {{0, 0, 0}};

    REQUIRE(expected_output == threeSumFA(nums));
}

TEST_CASE("Example 5", "[threeSum]")
{
    const std::vector<int> nums {1, -1, -1, 0};

    const std::vector<std::vector<int>> expected_output {{-1, 0, 1}};

    REQUIRE(expected_output == threeSumFA(nums));
}
