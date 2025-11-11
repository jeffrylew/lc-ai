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
    //!          First attempt solution does not pass Example 6.
    //!
    //!          Time complexity O(N * log N) where N = nums.size(). Need to
    //!          sort nums, which takes O(N * log N).
    //!          Space complexity O(N) for num_count map.
    //!          std::sort uses O(log N).

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
            if (target_num > right_num)
            {
                std::swap(three_sum[1], three_sum[2]);
            }

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

static void two_sum_II_DS1(const std::vector<int>&        nums,
                           int                            nums_size,
                           int                            curr_idx,
                           std::vector<std::vector<int>>& three_sums)
{
    int left_idx {curr_idx + 1};
    int right_idx {nums_size - 1};

    while (left_idx < right_idx)
    {
        const int three_sum {
            nums.at(curr_idx) + nums.at(left_idx) + nums.at(right_idx)};

        if (three_sum < 0)
        {
            ++left_idx;
        }
        else if (three_sum > 0)
        {
            --right_idx;
        }
        else
        {
            three_sums.push_back({
                nums.at(curr_idx), nums.at(left_idx), nums.at(right_idx)});

            ++left_idx;
            --right_idx;

            //! Increment left_idx to avoid duplicates
            while (left_idx < right_idx
                   && nums.at(left_idx - 1) == nums.at(left_idx))
            {
                ++left_idx;
            }
        }
    }
}

static std::vector<std::vector<int>> threeSumDS1(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/problems/3sum/editorial/

    const auto nums_size   = static_cast<int>(std::ssize(nums));
    auto       sorted_nums = nums;
    std::sort(sorted_nums.begin(), sorted_nums.end());

    std::vector<std::vector<int>> three_sums;

    for (int curr_idx = 0;
         curr_idx < nums_size && nums.at(curr_idx) <= 0;
         ++curr_idx)
    {
        if (curr_idx == 0 || nums.at(curr_idx - 1) != nums.at(curr_idx))
        {
            two_sum_II_DS1(nums, nums_size, curr_idx, three_sums);
        }
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
    REQUIRE(expected_output == threeSumDS1(nums));
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
    REQUIRE(threeSumDS1(nums).empty());
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
    REQUIRE(expected_output == threeSumDS1(nums))
}

TEST_CASE("Example 4", "[threeSum]")
{
    const std::vector<int> nums {0, 0, 0, 0};

    const std::vector<std::vector<int>> expected_output {{0, 0, 0}};

    REQUIRE(expected_output == threeSumFA(nums));
    REQUIRE(expected_output == threeSumDS1(nums));
}

TEST_CASE("Example 5", "[threeSum]")
{
    const std::vector<int> nums {1, -1, -1, 0};

    const std::vector<std::vector<int>> expected_output {{-1, 0, 1}};

    REQUIRE(expected_output == threeSumFA(nums));
    REQUIRE(expected_output == threeSumDS1(nums));
}

TEST_CASE("Example 6", "[threeSum]")
{
    const std::vector<int> nums {-2, 0, 1, 1, 2};

    const std::vector<std::vector<int>> expected_output {
        {-2, 0, 2}, {-2, 1, 1}};

    //! First attempt returns {{-2, 0, 2}}
    REQUIRE(expected_output != threeSumFA(nums));
    REQUIRE(expected_output == threeSumDS1(nums));
}
