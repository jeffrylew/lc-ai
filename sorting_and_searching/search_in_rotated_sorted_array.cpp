#include <catch2/catch_test_macros.hpp>

#include <vector>

static int searchFA(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/79
    //!          /sorting-and-searching/2992/

    const int start_value_of_nums_k_to_n_1 {nums.front()};
    const int end_value_of_nums_0_to_k_1 {nums.back()};

    if (target > end_value_of_nums_0_to_k_1
        && target < start_value_of_nums_k_to_n_1)
    {
        return -1;
    }

    const auto nums_size = static_cast<int>(std::ssize(nums));

    int lo {};
    int hi {nums_size - 1};
    int rotation_idx {-1};

    while (lo < hi)
    {
        const int mid {lo + (hi - lo) / 2};

        if (rotation_idx == -1
            && mid + 1 < nums_size
            && mid - 1 >= 0)
        {
            if (nums[mid] < nums[mid - 1] && nums[mid] < nums[mid + 1])
            {
                rotation_idx = mid;
            }
            else if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
            {
                rotation_idx = mid + 1;
            }
        }

        //! @todo
    }
}

TEST_CASE("Example 1", "[search]")
{
    const std::vector<int> nums {4, 5, 6, 7, 0, 1, 2};
    constexpr int          target {};
    REQUIRE(4 == searchFA(nums, target));
}

TEST_CASE("Example 2", "[search]")
{
    const std::vector<int> nums {4, 5, 6, 7, 0, 1, 2};
    constexpr int          target {3};
    REQUIRE(-1 == searchFA(nums, target));
}

TEST_CASE("Example 3", "[search]")
{
    const std::vector<int> nums {1};
    constexpr int          target {};
    REQUIRE(-1 == searchFA(nums, target));
}
