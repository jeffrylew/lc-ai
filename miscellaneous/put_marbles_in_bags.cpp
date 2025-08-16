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

    //! Collect and sort the values of all (num_weights - 1) pairs
    //! Let N = num_weights below
    const auto num_weights = static_cast<int>(std::ssize(weights));

    //! paired_weights_sum indices are in [0, N - 2]
    std::vector<int> paired_weights_sum(num_weights - 1);

    for (int idx = 0; idx < num_weights - 1; ++idx)
    {
        paired_weights_sum[idx] = weights[idx] + weights[idx + 1];
    }

    std::sort(paired_weights_sum.begin(), paired_weights_sum.end());

    //! Get the difference between
    //! - the largest (k - 1) values from indices [(N - 2) - (k - 1) + 1] to
    //!   (N - 2) = (N - k) to (N - 2)
    //! - the smallest (k - 1) values from indices 0 to [(k - 1) - 1] = (k - 2)
    long long min_max_diff {};

    //! idx = 0:
    //!     paired_weights_sum[(N - 2) - 0] - paired_weights_sum[0]
    //!   = paired_weights_sum[N - 2] - paired_weights_sum[0]
    //! idx = k - 2:
    //!     paired_weights_sum[(N - 2) - (k - 2)] - paired_weights_sum[k - 2]
    //!   = paired_weights_sum[N - k] - paired_weights_sum[k - 2]
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
