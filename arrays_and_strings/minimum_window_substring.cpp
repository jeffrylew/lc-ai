#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>
#include <unordered_map>

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

    if (s.empty() || t.empty())
    {
        return {};
    }

    //! @todo
}

TEST_CASE("Example 1", "[minWindow]")
{
    REQUIRE("BANC" == minWindowFA("ADOBECODEBANC", "ABC"));
    REQUIRE("BANC" == minWindowDS1("ADOBECODEBANC", "ABC"));
}

TEST_CASE("Example 2", "[minWindow]")
{
    REQUIRE("a" == minWindowFA("a", "a"));
    REQUIRE("a" == minWindowDS1("a", "a"));
}

TEST_CASE("Example 3", "[minWindow]")
{
    REQUIRE(minWindowFA("a", "aa").empty());
    REQUIRE(minWindowDS1("a", "aa").empty());
}
