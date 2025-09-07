#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <string>
#include <unordered_map>

static int lengthOfLongestSubstringFA(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2961/
    //!
    //!          Time complexity O(N) where N = s.size()
    //!          Space complexity O(N) for char_idxs map in the worst case when
    //!          s only contains unique chars.

    if (s.empty())
    {
        return 0;
    }

    int        longest_substr_len {};
    const auto s_size = static_cast<int>(std::ssize(s));

    //! Map of <char, index of char in s> for chars in current window
    std::unordered_map<char, int> char_idxs;

    int left_idx {};
    for (int right_idx = 0; right_idx < s_size; ++right_idx)
    {
        const char right_char {s[right_idx]};

        if (char_idxs.contains(right_char))
        {
            const int prev_right_char_idx {char_idxs[right_char]};

            for (int remove_idx = left_idx;
                 remove_idx <= prev_right_char_idx;
                 ++remove_idx)
            {
                char_idxs.erase(s[remove_idx]);
            }

            left_idx              = prev_right_char_idx + 1;
            char_idxs[right_char] = right_idx;
            continue;
        }

        char_idxs[right_char] = right_idx;

        longest_substr_len = std::max(longest_substr_len,
                                      right_idx - left_idx + 1);
    }

    return longest_substr_len;
}

TEST_CASE("Example 1", "[lengthOfLongestSubstring]")
{
    REQUIRE(3 == lengthOfLongestSubstringFA("abcabcbb"));
}

TEST_CASE("Example 2", "[lengthOfLongestSubstring]")
{
    REQUIRE(1 == lengthOfLongestSubstringFA("bbbbb"));
}

TEST_CASE("Example 3", "[lengthOfLongestSubstring]")
{
    REQUIRE(3 == lengthOfLongestSubstringFA("pwwkew"));
}
