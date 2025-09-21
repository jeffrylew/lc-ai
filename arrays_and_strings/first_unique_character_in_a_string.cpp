#include <catch2/catch_test_macros.hpp>

#include <string>
#include <unordered_map>

static int firstUniqCharFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/480/
    //!
    //!          Time complexity O(N) where N = s.size(). Iterate twice through
    //!          s - once to get character counts and a second time to find the
    //!          first unique character if it exists.
    //!          Space complexity O(N) in the worst case when s only contains
    //!          unique characters.

    std::unordered_map<char, int> char_count;

    for (const char ch : s)
    {
        ++char_count[ch];
    }

    for (int idx = 0; idx < std::ssize(s); ++idx)
    {
        if (char_count[s[idx]] == 1)
        {
            return idx;
        }
    }

    return -1;
}

TEST_CASE("Example 1", "[firstUniqChar]")
{
    REQUIRE(0 == firstUniqCharFA("leetcode"));
}

TEST_CASE("Example 2", "[firstUniqChar]")
{
    REQUIRE(2 == firstUniqCharFA("loveleetcode"));
}

TEST_CASE("Example 3", "[firstUniqChar]")
{
    REQUIRE(-1 == firstUniqCharFA("aabb"));
}
