#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

static std::string minWindowFA(std::string s, std::string t)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/902/

    const auto s_size = static_cast<int>(std::ssize(s));
    const auto t_size = static_cast<int>(std::ssize(t));
    if (t_size > s_size)
    {
        return {};
    }

    std::unordered_map<char, int> t_char_count;
    for (const char ch : t)
    {
        ++t_char_count[ch];
    }

    std::string_view min_window_substrv {s};

    int left_pos {};
    for (int right_pos = 0; right_pos < s_size; ++right_pos)
    {
        std::string_view window_substrv {
            s.data() + left_pos, right_pos - left_pos};
        if (window_substrv.empty())
        {
            continue;
        }

        auto window_char_count = t_char_count;
        for (const char ch : window_substrv)
        {
            if (!window_char_count.contains(ch))
            {
                continue;
            }

            --window_char_count[ch];
            if (window_char_count[ch] == 0)
            {
                window_char_count.erase(ch);
            }
        }

        if (window_char_count.empty()
            && std::ssize(window_substrv) <= std::ssize(min_window_substrv))
        {
            min_window_substrv = window_substrv;
        }

        //! @todo Need loop where left_pos is incremented until condition met
    }

    return std::string {min_window_substrv};
}

static std::string minWindowDS1(std::string s, std::string t)
{
    //! @details leetcode.com/problems/minimum-window-substring/editorial
    //!
    //!          Time complexity O(S + T) where S = s.size() and T = t.size().
    //!          In the worst case, we might visit every element of s twice,
    //!          once by left_pos and once by right_pos.
    //!          Space complexity O(S + T), O(S) when the window size is equal
    //!          to s.size() and O(T) when t has all unique characters.

    if (s.empty() || t.empty())
    {
        return {};
    }

    //! Map counts all unique chars in t
    std::unordered_map<char, int> t_char_count;
    for (const char ch : t)
    {
        ++t_char_count[ch];
    }

    //! Number of unique chars in t that need to be present in the window
    const auto num_required_unique_chars =
        static_cast<int>(std::ssize(t_char_count));

    //! Tracks the number of unique chars from t that are
    //! in the current window with the desired frequency
    int num_unique_chars_in_window {};

    //! Map counts all unique chars in current window
    std::unordered_map<char, int> window_char_count;

    int min_window_size {-1};
    int min_window_left_pos {};
    int min_window_right_pos {};

    const auto s_size = static_cast<int>(std::ssize(s));
    int        left_pos {};

    for (int right_pos = 0; right_pos < s_size; ++right_pos)
    {
        const char right_char {s[right_pos]};
        ++window_char_count[right_char];

        //! If the current char frequency equals the desired count
        //! in t then increment num_unique_chars_in_window
        if (t_char_count.contains(right_char)
            && window_char_count[right_char] == t_char_count[right_char])
        {
            ++num_unique_chars_in_window;
        }

        //! Contract window until it is undesirable
        while (left_pos <= right_pos
               && num_unique_chars_in_window == num_required_unique_chars)
        {
            //! Save the smallest window until now
            if (min_window_size == -1
                || right_pos - left_pos + 1 < min_window_size)
            {
                min_window_size      = right_pos - left_pos + 1;
                min_window_left_pos  = left_pos;
                min_window_right_pos = right_pos;
            }

            //! The left char is no longer part of the window
            const char left_char {s[left_pos]};
            --window_char_count[left_char];

            if (t_char_count.contains(left_char)
                && window_char_count[left_char] < t_char_count[left_char])
            {
                --num_unique_chars_in_window;
            }

            //! Increment left pointer to look for new window
            ++left_pos;

        } // while (left_pos <= right_pos && ...

    } // for (int right_pos = 0; ...

    return min_window_size == -1
        ? ""
        : s.substr(min_window_left_pos, min_window_size);
}

static std::string minWindowDS2(std::string s, std::string t)
{
    //! @details leetcode.com/problems/minimum-window-substring/editorial
    //!
    //!          Time complexity O(S + T) where S = s.size() and T = t.size().
    //!          In cases where filtered_s_size <<< S, the time complexity is
    //!          reduced because the number of iterations would be
    //!          2 * filtered_s_size + S + T instead of 2 * S + T.
    //!          Space complexity O(S + T).

    if (s.empty() || t.empty())
    {
        return {};
    }

    std::unordered_map<char, int> t_char_count;
    for (const char ch : t)
    {
        ++t_char_count[ch];
    }

    //! Number of unique chars in t that need to be present in the window
    const auto num_required_unique_chars =
        static_cast<int>(std::ssize(t_char_count));

    //! Tracks the number of unique chars from t that are
    //! in the current window with the desired frequency
    int num_unique_chars_in_window {};

    //! Map counts all unique chars in current window
    std::unordered_map<char, int> window_char_count;

    const auto s_size = static_cast<int>(std::ssize(s));

    //! <index, char> of chars in s that are in t
    std::vector<std::pair<int, char>> s_idx_char;
    for (int idx = 0; idx < s_size; ++idx)
    {
        const char ch {s[idx]};
        if (t_char_count.contains(ch))
        {
            s_idx_char.emplace_back(idx, ch);
        }
    }

    int min_window_size {-1};
    int min_window_start_pos {};

    const auto filtered_s_size = static_cast<int>(std::ssize(s_idx_char));
    int        left_pos {};

    for (int right_pos = 0; right_pos < filtered_s_size; ++right_pos)
    {
        const auto [s_end_idx, right_char] = s_idx_char[right_pos];

        ++window_char_count[right_char];
        if (window_char_count[right_char] == t_char_count[right_char])
        {
            ++num_unique_chars_in_window;
        }

        while (left_pos <= right_pos
               && num_unique_chars_in_window == num_required_unique_chars)
        {
            const auto [s_start_idx, left_char] = s_idx_char[left_pos];

            if (min_window_size == -1
                || s_end_idx - s_start_idx + 1 < min_window_size)
            {
                min_window_size      = s_end_idx - s_start_idx + 1;
                min_window_start_pos = s_start_idx;
            }

            --window_char_count[left_char];
            if (window_char_count[left_char] < t_char_count[left_char])
            {
                --num_unique_chars_in_window;
            }

            ++left_pos;

        } // while (left_pos <= right_pos && ...

    } // for (int right_pos = 0; ...

    return min_window_size == -1
        ? ""
        : s.substr(min_window_start_pos, min_window_size);
}

TEST_CASE("Example 1", "[minWindow]")
{
    REQUIRE("BANC" == minWindowFA("ADOBECODEBANC", "ABC"));
    REQUIRE("BANC" == minWindowDS1("ADOBECODEBANC", "ABC"));
    REQUIRE("BANC" == minWindowDS2("ADOBECODEBANC", "ABC"));
}

TEST_CASE("Example 2", "[minWindow]")
{
    REQUIRE("a" == minWindowFA("a", "a"));
    REQUIRE("a" == minWindowDS1("a", "a"));
    REQUIRE("a" == minWindowDS2("a", "a"));
}

TEST_CASE("Example 3", "[minWindow]")
{
    REQUIRE(minWindowFA("a", "aa").empty());
    REQUIRE(minWindowDS1("a", "aa").empty());
    REQUIRE(minWindowDS2("a", "aa").empty());
}
