#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

//! @brief Get difference between max and min scores among marble distributions
//! @param[in] weights Reference to vector of marble weights
//! @param[in] k       Number of bags to divide the marbles into
//! @return Difference between the max and min scores among marble distributions
static long long putMarblesDS(const std::vector<int>& weights, int k)
{
    //! @details https://leetcode.com/problems/put-marbles-in-bags/description/

    //! Collect and sort the value of all n - 1 pairs
    const auto num_weights = static_cast<int>(std::ssize(weights));

    std::vector<int> paired_weights_sum(num_weights - 1);

    for (int idx = 0; idx < num_weights - 1; ++idx)
    {
        paired_weights_sum[idx] += weights[idx] + weights[idx + 1];
    }

    std::sort(paired_weights_sum.begin(), paired_weights_sum.end());

    //! Get the difference between the largest k - 1 values
    //! and the smallest k - 1 values
    long long min_max_diff {};

    for (int idx = 0; idx < k - 1; ++idx)
    {
        min_max_diff +=
            paired_weights_sum[num_weights - 2 - idx] - paired_weights_sum[idx];
    }

    return min_max_diff;
}

TEST_CASE("Example 1", "[putMarbles]")
{
    const std::vector<int> weights {1, 3, 5, 1};
    constexpr int          k {2};

    //! Explanation:
    //! - Distribution [1], [3, 5, 1] results in min score of (1+1) + (3+1) = 6
    //! - Distribution [1, 3], [5, 1] results in max score of (1+3) + (5+1) = 10
    //! - Thus, return their difference 10 - 6 = 4.
    REQUIRE(4LL == putMarblesDS(weights, k));
}

TEST_CASE("Example 2", "[putMarbles]")
{
    const std::vector<int> weights {1, 3};
    constexpr int          k {2};

    //! Explanation:
    //! - The only distribution possible is [1], [3]
    //! - Since both the max and min scores are the same, return 0
    REQUIRE(0LL == putMarblesDS(weights, k));
}
