#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <vector>

static int findKthLargestFA(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/kth-largest-element-in-an-array
    //!
    //!          Time complexity O(N + k * log N) where N = nums.size(). Need
    //!          O(N) to construct max_heap from nums and need O(k * log N) to
    //!          pop k - 1 elements.
    //!          Space complexity O(N) for max_heap.

    std::priority_queue<int> max_heap(nums.begin(), nums.end());

    while (!max_heap.empty() && k > 1)
    {
        max_heap.pop();
        --k;
    }

    return max_heap.top();
}

TEST_CASE("Example 1", "[findKthLargest]")
{
    const std::vector<int> nums {3, 2, 1, 5, 6, 4};
    constexpr int          k {2};

    REQUIRE(5 == findKthLargestFA(nums, k));
}

TEST_CASE("Example 2", "[findKthLargest]")
{
    const std::vector<int> nums {3, 2, 3, 1, 2, 4, 5, 5, 6};
    constexpr int          k {4};

    REQUIRE(4 == findKthLargestFA(nums, k));
}
