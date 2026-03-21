#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

static std::vector<std::vector<std::string>> findLaddersFA(
    std::string                     beginWord,
    std::string                     endWord,
    const std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/483/

    //! Map of <word neighbor, word>
    std::unordered_map<std::string, std::vector<std::string_view>>
        word_neighbor_map;

    for (const auto& word : wordList)
    {
        const auto word_size = static_cast<int>(std::ssize(word));

        for (int word_idx = 0; word_idx < word_size; ++word_idx)
        {
            std::string neighbor {word};
            neighbor[word_idx] = '#';
            word_neighbor_map[std::move(neighbor)].emplace_back(
                std::string_view {word});
        }
    }

    std::vector<std::vector<std::string>> shortest_sequences;

    const auto begin_word_size = static_cast<int>(std::ssize(beginWord));
    for (int begin_idx = 0; begin_idx < begin_word_size; ++begin_idx)
    {
        std::string begin_word_neighbor {beginWord};
        begin_word_neighbor[begin_idx] = '#';

        if (!word_neighbor_map.contains(begin_word_neighbor))
        {
            continue;
        }

        //! @todo
    }

    return shortest_sequences;
}

TEST_CASE("Example 1", "[findLadders]")
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};

    const std::vector<std::vector<std::string>> expected_output {
        {"hit", "hot", "dot", "dog", "cog"},
        {"hit", "hot", "lot", "log", "cog"}};

    REQUIRE(expected_output == findLaddersFA("hit", "cog", wordList));
}

TEST_CASE("Example 2", "[findLadders]")
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log"};

    REQUIRE(findLaddersFA("hit", "cog", wordList).empty());
}
