#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <queue>
#include <random>
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

static int findKthLargestDS1(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/kth-largest-element-in-an-array
    //!
    //!          Time complexity O(N * log k) where N = nums.size(). Operations
    //!          on a heap cost logarithmic time relative to its size. Our heap
    //!          is limited to a size of k so operations cost at most O(log k).
    //!          We iterate over nums, performing one or two heap operations in
    //!          each iteration.
    //!          Space complexity O(k) for min_heap.

    std::priority_queue<int,
                        std::vector<int>,
                        std::greater<int>> min_heap;

    for (const int num : nums)
    {
        min_heap.push(num);

        if (std::ssize(min_heap) > k)
        {
            min_heap.pop();
        }
    }

    return min_heap.top()
}

//! @brief Get kth greatest element in nums
[[nodiscard]] static int quickselect(const std::vector<int>& nums, int k)
{
    const auto nums_size = static_cast<int>(std::ssize(nums));

    //! Obtain a random number from hardware
    std::random_device rd;

    //! Seed the engine
    std::mt19937 gen(rd());

    //! Create a uniform int distribution
    std::uniform_int_distribution<> distrib(0, nums_size - 1);

    const int pivot {distrib(gen)};

    std::vector<int> left;
    std::vector<int> mid;
    std::vector<int> right;

    for (const int num : nums)
    {
        if (num > pivot)
        {
            left.push_back(num);
        }
        else if (num < pivot)
        {
            right.push_back(num);
        }
        else
        {
            mid.push_back(num);
        }
    }

    const auto left_size = static_cast<int>(std::ssize(left));
    if (left_size >= k)
    {
        return quickselect(left, k);
    }

    const auto left_mid_size = left_size + static_cast<int>(std::ssize(mid));
    if (left_mid_size < k)
    {
        return quickselect(right, k - left_mid_size);
    }

    return pivot;
}

static int findKthLargestDS2(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/kth-largest-element-in-an-array
    //!
    //!          Time complexity O(N) on average, O(N ^ 2) in the worst case
    //!          where N = nums.size(). Each call we make to quickSelect will
    //!          cost O(N) since we need to iterate over nums to create left,
    //!          mid, and right. The number of times we call quickSelect depends
    //!          on how the pivot is chosen. The worst pivots to select are the
    //!          smallest and largest ones because they reduce the search space
    //!          by the least amount. The algorithm has a linear runtime since
    //!          the probability of needing to call quickselect O(N) times is so
    //!          low that we can ignore it.
    //!          Space complexity O(N) to create left, mid, and right.

    return quickselect(nums, k);
}

TEST_CASE("Example 1", "[findKthLargest]")
{
    const std::vector<int> nums {3, 2, 1, 5, 6, 4};
    constexpr int          k {2};

    REQUIRE(5 == findKthLargestFA(nums, k));
    REQUIRE(5 == findKthLargestDS1(nums, k));
    REQUIRE(5 == findKthLargestDS2(nums, k));
}

TEST_CASE("Example 2", "[findKthLargest]")
{
    const std::vector<int> nums {3, 2, 3, 1, 2, 4, 5, 5, 6};
    constexpr int          k {4};

    REQUIRE(4 == findKthLargestFA(nums, k));
    REQUIRE(4 == findKthLargestDS1(nums, k));
    REQUIRE(4 == findKthLargestDS2(nums, k));
}
