#include <catch2/catch_test_macros.hpp>

#include <queue>
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

TEST_CASE("Example 1", "[topKFrequent]")
{
    const std::vector<int> nums {1, 1, 1, 2, 2, 3};
    constexpr int          k {2};
    const std::vector<int> expected_output {1, 2};

    REQUIRE(expected_output == topKFrequentFA(nums, k));
}

TEST_CASE("Example 2", "[topKFrequent]")
{
    const std::vector<int> nums {1};
    constexpr int          k {1};
    const std::vector<int> expected_output {1};

    REQUIRE(expected_output == topKFrequentFA(nums, k));
}
