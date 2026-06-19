#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <memory>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

[[nodiscard]] constexpr bool
    compare_hot_sentences(const std::pair<int, std::string_view>& lhs,
                          const std::pair<int, std::string_view>& rhs)
{
    if (lhs.first == rhs.first)
    {
        return lhs.second < rhs.second;
    }

    return lhs.first > rhs.first;
}

//! @struct HotDegreeTrieNode
//! @brief Trie node containing pointers to its children and a hot degree
struct HotDegreeTrieNode
{
    std::unordered_map<char, std::unique_ptr<HotDegreeTrieNode>> children;

    //! Each entry marks a sentence that has a prefix up to the current node.
    //! Each entry has value <hot degree, corresponding sentence>.
    //! A vector is used instead of std::map or std::unordered_map so
    //! std::ranges::partial_sort can be efficiently used to retrieve the top 3
    //! historical hot sentences (Time complexity O(N * log M), where N is
    //! hot_degrees.size() and M = 3).
    std::vector<std::pair<int, std::string_view>> hot_degrees_sentences;
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

        bool found_sentence {};

        for (auto& [hot_deg, sentence_sv] : curr_node->hot_degrees_sentences)
        {
            if (sentence == sentence_sv)
            {
                found_sentence = true;
                hot_deg        = hot_degree;
                break;
            }
        }

        if (!found_sentence)
        {
            curr_node->hot_degrees_sentences.emplace_back(hot_degree, sentence);
        }
    }
}

//! @class AutocompleteSystemFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/others/3000/
//!
//!          First attempt solution does not pass Example 2 yet.
//!          17 / 43 testcases passed.
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
            update_trie(root, sentence_it->first, curr_tested_frequency);
            curr_tested_sentence.clear();
            return {};
        }

        auto* curr_node = &root;

        curr_tested_sentence += c;
        for (const char letter : curr_tested_sentence)
        {
            auto child_it = curr_node->children.find(letter);
            if (child_it == curr_node->children.end())
            {
                return {};
            }

            curr_node = child_it->second.get();
        }

        //! curr_node points to HotDegreeTrieNode for input char c
        static constexpr int top_hot_qty {3};

        auto& hot_degrees_sentences = curr_node->hot_degrees_sentences;

        const auto num_hot_sentences =
            static_cast<int>(std::ssize(hot_degrees_sentences));

        std::vector<std::string> top_hot_sentences;
        
        if (num_hot_sentences <= top_hot_qty)
        {
            top_hot_sentences.reserve(num_hot_sentences);
            std::ranges::sort(hot_degrees_sentences, compare_hot_sentences);
            std::ranges::transform(
                hot_degrees_sentences,
                std::back_inserter(top_hot_sentences),
                [](const std::pair<int, std::string_view>& elem) {
                    return std::string {elem.second};
                });
        }
        else
        {
            //! Partially sort hot_degrees_sentences to get the top 3
            top_hot_sentences.reserve(top_hot_qty);
            std::ranges::partial_sort(
                hot_degrees_sentences,
                hot_degrees_sentences.begin() + top_hot_qty,
                compare_hot_sentences);
            std::ranges::transform(
                hot_degrees_sentences.begin(),
                hot_degrees_sentences.begin() + top_hot_qty,
                std::back_inserter(top_hot_sentences),
                [](const std::pair<int, std::string_view>& elem) {
                    return std::string {elem.second};
                });
        }

        return top_hot_sentences;
    }

private:
    HotDegreeTrieNode root;

    //! Current tested sentence formed from calls to input
    std::string curr_tested_sentence;

    //! Map of <sentence, hot degree>
    std::unordered_map<std::string, int> sentence_hot_degree;
};

//! @struct TrieNodeDS1
struct TrieNodeDS1
{
    std::unordered_map<char, std::unique_ptr<TrieNodeDS1>> children;

    std::unordered_map<std::string, int> sentence_counts;
};

static void add_to_trie_DS1(TrieNodeDS1&       root,
                            const std::string& sentence,
                            int                count)
{
    auto* curr_node = &root;
    for (const char letter : sentence)
    {
        auto [child_it, node_exists] = curr_node->children.try_emplace(
            letter, std::make_unique<TrieNodeDS1>());

        curr_node = child_it->second.get();
        curr_node->sentence_counts[sentence] += count;
    }
}

[[nodiscard]] constexpr bool
    compare_hot_sentences_DS1(const std::pair<std::string, int>& lhs,
                              const std::pair<std::string, int>& rhs)
{
    if (lhs.second == rhs.second)
    {
        return lhs.first < rhs.first;
    }

    return lhs.second > rhs.second;
}

//! @class AutocompleteSystemDS1
//! @details leetcode.com/problems/design-search-autocomplete-system/editorial
//!
//!          Time complexity O(N * K + M * (N + M / K) * log (N + M / K)) where
//!          N = sentences.size(), K = average length of all sentences, and M is
//!          the number of times that input() is called.
//!          constructor: We initialize the trie, which costs O(N * K) to
//!          iterate over each character in each sentence.
//!          input: Adding a character to curr_sentence and the trie costs O(1).
//!          Next, we fetch and sort the sentences in the current node. A node
//!          can initially hold O(N) sentences. After calling input() M times,
//!          we could add M / K new sentences for a total of O(N + M / K)
//!          sentences. Sorting them costs O((N + M / K) * log (N + M / K)). The
//!          work done in the other cases like adding a new sentence to the trie
//!          will be dominated by this sort.
//!          Space complexity O(K * (N * K + M)). The worst-case scenario for
//!          the trie size is when no two sentences share any prefix. The trie
//!          will initially have a size of N * K. Then, each call to input()
//!          would create a new node. Each of these trie nodes have children and
//!          sentence_counts hash maps. The size of children is limited to 26 so
//!          we will ignore it. In sentence_counts, each node will only have one
//!          entry because no two sentences share any prefix, so no trie node is
//!          visited by more than one sentence. This entry has a size O(K).
class AutocompleteSystemDS1
{ 
public:
    AutocompleteSystemDS1(const std::vector<std::string>& sentences,
                          const std::vector<int>&         times)
    {
        for (int idx = 0; idx < std::ssize(sentences); ++idx)
        {
            add_to_trie_DS1(root, sentences[idx], times[idx]);
        }
    }

    std::vector<std::string> input(char c)
    {
        if (c == '#')
        {
            add_to_trie_DS1(root, curr_sentence, 1);
            curr_sentence.clear();
            curr_node = &root;
            return {};
        }

        curr_sentence += c;
        auto child_it = curr_node->children.find(c);
        if (child_it == curr_node->children.end())
        {
            curr_node = &dead_node;
            return {};
        }

        curr_node = child_it->second.get();

        std::vector<std::pair<std::string, int>> hot_sentences;
        std::ranges::copy(curr_node->sentence_counts,
                          std::back_inserter(hot_sentences));

        static constexpr int top_hot_qty {3};
        const auto           num_hot_sentences =
            static_cast<int>(std::ssize(hot_sentences));
        std::vector<std::string> top_hot_sentences;

        if (num_hot_sentences <= top_hot_qty)
        {
            std::ranges::sort(hot_sentences, compare_hot_sentences_DS1);
            top_hot_sentences.reserve(num_hot_sentences);
            for (auto& [sentence, hot_degree] : hot_sentences)
            {
                top_hot_sentences.push_back(std::move(sentence));
            }
            return top_hot_sentences;
        }

        std::ranges::partial_sort(hot_sentences,
                                  hot_sentences.begin() + top_hot_qty,
                                  compare_hot_sentences_DS1);
        top_hot_sentences.reserve(top_hot_qty);
        for (int idx = 0; idx < top_hot_qty; ++idx)
        {
            top_hot_sentences.push_back(std::move(hot_sentences[idx].first));
        }
        return top_hot_sentences;
    }

private:
    TrieNodeDS1  root {};
    TrieNodeDS1* curr_node {&root};
    TrieNodeDS1  dead_node {};

    std::string curr_sentence;
};

//! @struct TrieNodeDS2
struct TrieNodeDS2
{
    std::unordered_map<char, std::unique_ptr<TrieNodeDS2>> children;

    std::unordered_map<std::string, int> sentence_counts;
};

static void add_to_trie_DS2(TrieNodeDS2&       root,
                            const std::string& sentence,
                            int                count)
{
    auto* curr_node = &root;
    for (const char letter : sentence)
    {
        auto [child_it, node_exists] = curr_node->children.try_emplace(
            letter, std::make_unique<TrieNodeDS2>());

        curr_node = child_it->second.get();
        curr_node->sentence_counts[sentence] += count;
    }
}

[[nodiscard]] constexpr bool
    compare_hot_sentences_DS2(const std::pair<std::string, int>& lhs,
                              const std::pair<std::string, int>& rhs)
{
    if (lhs.second == rhs.second)
    {
        return lhs.first > rhs.first;
    }

    return lhs.second < rhs.second;
}

//! @class AutocompleteSystemDS2
//! @details leetcode.com/problems/design-search-autocomplete-system/editorial
class AutocompleteSystemDS2
{ 
public:
    AutocompleteSystemDS2(const std::vector<std::string>& sentences,
                          const std::vector<int>&         times)
    {
        for (int idx = 0; idx < std::ssize(sentences); ++idx)
        {
            add_to_trie_DS2(root, sentences[idx], times[idx]);
        }
    }

    std::vector<std::string> input(char c)
    {
        if (c == '#')
        {
            add_to_trie_DS2(root, curr_sentence, 1);
            curr_sentence.clear();
            curr_node = &root;
            return {};
        }

        curr_sentence += c;
        auto child_it = curr_node->children.find(c);
        if (child_it == curr_node->children.end())
        {
            curr_node = &dead_node;
            return {};
        }

        curr_node = child_it->second.get();
        std::priority_queue<std::pair<std::string, int>,
                            std::vector<std::pair<std::string, int>>,
                            decltype(&compare_hot_sentences_DS2)> max_hot_heap {
                                curr_node->sentence_counts.begin(),
                                curr_node->sentence_counts.end(),
                                compare_hot_sentences_DS2};

        static constexpr std::size_t top_hot_qty {3U};
        std::vector<std::string>     top_hot_sentences;
        top_hot_sentences.resize(std::min(top_hot_qty, max_hot_heap.size()));

        for (auto& hot_sentence : top_hot_sentences)
        {
            hot_sentence = std::move(max_hot_heap.top().first);
            max_hot_heap.pop();
        }

        return top_hot_sentences;
    }

private:
    TrieNodeDS2  root {};
    TrieNodeDS2* curr_node {&root};
    TrieNodeDS2  dead_node {};

    std::string curr_sentence;
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

    AutocompleteSystemDS1 system_ds1 {sentences, times};
    CHECK(expected_output1 == system_ds1.input('i'));
    CHECK(expected_output2 == system_ds1.input(' '));
    CHECK(system_ds1.input('a').empty());
    CHECK(system_ds1.input('#').empty());

    AutocompleteSystemDS2 system_ds2 {sentences, times};
    CHECK(expected_output1 == system_ds2.input('i'));
    CHECK(expected_output2 == system_ds2.input(' '));
    CHECK(system_ds2.input('a').empty());
    CHECK(system_ds2.input('#').empty());
}

TEST_CASE("Example 2", "[AutocompleteSystem]")
{
    const std::vector<std::string> sentences {
        "i love you", "island", "ironman", "i love leetcode"};
    const std::vector<int> times {5, 3, 2, 2};

    const std::vector<std::string> expected_output1 {
        "i love you", "island", "i love leetcode"};
    const std::vector<std::string> expected_output2 {
        "i love you", "i love leetcode"};
    const std::vector<std::string> expected_output3 {
        "i love you", "i love leetcode", "i a"};
    const std::vector<std::string> expected_output4 {"i a"};
    const std::vector<std::string> expected_output5 {
        "i love you", "island", "i a"};
    const std::vector<std::string> expected_output6 {
        "i love you", "i a", "i love leetcode"};

    AutocompleteSystemFA system_fa {sentences, times};

    CHECK(expected_output1 == system_fa.input('i'));
    CHECK(expected_output2 == system_fa.input(' '));
    CHECK(system_fa.input('a').empty());
    CHECK(system_fa.input('#').empty());

    const auto generated_output_round2_from_i = system_fa.input('i');
    CHECK(expected_output1 != generated_output_round2_from_i);
    CHECK(std::vector<std::string> {"i love you", "island", "i a"}
          == generated_output_round2_from_i);

    const auto generated_output_round2_from_space = system_fa.input(' ');
    CHECK(expected_output3 != generated_output_round2_from_space);
    CHECK(std::vector<std::string> {"i love you", "i a", "i love leetcode"}
          == generated_output_round2_from_space);

    CHECK(expected_output4 == system_fa.input('a'));
    CHECK(system_fa.input('#').empty());

    const auto generated_output_round3_from_i = system_fa.input('i');
    CHECK(expected_output5 != generated_output_round3_from_i);
    CHECK(std::vector<std::string> {"i love you", "island", "i love leetcode"}
          == generated_output_round3_from_i);

    const auto generated_output_round3_from_space = system_fa.input(' ');
    CHECK(expected_output6 != generated_output_round3_from_space);
    CHECK(std::vector<std::string> {"i love you", "i love leetcode", "i a"}
          == generated_output_round3_from_space);

    CHECK(expected_output4 == system_fa.input('a'));
    CHECK(system_fa.input('#').empty());

    AutocompleteSystemDS1 system_ds1 {sentences, times};
    CHECK(expected_output1 == system_ds1.input('i'));
    CHECK(expected_output2 == system_ds1.input(' '));
    CHECK(system_ds1.input('a').empty());
    CHECK(system_ds1.input('#').empty());

    CHECK(expected_output1 == system_ds1.input('i'));
    CHECK(expected_output3 == system_ds1.input(' '));
    CHECK(expected_output4 == system_ds1.input('a'));
    CHECK(system_ds1.input('#').empty());

    CHECK(expected_output5 == system_ds1.input('i'));
    CHECK(expected_output6 == system_ds1.input(' '));
    CHECK(expected_output4 == system_ds1.input('a'));
    CHECK(system_ds1.input('#').empty());

    AutocompleteSystemDS2 system_ds2 {sentences, times};
    CHECK(expected_output1 == system_ds2.input('i'));
    CHECK(expected_output2 == system_ds2.input(' '));
    CHECK(system_ds2.input('a').empty());
    CHECK(system_ds2.input('#').empty());

    CHECK(expected_output1 == system_ds2.input('i'));
    CHECK(expected_output3 == system_ds2.input(' '));
    CHECK(expected_output4 == system_ds2.input('a'));
    CHECK(system_ds2.input('#').empty());

    CHECK(expected_output5 == system_ds2.input('i'));
    CHECK(expected_output6 == system_ds2.input(' '));
    CHECK(expected_output4 == system_ds2.input('a'));
    CHECK(system_ds2.input('#').empty());
}
