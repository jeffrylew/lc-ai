#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <limits>
#include <vector>

static int threeSumClosestDS1(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2967/

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
                nums.at(curr_idx) + nums.at(left_idx) + nums.at(right_idx)};

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

TEST_CASE("Example 1", "[threeSumClosest]")
{
    const std::vector<int> nums {-1, 2, 1, -4};
    constexpr int          target {1};

    REQUIRE(2 == threeSumClosestDS1(nums, target));
}

TEST_CASE("Example 2", "[threeSumClosest]")
{
    const std::vector<int> nums {0, 0, 0};
    constexpr int          target {1};

    REQUIRE(0 == threeSumClosestDS1(nums, target));
}
