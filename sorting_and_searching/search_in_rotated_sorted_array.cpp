#include <catch2/catch_test_macros.hpp>

#include <vector>

static int searchFA(const std::vector<int>& nums, int target)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/79
    //!          /sorting-and-searching/2992/
    //!
    //!          Time limit exceeded for Example 1.

    const int start_value_of_nums_k_to_n_1 {nums.front()};
    const int end_value_of_nums_0_to_k_1 {nums.back()};

    if (target > end_value_of_nums_0_to_k_1
        && target < start_value_of_nums_k_to_n_1)
    {
        return -1;
    }

    const auto nums_size = static_cast<int>(std::ssize(nums));

    if (nums_size == 1)
    {
        return target == nums[0] ? 0 : -1;
    }

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

        if (rotation_idx == -1)
        {
            if (target < nums[mid])
            {
                hi = mid - 1;
            }
            else if (target > nums[mid])
            {
                lo = mid + 1;
            }
            else
            {
                return mid;
            }
        }
        else
        {
            if (target < nums[rotation_idx] || target > nums[rotation_idx - 1])
            {
                //! target is smaller than smallest or larger than largest
                return -1;
            }

            if (target >= start_value_of_nums_k_to_n_1)
            {
                //! Search indices [start_value_of_nums_k_to_n_1, rotation_idx)

                if (target <= nums[rotation_idx - 1])
                {
                    hi = rotation_idx - 1;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                //! Search indices [rotation_idx, end_value_of_nums_0_to_k_1]

                if (target >= nums[rotation_idx])
                {
                    lo = rotation_idx;
                }
                else
                {
                    return -1;
                }
            }
        }
    }

    return lo;
}

static int searchDS1(const std::vector<int>& nums, int target)
{
    //! @details leetcode.com/problems/search-in-rotated-sorted-array/editorial
    //!
    //!          Time complexity O(log N) where N = nums.size(). The algorithm
    //!          requires one binary search to find the pivot element and at
    //!          most 2 binary searches to find target. Each binary search takes
    //!          O(log N).
    //!          Space complexity O(1) for left, right, and mid.

    const auto nums_size = static_cast<int>(std::ssize(nums));
    int        left {};
    int        right {nums_size - 1};

    //! Find the index of the pivot element (smallest element)
    while (left <= right)
    {
        const int mid {left + (right - left) / 2};
        if (nums[mid] > nums[nums_size - 1])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    //! Binary search over the inclusive range [left_bound, right_bound]
    const auto binary_search = [&](int left_bound, int right_bound) {
        int left_idx {left_bound};
        int right_idx {right_bound};

        while (left_idx <= right_idx)
        {
            const int mid_idx {left_idx + (right_idx - left_idx) / 2};
            if (nums[mid_idx] == target)
            {
                return mid_idx;
            }

            if (nums[mid_idx] > target)
            {
                right_idx = mid_idx - 1;
            }
            else
            {
                left_idx = mid_idx + 1;
            }
        }

        return -1;
    };

    //! Binary search over elements on the pivot element's left
    const int target_idx {binary_search(0, left - 1)};
    if (target_idx != -1)
    {
        return target_idx;
    }

    //! Binary search over elements on the pivot element's right
    return binary_search(left, nums_size - 1);
}

static int searchDS2(const std::vector<int>& nums, int target)
{
    //! @details leetcode.com/problems/search-in-rotated-sorted-array/editorial
    //!
    //!          Time complexity O(log N) where N = nums.size(). The algorithm
    //!          requires one binary search to locate pivot and one binary
    //!          search over the shifted indices to find target.
    //!          Space complexity O(1).

    const auto nums_size = static_cast<int>(std::ssize(nums));
    int        left {};
    int        right {nums_size - 1};

    //! Find the index of the pivot (smallest) element
    while (left <= right)
    {
        const int mid {left + (right - left) / 2};
        if (nums[mid] > nums[nums_size - 1])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    //! Shift elements in a circular manner, with the pivot element at index 0.
    //! Then perform a regular binary search.
    const auto shifted_binary_search = [&](int pivot) -> int {
        const int shift {nums_size - pivot};

        //! Boundaries of the sorted search space
        int sorted_left {(pivot + shift) % nums_size};
        int sorted_right {(pivot + shift - 1) % nums_size};

        while (sorted_left <= sorted_right)
        {
            const int sorted_mid {
                sorted_left + (sorted_right - sorted_left) / 2};

            //! We had to shift every element to the right by nums_size - pivot
            //! steps to get the sorted version of nums. Now we need to shift
            //! the index in the sorted nums to the left by nums_size - pivot to
            //! find the corresponding index in the original nums. i.e.,
            //!   orig_mid = sorted_mid - (nums_size - pivot)
            //!            = sorted_mid - shift (then incorporate modulus)
            const int orig_mid {(sorted_mid - shift + nums_size) % nums_size};

            if (nums[orig_mid] == target)
            {
                return orig_mid;
            }

            if (nums[orig_mid] > target)
            {
                sorted_right = sorted_mid - 1;
            }
            else
            {
                sorted_left = sorted_mid + 1;
            }
        }

        return -1;
    };

    return shifted_binary_search(left);
}

static int searchDS3(const std::vector<int>& nums, int target)
{
    //! @details leetcode.com/problems/search-in-rotated-sorted-array/editorial

    const auto nums_size = static_cast<int>(std::ssize(nums));
    int        left {};
    int        right {nums_size - 1};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};
        if (nums[mid] == target)
        {
            //! Case 1: Found target
            return mid;
        }

        //! Case 2: Subarray on mid's left is sorted
        if (nums[mid] >= nums[left])
        {
            if (target >= nums[left] && target < nums[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        //! Case 3: Subarray on mid's right is sorted
        else
        {
            if (target <= nums[right] && target > nums[mid])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }

    return -1;
}

TEST_CASE("Example 1", "[search]")
{
    const std::vector<int> nums {4, 5, 6, 7, 0, 1, 2};
    constexpr int          target {};
    REQUIRE(4 == searchFA(nums, target));
    REQUIRE(4 == searchDS1(nums, target));
    REQUIRE(4 == searchDS2(nums, target));
    REQUIRE(4 == searchDS3(nums, target));
}

TEST_CASE("Example 2", "[search]")
{
    const std::vector<int> nums {4, 5, 6, 7, 0, 1, 2};
    constexpr int          target {3};
    REQUIRE(-1 == searchFA(nums, target));
    REQUIRE(-1 == searchDS1(nums, target));
    REQUIRE(-1 == searchDS2(nums, target));
    REQUIRE(-1 == searchDS3(nums, target));
}

TEST_CASE("Example 3", "[search]")
{
    const std::vector<int> nums {1};
    constexpr int          target {};
    REQUIRE(-1 == searchFA(nums, target));
    REQUIRE(-1 == searchDS1(nums, target));
    REQUIRE(-1 == searchDS2(nums, target));
    REQUIRE(-1 == searchDS3(nums, target));
}
