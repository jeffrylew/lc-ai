#include <catch2/catch_test_macros.hpp>

#include <string>
#include <unordered_map>

//! @brief Get total substrings of s where at least one char appears >= k times
//! @param[in] s String to get substrings from
//! @param[in] k At least one character in substring appears at least k times
//! @return Total number of substrings
static int numberOfSubstringsDS1(std::string s, int k)
{
    //! @details https://leetcode.com/problems
    //!            /count-substrings-with-k-frequency-characters-i/description/
    //!          https://leetcode.com/problems
    //!            /count-substrings-with-k-frequency-characters-i/solutions
    //!            /5939809/easiest-solution-sliding-window-beats-9494/comments
    //!            /2695092/
    //!
    //!          Time complexity O(N) where N = s.size().
    //!          Space complexity O(1) since the max number of characters in
    //!          char_counts is 26.

    int num_substrings {};

    //! Map of <char, char count>
    std::unordered_map<char, int> char_counts;

    //! Keeps track of the number of substrings that are valid
    int left_idx {};

    for (const char curr_char : s)
    {
        ++char_counts[curr_char];

        while (char_counts[curr_char] == k)
        {
            --char_counts[s[left_idx]];
            ++left_idx;
        }

        num_substrings += left_idx;
    }

    return num_substrings;
}

//! @brief Get total substrings of s where at least one char appears >= k times
//! @param[in] s String to get substrings from
//! @param[in] k At least one character in substring appears at least k times
//! @return Total number of substrings
static int numberOfSubstringsDS2(std::string s, int k)
{
    //! @details https://leetcode.com/problems
    //!            /count-substrings-with-k-frequency-characters-i/description/
    //!          https://leetcode.com/problems
    //!            /count-substrings-with-k-frequency-characters-i/solutions
    //!            /5939947/javacpython-sliding-window-on-by-lee215-91da/
    //!
    //!          Time complexity O(N) where N = s.size().
    //!          Space complexity O(1).

    const auto num_chars = static_cast<int>(std::ssize(s));

    //! There are (N + 1) * N / 2 substrings in total
    int num_substrings {(num_chars + 1) * num_chars / 2};

    std::unordered_map<char, int> char_counts {};

    int left_idx {};
    for (int right_idx = 0; right_idx < num_substrings; ++right_idx)
    {
        ++char_counts[s[right_idx]];

        while (char_counts[s[right_idx]] >= k)
        {
            --char_counts[s[left_idx]];
            ++left_idx;
        }

        num_substrings -= (right_idx - left_idx + 1);
    }

    return num_substrings;
}

TEST_CASE("Example 1", "[numberOfSubstrings]")
{
    //! Valid substrings are
    //! - "aba" ('a' appears 2 times)
    //! - "abac" ('a' appears 2 times)
    //! - "abacb" ('a' appears 2 times)
    //! - "bacb" ('b' appears 2 times)
    REQUIRE(4 == numberOfSubstringsDS1("abacb", 2));
    REQUIRE(4 == numberOfSubstringsDS2("abacb", 2));
}

TEST_CASE("Example 2", "[numberOfSubstrings]")
{
    //! All substrings are valid because every character appears at least once
    REQUIRE(15 == numberOfSubstringsDS1("abcde", 1));
    REQUIRE(15 == numberOfSubstringsDS2("abcde", 1));
}
