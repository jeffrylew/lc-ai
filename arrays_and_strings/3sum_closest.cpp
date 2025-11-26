#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iterator>
#include <limits>
#include <vector>

static int threeSumClosestDS1(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2967/
    //!
    //!          Time complexity O(N ^ 2) where N = nums.size(). We have outer
    //!          and inner loops, each going through N elements. Sorting the
    //!          vector takes O(N * log N).
    //!          Space complexity O(log N) for std::sort

    int minimum_difference {std::numeric_limits<int>::max()};

    const auto nums_size   = static_cast<int>(std::ssize(nums));
    auto       sorted_nums = nums;
    std::ranges::sort(sorted_nums);

    for (int curr_idx = 0;
         curr_idx < nums_size && minimum_difference != 0;
         ++curr_idx)
    {
        int left_idx {curr_idx + 1};
        int right_idx {nums_size - 1};

        while (left_idx < right_idx)
        {
            const int three_sum {
                sorted_nums.at(curr_idx)
                + sorted_nums.at(left_idx)
                + sorted_nums.at(right_idx)};

            if (std::abs(target - three_sum) < std::abs(minimum_difference))
            {
                minimum_difference = target - three_sum;
            }

            if (three_sum < target)
            {
                ++left_idx;
            }
            else
            {
                --right_idx;
            }
        }
    }

    return target - minimum_difference;
}

static int threeSumClosestDS2(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/problems/3sum-closest/editorial/
    //!
    //!          Time complexity O(N ^ 2 * log N) where N = nums.size(). Binary
    //!          search takes O(log N) and we do it N times in the inner loop.
    //!          Since we go through N elements in the outer loop, the overall
    //!          complexity is O(N ^ 2 * log N).
    //!          Space complexity O(log N) for std::sort.

    int minimum_difference {std::numeric_limits<int>::max()};

    const auto nums_size   = static_cast<int>(std::ssize(nums));
    auto       sorted_nums = nums;
    std::ranges::sort(sorted_nums);

    for (int curr_idx = 0;
         curr_idx < nums_size && minimum_difference != 0;
         ++curr_idx)
    {
        for (int next_idx = curr_idx + 1; next_idx < nums_size - 1; ++next_idx)
        {
            const int complement {
                target - sorted_nums.at(curr_idx) - sorted_nums.at(next_idx)};

            auto complement_it =
                std::upper_bound(sorted_nums.begin() + next_idx + 1,
                                 sorted_nums.end(),
                                 complement);

            const auto hi_idx = static_cast<int>(
                std::distance(sorted_nums.begin(), complement_it));
            const int lo_idx {hi_idx - 1};

            if (hi_idx < nums_size
                && std::abs(complement - sorted_nums.at(hi_idx))
                    < std::abs(minimum_difference))
            {
                minimum_difference = complement - sorted_nums.at(hi_idx);
            }

            if (lo_idx < next_idx
                && std::abs(complement - sorted_nums.at(lo_idx))
                    < std::abs(minimum_difference))
            {
                minimum_difference = complement - sorted_nums.at(lo_idx);
            }
        }
    }

    return target - minimum_difference;
}

TEST_CASE("Example 1", "[threeSumClosest]")
{
    const std::vector<int> nums {-1, 2, 1, -4};
    constexpr int          target {1};

    REQUIRE(2 == threeSumClosestDS1(nums, target));
    REQUIRE(2 == threeSumClosestDS2(nums, target));
}

TEST_CASE("Example 2", "[threeSumClosest]")
{
    const std::vector<int> nums {0, 0, 0};
    constexpr int          target {1};

    REQUIRE(0 == threeSumClosestDS1(nums, target));
    REQUIRE(0 == threeSumClosestDS2(nums, target));
}
