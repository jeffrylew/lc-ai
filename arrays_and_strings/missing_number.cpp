#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <numeric>
#include <unordered_set>
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
    //! @details https://leetcode.com/problems/missing-number/editorial/
    //!
    //!          Time complexity O(N * log N) where N = nums.size(). The main
    //!          for loop runs in O(N) and std::ranges::sort takes O(N * log N).
    //!          Space complexity O(N) for the sorted_nums copy.

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

static int missingNumberDS2(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/problems/missing-number/editorial/
    //!
    //!          Time complexity O(N) where N = nums.size(). The main loop runs
    //!          in O(N) and creating nums_set takes O(N).
    //!          Space complexity O(N). nums contains N - 1 distinct elements so
    //!          nums_set requires O(N).

    std::unordered_set<int> nums_set(nums.begin(), nums.end());

    const auto expected_num_count = static_cast<int>(std::ssize(nums)) + 1;

    for (int num = 0; num < expected_num_count; ++num)
    {
        if (!nums_set.contains(num))
        {
            return num;
        }
    }

    return -1;
}

static int missingNumberDS3(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/problems/missing-number/editorial/

    const auto nums_size = static_cast<int>(std::ssize(nums));
    int        missing_num {nums_size};

    for (int idx = 0; idx < nums_size; ++idx)
    {
        missing_num ^= idx ^ nums[idx];
    }

    return missing_num;
}

TEST_CASE("Example 1", "[missingNumber]")
{
    const std::vector<int> nums {3, 0, 1};

    REQUIRE(2 == missingNumberFA(nums));
    REQUIRE(2 == missingNumberDS1(nums));
    REQUIRE(2 == missingNumberDS2(nums));
    REQUIRE(2 == missingNumberDS3(nums));
}

TEST_CASE("Example 2", "[missingNumber]")
{
    const std::vector<int> nums {0, 1};

    REQUIRE(2 == missingNumberFA(nums));
    REQUIRE(2 == missingNumberDS1(nums));
    REQUIRE(2 == missingNumberDS2(nums));
    REQUIRE(2 == missingNumberDS3(nums));
}

TEST_CASE("Example 3", "[missingNumber]")
{
    const std::vector<int> nums {9, 6, 4, 2, 3, 5, 7, 0, 1};

    REQUIRE(8 == missingNumberFA(nums));
    REQUIRE(8 == missingNumberDS1(nums));
    REQUIRE(8 == missingNumberDS2(nums));
    REQUIRE(8 == missingNumberDS3(nums));
}
