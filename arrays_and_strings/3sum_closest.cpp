#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

static int threeSumClosestFA(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2967/

    auto sorted_nums = nums;
    std::ranges::sort(sorted_nums);

    const auto nums_size = static_cast<int>(std::ssize(nums));

    int three_sum_closest {};

    int right_idx {nums_size - 1};
    for (int curr_idx = 0; curr_idx < nums_size; ++curr_idx)
    {
        if (curr_idx >= right_idx)
        {
            break;
        }

        const int curr_num {sorted_nums.at(curr_idx)};
        const int right_num {sorted_nums.at(right_idx)};

        //! @todo
    }

    return three_sum_closest;
}

TEST_CASE("Example 1", "[threeSumClosest]")
{
    const std::vector<int> nums {-1, 2, 1, -4};
    constexpr int          target {1};

    REQUIRE(2 == threeSumClosestFA(nums, target));
}

TEST_CASE("Example 2", "[threeSumClosest]")
{
    const std::vector<int> nums {0, 0, 0};
    constexpr int          target {1};

    REQUIRE(0 == threeSumClosestFA(nums, target));
}
