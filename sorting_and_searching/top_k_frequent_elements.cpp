#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <queue>
//#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>

//! @brief First attempt to get k most frequent elements
//! @param[in] nums Reference to vector of ints
//! @param[in] k    Number of most frequent elements to return
//! @return Vector of k most frequent elements
static std::vector<int> topKFrequentFA(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/79
    //!          /sorting-and-searching/2995/
    //!
    //!          Time complexity O(N * log N). It takes O(N) to get element
    //!          counts. In the worst case of all unique elements, constructing
    //!          the min heap takes O(N). Then popping all unique elements from
    //!          the min heap to get the top k elements takes O(N * log N).
    //!          Space complexity O(N) for num_counts and min_count_heap. The
    //!          output top_k_elements is excluded from the complexity analysis.

    //! Map of <element, element count>
    std::unordered_map<int, int> num_counts;
    for (const int num : nums)
    {
        ++num_counts[num];
    }

    const auto num_unique_elements = static_cast<int>(std::ssize(num_counts));

    using Elem_count_t = std::pair<int, int>;

    auto min_count_compare =
        [](const Elem_count_t& lhs, const Elem_count_t& rhs) {
            return lhs.second > rhs.second;
        };

    //! Min heap of <element, element count> sorted by element count
    std::priority_queue<Elem_count_t,
                        std::vector<Elem_count_t>,
                        decltype(min_count_compare)> min_count_heap(
                            num_counts.begin(),
                            num_counts.end(),
                            min_count_compare);

    int excess_elements {num_unique_elements - k};
    while (excess_elements > 0)
    {
        min_count_heap.pop();
        --excess_elements;
    }

    std::vector<int> top_k_elements;
    top_k_elements.reserve(k);

    while (!min_count_heap.empty())
    {
        top_k_elements.push_back(min_count_heap.top().first);
        min_count_heap.pop();
    }

    return top_k_elements;
}

//! @brief Heap discussion solution to get k most frequent elements
//! @param[in] nums Reference to vector of ints
//! @param[in] k    Number of most frequent elements to return
//! @return Vector of k most frequent elements
static std::vector<int> topKFrequentDS1(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/top-k-frequent-elements/editorial
    //!
    //!          Time complexity O(N + N * log k) where N = nums.size() for
    //!          k < N. If k = N then O(1).
    //!          Space complexity O(N + k) to store the hash map with no more
    //!          than N elements and the min heap with k elements.

    //! O(1) time
    if (k == std::ssize(nums))
    {
        return nums;
    }

    //! Build hash map of <element, element count> in O(N)
    std::unordered_map<int, int> num_counts;
    for (const int num : nums)
    {
        ++num_counts[num];
    }

    //! Initialize a heap with the least frequent elements at the top
    auto min_count_compare = [&num_counts](int lhs_elem, int rhs_elem) {
        return num_counts[lhs_elem] > num_counts[rhs_elem];
    };
    std::priority_queue<int,
                        std::vector<int>,
                        decltype(min_count_compare)> min_count_heap(
                            min_count_compare);

    //! Keep top k frequent elements in the min heap
    //! O(N * log k) < O(N * log N) time
    for (const auto& [element, element_count] : num_counts)
    {
        min_count_heap.push(element);

        if (std::ssize(min_count_heap) > k)
        {
            min_count_heap.pop();
        }
    }

    //! Build an output vector in O(k * log k) time
    std::vector<int> top_k_elements(k);
    for (int elem_idx = k - 1; elem_idx >= 0; --elem_idx)
    {
        top_k_elements[elem_idx] = min_count_heap.top();
        min_count_heap.pop();
    }

    return top_k_elements;
}

//! @brief Bucket sort discussion solution to get k most frequent elements
//! @param[in] nums Reference to vector of ints
//! @param[in] k    Number of most frequent elements to return
//! @return Vector of k most frequent elements
static std::vector<int> topKFrequentDS2(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/top-k-frequent-elements/editorial
    //!
    //!          Time complexity O(N) where N = nums.size().
    //!          Space complexity O(N).

    if (k == std::ssize(nums))
    {
        return nums;
    }

    //! Build hash map of <element, element count>
    std::unordered_map<int, int> num_counts;
    for (const int num : nums)
    {
        ++num_counts[num];
    }

    //! Create vector of buckets where each index is the element count and the
    //! corresponding bucket stores the elements. Could also use a
    //! map<element count, vector<element>> but insertions take O(N * log N) in
    //! the worst case of unique elements.
    std::vector<std::vector<int>> frequency_buckets(1U + nums.size());
    for (const auto& [element, element_count] : num_counts)
    {
        frequency_buckets[element_count].push_back(element);
    }

    std::vector<int> top_k_elements;
    top_k_elements.reserve(k);

    const auto num_buckets = static_cast<int>(std::ssize(frequency_buckets));

    for (int bucket = num_buckets - 1; bucket >= 0; --bucket)
    {
        auto& curr_bucket = frequency_buckets[bucket];

        if (curr_bucket.empty())
        {
            continue;
        }

        const int num_elements_to_add {
            std::min(k - static_cast<int>(std::ssize(top_k_elements)),
                     static_cast<int>(std::ssize(curr_bucket)))};
        if (num_elements_to_add == 0)
        {
            break;
        }

        //top_k_elements.append_range(
        //    std::ranges::subrange(curr_bucket.begin(),
        //                          curr_bucket.begin() + num_elements_to_add));

        top_k_elements.insert(
            top_k_elements.end(),
            curr_bucket.begin(),
            curr_bucket.begin() + num_elements_to_add);
    }

    return top_k_elements;
}

[[nodiscard]] static int partition(
    int                                 left_idx,
    int                                 right_idx,
    int                                 pivot_idx,
    std::vector<int>&                   unique_nums,
    const std::unordered_map<int, int>& count_map)
{
    const int pivot_frequency {count_map.at(unique_nums[pivot_idx])};

    //! 1. Move the pivot to the end
    std::swap(unique_nums[pivot_idx], unique_nums[right_idx]);

    //! 2. Move all less frequent elements to the left
    int store_idx {left_idx};
    for (int curr_idx = left; curr_idx <= right_idx; ++curr_idx)
    {
        if (count_map.at(unique_nums[curr_idx]) < pivot_frequency)
        {
            std::swap(unique_nums[store_idx], unique_nums[curr_idx]);
            ++store_idx;
        }
    }

    //! 3. Move the pivot to its final place
    std::swap(unique_nums[right_idx], unique_nums[store_idx]);

    return store_idx;

} // [[nodiscard]] static int partition( ...

static void quickselect(
    int                                 left_idx,
    int                                 right_idx,
    int                                 k_smallest,
    std::vector<int>&                   unique_nums,
    const std::unordered_map<int, int>& count_map)
{
    
}

//! @brief Quickselect discussion solution to get k most frequent elements
//! @param[in] nums Reference to vector of ints
//! @param[in] k    Number of most frequent elements to return
//! @return Vector of k most frequent elements
static std::vector<int> topKFrequentDS3(const std::vector<int>& nums, int k)
{
    //! @details https://leetcode.com/problems/top-k-frequent-elements/editorial

    //! Build hash map of <element, element count>
    std::unordered_map<int, int> count_map;
    for (const int num : nums)
    {
        ++count_map[num];
    }

    //! Vector of unique elements
    std::vector<int> unique_nums;
    unique_nums.reserve(count_map.size());
    for (const auto& [element, element_count] : count_map)
    {
        unique_nums.push_back(element);
    }

    const auto num_unique_elements = static_cast<int>(std::ssize(count_map));

    //! kth top frequent element is (N - k)th least frequent
    //! Do a partial sort: from least frequent to the most frequent until the
    //! (N - k)th least frequent element is correctly placed in a sorted vector
    //! at the N - k position.
    //! All elements on the left are less frequent.
    //! All elements on the right are more frequent.
    quickselect(0,
                num_unique_elements - 1,
                num_unique_elements - k,
                unique_nums,
                count_map);

    //! Return top k frequent elements
    std::vector<int> top_k_elements(k);
    std::move(unique_nums.begin() + num_unique_elements - k,
              unique_nums.end(),
              top_k_elements.begin());

    return top_k_elements;

} // static std::vector<int> topKFrequentDS3( ...

TEST_CASE("Example 1", "[topKFrequent]")
{
    const std::vector<int> nums {1, 1, 1, 2, 2, 3};
    constexpr int          k {2};
    const std::vector<int> expected_output {1, 2};

    REQUIRE(expected_output == topKFrequentFA(nums, k));
    REQUIRE(expected_output == topKFrequentDS1(nums, k));
    REQUIRE(expected_output == topKFrequentDS2(nums, k));
    REQUIRE(expected_output == topKFrequentDS3(nums, k));
}

TEST_CASE("Example 2", "[topKFrequent]")
{
    const std::vector<int> nums {1};
    constexpr int          k {1};
    const std::vector<int> expected_output {1};

    REQUIRE(expected_output == topKFrequentFA(nums, k));
    REQUIRE(expected_output == topKFrequentDS1(nums, k));
    REQUIRE(expected_output == topKFrequentDS2(nums, k));
    REQUIRE(expected_output == topKFrequentDS3(nums, k));
}
