#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

static int missingNumberFA(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2971/
    //!
    //!          Time complexity O(N) where N = nums.size() for std::accumulate.
    //!          Space complexity O(1).

    const auto nums_size = static_cast<int>(std::ssize(nums));
    const int  expected_sum {nums_size * (nums_size + 1) / 2};

    return expected_sum - std::accumulate(nums.begin(), nums.end(), 0);
}

static int missingNumberDS1(const std::vector<int>& nums)
{
    auto sorted_nums = nums;
    std::ranges::sort(sorted_nums);

    const auto nums_size = static_cast<int>(std::ssize(sorted_nums));

    if (sorted_nums.back() != nums_size)
    {
        //! Ensure that n is at the last index
        return nums_size;
    }
    else if (sorted_nums.front() != 0)
    {
        //! Ensure that 0 is at the first index
        return 0;
    }

    for (int idx = 1; idx < nums_size; ++idx)
    {
        const int expected_num {sorted_nums[idx - 1] + 1};

        if (sorted_nums[idx] != expected_num)
        {
            return expected_num;
        }
    }

    //! Vector was not missing any numbers
    return -1;
}

TEST_CASE("Example 1", "[missingNumber]")
{
    const std::vector<int> nums {3, 0, 1};

    REQUIRE(2 == missingNumberFA(nums));
    REQUIRE(2 == missingNumberDS1(nums));
}

TEST_CASE("Example 2", "[missingNumber]")
{
    const std::vector<int> nums {0, 1};

    REQUIRE(2 == missingNumberFA(nums));
    REQUIRE(2 == missingNumberDS1(nums));
}

TEST_CASE("Example 3", "[missingNumber]")
{
    const std::vector<int> nums {9, 6, 4, 2, 3, 5, 7, 0, 1};

    REQUIRE(8 == missingNumberFA(nums));
    REQUIRE(8 == missingNumberDS1(nums));
}
