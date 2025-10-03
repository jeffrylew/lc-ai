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

static std::vector<std::vector<std::string>>
    groupAnagramsDS1(const std::vector<std::string>& strs)
{
    //! @details https://leetcode.com/problems/group-anagrams/editorial/
    //!
    //!          Time complexity O(N * K * log K) where N = strs.size() and K is
    //!          the max length of a string in strs. The outer loop takes O(N)
    //!          to iterate through each string. Within an iteration, we sort
    //!          each string in O(K * log K).
    //!          Space complexity O(N * K) to store all strings in anagram_map

    //! Create a map to store the anagrams where the keys are the sorted
    //! strings and the values are the vectors of grouped anagrams
    std::unordered_map<std::string, std::vector<std::string>> anagram_map;

    for (const auto& str : strs)
    {
        //! Sort the key
        auto alphabetical_key = str;
        std::ranges::sort(alphabetical_key);

        //! If the string is an anagram of another string then
        //! they will have the same key and be grouped together
        anagram_map[std::move(alphabetical_key)].push_back(str);
    }

    std::vector<std::vector<std::string>> anagram_groups;
    anagram_groups.reserve(anagram_map.size());

    for (auto& key_and_group : anagram_map)
    {
        anagram_groups.push_back(std::move(key_and_group.second));
    }

    return anagram_groups;
}

TEST_CASE("Example 1", "[groupAnagrams]")
{
    const std::vector<std::string> strs {
        "eat", "tea", "tan", "ate", "nat", "bat"};

    const std::vector<std::vector<std::string>> expected_output {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
    REQUIRE(expected_output == groupAnagramsDS1(strs));
}

TEST_CAST("Example 2", "[groupAnagrams]")
{
    const std::vector<std::string> strs {""};

    const std::vector<std::vector<std::string>> expected_output {{""}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
    REQUIRE(expected_output == groupAnagramsDS1(strs));
}

TEST_CAST("Example 3", "[groupAnagrams]")
{
    const std::vector<std::string> strs {"a"};

    const std::vector<std::vector<std::string>> expected_output {{"a"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
    REQUIRE(expected_output == groupAnagramsDS1(strs));
}
