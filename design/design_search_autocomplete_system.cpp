#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

//! @struct HotDegreeTrieNode
//! @brief Trie node containing pointers to its children and a hot degree
struct HotDegreeTrieNode
{
    std::unordered_map<char, std::unique_ptr<FrequencyTrieNode>> children;

    //! Each entry marks the end of a sentence at the current HotDegreeNode.
    //! Each entry has value <hot degree, corresponding sentence>.
    //! A vector is used instead of std::map or std::unordered_map so
    //! std::ranges::partial_sort can be efficiently used to retrieve the top 3
    //! historical hot sentences (Time complexity O(N * log M), where N is
    //! hot_degrees.size() and M = 3).
    std::vector<std::pair<int, std::string>> hot_degrees_sentences;
};

//! @brief Add a sentence and its hot degree to the trie
//! @param[in, out] root       Reference to root HotDegreeTrieNode
//! @param[in]      sentence   std::string_view of sentence to add to trie
//! @param[in]      hot_degree The hot degree of the sentence
static void update_trie(HotDegreeTrieNode& root,
                        std::string_view   sentence,
                        int                hot_degree)
{
    auto* curr_node = &root;
    for (const char letter : sentence)
    {
        auto [child_it, node_exists] = curr_node->children.try_emplace(
            letter, std::make_unique<HotDegreeTrieNode>());

        curr_node = child_it->second.get();
    }

    //! At this point, we have a full sentence ending at curr_node
    curr_node->hot_degrees_sentences.emplace_back(
        hot_degree, std::string {sentence});
}

//! @class AutocompleteSystemFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/others/3000/
class AutocompleteSystemFA
{
public:
    AutocompleteSystemFA(const std::vector<std::string>& sentences,
                         const std::vector<int>&         times)
    {
        for (int idx = 0; idx < std::ssize(sentences); ++idx)
        {
            sentence_hot_degree.try_emplace(sentences[idx], times[idx]);
            update_trie(root, sentences[idx], times[idx]);
        }
    }

    std::vector<std::string> input(char c)
    {
        if (c == '#')
        {
            int curr_tested_frequency {1};

            auto [sentence_it, sentence_exists] =
                sentence_hot_degree.try_emplace(curr_tested_sentence,
                                                curr_tested_frequency);
            if (sentence_exists)
            {
                curr_tested_frequency = ++(sentence_it->second);
            }
            update_trie(root, curr_tested_sentence, curr_tested_frequency);
            curr_tested_sentence.clear();
            return {};
        }

        //! @todo
    }

private:
    HotDegreeTrieNode root;

    //! Current tested sentence formed from calls to input
    std::string curr_tested_sentence;

    //! Map of <sentence, hot degree>
    std::unordered_map<std::string, int> sentence_hot_degree;
};

TEST_CASE("Example 1", "[AutocompleteSystem]")
{
    const std::vector<std::string> sentences {
        "i love you", "island", "ironman", "i love leetcode"};
    const std::vector<int> times {5, 3, 2, 2};

    const std::vector<std::string> expected_output1 {
        "i love you", "island", "i love leetcode"};
    const std::vector<std::string> expected_output2 {
        "i love you", "i love leetcode"};

    AutocompleteSystemFA system_fa {sentences, times};

    //! There are four sentences that have prefix 'i'. Among them, "ironman" and
    //! "i love leetcode" have the same hot degree. Since ' ' has ASCII code 32
    //! and 'r' has ASCII code 114, "i love leetcode" should be in front of
    //! "ironman". Also, we only need to output the top 3 hot sentences, so
    //! "ironman" will be ignored.
    CHECK(expected_output1 == system_fa.input('i'));

    //! There are only two sentences that have prefix "i "
    //! - "i love you"
    //! - "i love leetcode"
    CHECK(expected_output2 == system_fa.input(' '));

    //! There are no sentences that have prefix "i a"
    CHECK(system_fa.input('a').empty());

    //! The user finished the input, the sentence "i a" should be saved as a
    //! historical sentence in the system. And the following input will be
    //! counted as a new search.
    CHECK(system_fa.input('#').empty());
}
