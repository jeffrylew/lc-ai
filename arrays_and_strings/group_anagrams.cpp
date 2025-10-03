#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

static std::vector<std::vector<std::string>>
    groupAnagramsFA(const std::vector<std::string>& strs)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2970/
    //!
    //!          Time complexity O(N * S * log S) where N = strs.size() and
    //!          S = the average length of a string in strs. We sort each string
    //!          in O(S * log S) and repeat for all O(N) strings in strs.
    //!          Space complexity O(N) to store all strings in strs.

    std::unordered_map<std::string, std::vector<std::string>> anagram_groups;

    for (const auto& str : strs)
    {
        auto alphabetical_str = str;
        std::ranges::sort(alphabetical_str);

        anagram_groups[std::move(alphabetical_str)].push_back(str);
    }

    std::vector<std::vector<std::string>> grouped_anagrams;
    grouped_anagrams.reserve(anagram_groups.size());

    for (auto& [alphabetical_key, anagram_vec] : anagram_groups)
    {
        grouped_anagrams.push_back(std::move(anagram_vec));
    }

    return grouped_anagrams;
}

TEST_CASE("Example 1", "[groupAnagrams]")
{
    const std::vector<std::string> strs {
        "eat", "tea", "tan", "ate", "nat", "bat"};

    const std::vector<std::vector<std::string>> expected_output {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}

TEST_CAST("Example 2", "[groupAnagrams]")
{
    const std::vector<std::string> strs {""};

    const std::vector<std::vector<std::string>> expected_output {{""}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}

TEST_CAST("Example 3", "[groupAnagrams]")
{
    const std::vector<std::string> strs {"a"};

    const std::vector<std::vector<std::string>> expected_output {{"a"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}
