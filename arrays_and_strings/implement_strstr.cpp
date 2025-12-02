#include <catch2/catch_test_macros.hpp>

#include <string>

static int strStrFA(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2968/
    //!
    //!          Time complexity O(H) where H = haystack.size()
    //!          Space complexity O(1)

    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    const auto needle_size   = static_cast<int>(std::ssize(needle));

    for (int haystack_pos = 0; haystack_pos < haystack_size; ++haystack_pos)
    {
        if (haystack_size - haystack_pos < needle_size)
        {
            return -1;
        }

        if (haystack[haystack_pos] != needle.front())
        {
            continue;
        }

        int pos_offset {1};
        while (pos_offset < needle_size)
        {
            if (haystack[haystack_pos + pos_offset] != needle[pos_offset])
            {
                break;
            }

            ++pos_offset;
        }

        if (pos_offset == needle_size)
        {
            return haystack_pos;
        }
    }

    return -1;
}

static int strStrDS1(std::string haystack, std::string needle)
{
    //! @details https://leetcode.com/problems
    //!          /find-the-index-of-the-first-occurrence-in-a-string/editorial/
    //!
    //!          Time complexity O(H * N) where H = haystack.size() and
    //!          N = needle.size(). For every window_start, we may have to
    //!          iterate at most N times. There are H - N + 1 such window_starts
    //!          which gives O((H - N + 1) * N) or O(H * N).
    //!          Space complexity O(1).

    const auto haystack_size = static_cast<int>(std::ssize(haystack));
    const auto needle_size   = static_cast<int>(std::ssize(needle));

    for (int window_start = 0;
         window_start <= haystack_size - needle_size;
         ++window_start)
    {
        for (int window_idx = 0; window_idx < needle_size; ++window_idx)
        {
            if (needle[window_idx] != haystack[window_start + window_idx])
            {
                break;
            }

            if (window_idx == needle_size - 1)
            {
                return window_start;
            }
        }
    }

    return -1;
}

TEST_CASE("Example 1", "[strStr]")
{
    const std::string haystack {"sadbutsad"};
    const std::string needle {"sad"};

    REQUIRE(0 == strStrFA(haystack, needle));
    REQUIRE(0 == strStrDS1(haystack, needle));
}

TEST_CASE("Example 2", "[strStr]")
{
    const std::string haystack {"leetcode"};
    const std::string needle {"leeto"};

    REQUIRE(-1 == strStrFA(haystack, needle));
    REQUIRE(-1 == strStrDS1(haystack, needle));
}
