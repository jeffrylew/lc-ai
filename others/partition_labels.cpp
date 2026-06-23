#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

static std::vector<int> partitionLabelsDS1(std::string s)
{
    //! @details leetcode.com/explore/interview/card/amazon/82/others/3004
    //!          https://leetcode.com/problems/partition-labels/editorial/
    //!
    //!          Time complexity O(N) where N = s.size(). The algorithm iterates
    //!          through s twice. The first loop takes O(N) to store the index
    //!          of the last occurrence of each character in the last_occurrence
    //!          array. The second loop determines the partitions in O(N) by
    //!          tracking the end of each partition.
    //!          Space complexity O(K) where K = number of unique characters in
    //!          s. The algorithm uses a fixed-size array, last_occurrence, of
    //!          size 26 to store the last occurrence of each lowercase English
    //!          letter. In the general case, the space required is proportional
    //!          to the number of distinct letters in s. Thus, for an arbitrary
    //!          alphabet of size K, the space complexity is O(K).

    const auto s_size = static_cast<int>(std::ssize(s));

    //! Store the last index of each char in s
    std::array<int, 26U> last_occurrence {};
    for (int idx = 0; idx < s_size; ++idx)
    {
        last_occurrence[s[idx] - 'a'] = idx;
    }

    //! partition_start: Marks where current partition begins
    //! partition_end: Tracks the farthest point to reach for current partition
    int              partition_start {};
    int              partition_end {};
    std::vector<int> partition_sizes;

    for (int idx = 0; idx < s_size; ++idx)
    {
        partition_end = std::max(partition_end, last_occurrence[s[idx] - 'a']);

        //! End of the current partition
        if (idx == partition_end)
        {
            partition_sizes.push_back(idx - partition_start + 1);
            partition_start = idx + 1;
        }
    }

    return partition_sizes;
}

TEST_CASE("Example 1", "[partitionLabels]")
{
    const std::string      s {"ababcbacadefegdehijhklij"};
    const std::vector<int> expected_output {9, 7, 8};

    REQUIRE(expected_output == partitionLabelsDS1(s));
}

TEST_CASE("Example 2", "[partitionLabels]")
{
    const std::string      s {"eccbbbbdec"};
    const std::vector<int> expected_output {10};

    REQUIRE(expected_output == partitionLabelsDS1(s));
}

TEST_CASE("Example 3", "[partitionLabels]")
{
    //! Partitions:
    //! - "bob"
    //! - "h"
    //! - "a"
    //! - "s"
    //! - "peppe"
    //! - "r"
    //!               Indices: 012345678901
    const std::string      s {"bobhaspepper"};
    const std::vector<int> expected_output {3, 1, 1, 1, 5, 1};

    REQUIRE(expected_output == partitionLabelsDS1(s));
}
