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

// Skip brute force discussion solution DS1

static int lengthOfLongestSubstringDS2(std::string s)
{
    //! @details https://leetcode.com/problems
    //!          /longest-substring-without-repeating-characters/editorial
    //!
    //!          Time complexity O(N) where N = s.size(). In the worst case,
    //!          each character will be visited twice.
    //!          Space complexity O(min(N, S)) where S is the size of the
    //!          charset. We need O(K) space for checking if a substring has no
    //!          duplicate characters, where K = char_count.size(). The size of
    //!          char_count is upper bounded by the size N of the string and the
    //!          size S of the charset.

    std::unordered_map<char, int> char_count;

    int longest_substr_len {};
    int left_idx {};

    for (int right_idx = 0; right_idx < std::ssize(s); ++right_idx)
    {
        const char right_char {s[right_idx]};
        ++char_count[right_char];

        while (char_count[right_char] > 1)
        {
            const char left_char {s[left_idx]};
            --char_count[left_char];
            ++left_idx;
        }

        longest_substr_len =
            std::max(longest_substr_len, right_idx - left_idx + 1);
    }

    return longest_substr_len;
}

static int lengthOfLongestSubstringDS3(std::string s)
{
    //! @details https://leetcode.com/problems
    //!          /longest-substring-without-repeating-characters/editorial
    //!
    //!          Time complexity O(N) where N = s.size(). right_idx iterates N
    //!          times.
    //!          Space complexity O(min(N, S)) where S is the size of the
    //!          charset. We need O(K) space for checking if a substring has no
    //!          duplicate characters, where K = char_to_next_idx.size(). The
    //!          size of char_to_next_idx is upper bounded by the size N of the
    //!          string and the size S of the charset.

    std::unordered_map<char, int> char_to_next_idx;

    int longest_substr_len {};
    int left_idx {};

    for (int right_idx = 0; right_idx < std::ssize(s); ++right_idx)
    {
        const char right_char {s[right_idx]};

        if (char_to_next_idx.contains(right_char))
        {
            left_idx = std::max(left_idx, char_to_next_idx[right_char]);
        }

        longest_substr_len =
            std::max(longest_substr_len, right_idx - left_idx + 1);

        char_to_next_idx[right_char] = right_idx + 1;
    }

    return longest_substr_len;
}

TEST_CASE("Example 1", "[lengthOfLongestSubstring]")
{
    REQUIRE(3 == lengthOfLongestSubstringFA("abcabcbb"));
    REQUIRE(3 == lengthOfLongestSubstringDS2("abcabcbb"));
    REQUIRE(3 == lengthOfLongestSubstringDS3("abcabcbb"));
}

TEST_CASE("Example 2", "[lengthOfLongestSubstring]")
{
    REQUIRE(1 == lengthOfLongestSubstringFA("bbbbb"));
    REQUIRE(1 == lengthOfLongestSubstringDS2("bbbbb"));
    REQUIRE(1 == lengthOfLongestSubstringDS3("bbbbb"));
}

TEST_CASE("Example 3", "[lengthOfLongestSubstring]")
{
    REQUIRE(3 == lengthOfLongestSubstringFA("pwwkew"));
    REQUIRE(3 == lengthOfLongestSubstringDS2("pwwkew"));
    REQUIRE(3 == lengthOfLongestSubstringDS3("pwwkew"));
}
