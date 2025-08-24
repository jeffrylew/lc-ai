#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static int ladderLengthDS1(std::string               beginWord,
                           std::string               endWord,
                           std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/problems/word-ladder/editorial/
    //!
    //!          Time complexity O(M ^ 2 * N) where M = length of each word and
    //!          N = wordList.size(). For each word in the word list, we iterate
    //!          over its length to find all intermediate words corresponding to
    //!          it. The total number of iteration to create word_combo_map is
    //!          M * N. Additionally, forming each intermediate word takes O(M)
    //!          due to the substring operation. BFS in the worst case might go
    //!          to each of the N words. For each word, we need to examine M
    //!          possible intermediate words/combinations. Since we are using
    //!          the substring operation to find each combination, M combos take
    //!          O(M ^ 2). Thus, BFS traversal is also O(M ^ 2 * N).
    //!          Space complexity O(M ^ 2 * N). Each word in the word list has
    //!          M intermediate combos so each word needs M ^ 2 space. Thus,
    //!          word_combo_map needs O(M ^ 2 * N). In the worst case, the BFS
    //!          queue needs space for all O(N) words resulting in O(M * N).
    //!          Optimization: Can reduce space complexity by storing indices
    //!          corresponding to each word instead of the word itself.

    //! All words are the same length
    const auto word_size = static_cast<int>(std::ssize(beginWord));

    //! Hash map holds combinations of words that can be formed from any given
    //! word by changing one letter at a time. Key is the generic word and the
    //! value is a vector of words that have the same intermediate generic word.
    std::unordered_map<std::string, std::vector<std::string>>> word_combo_map;

    for (const auto& word : wordList)
    {
        for (int idx = 0; idx < word_size; ++idx)
        {
            std::string generic_word {
                word.substr(0, idx) + '*' + word.substr(i + 1, word_size)};

            word_combo_map[std::move(generic_word)].push_back(word);
        }
    }

    //! Queue for BFS
    std::queue<std::pair<std::string, int>> word_level_queue;
    word_level_queue.emplace(beginWord, 1);

    //! Ensure we don't process the same word
    std::unordered_set<std::string> processed_words;
    processed_words.insert(beginWord);
    // std::unordered_set<std::string> processed_words({beginWord});

    while (!word_level_queue.empty())
    {
        const auto [word, level] = word_level_queue.front();
        word_level_queue.pop();

        for (int idx = 0; idx < word_size; ++idx)
        {
            std::string generic_word {
                word.substr(0, idx) + '*' + word.substr(idx + 1, word_size)};
            const auto& adjacent_words =
                word_combo_map[std::move(generic_word)];

            for (const auto& adjacent_word : adjacent_words)
            {
                if (adjacent_word == endWord)
                {
                    return level + 1;
                }

                if (!processed_words.contains(adjacent_word))
                {
                    processed_words.insert(adjacent_word);
                    word_level_queue.emplace(adjacent_word, level + 1);
                }
            }
        }
    }

    return 0;
}

using AllComboMap_t = std::unordered_map<std::string, std::vector<std::string>>;

[[nodiscard]] static int visitWord(
    std::queue<std::pair<std::string, int>>&    word_level_queue,
    std::unordered_map<std::string, int>&       processed_words,
    const std::unordered_map<std::string, int>& other_processed_words,
    const AllComboMap_t&                        word_combo_map,
    int                                         word_size)
{
    const auto init_queue_size = static_cast<int>(std::ssize(word_level_queue));

    for (int word_idx = 0; word_idx < init_queue_size; ++word_idx)
    {
        const auto [word, level] = word_level_queue.front();
        word_level_queue.pop();

        for (int idx = 0; idx < word_size; ++idx)
        {
            std::string generic_word {
                word.substr(0, idx) + '*' + word.substr(idx + 1, word_size)};
            const auto& adjacent_words =
                word_combo_map[std::move(generic_word)];

            //! Next states are all words that share the same intermediate state
            for (const auto& adjacent_word : adjacent_words)
            {
                if (other_processed_words.contains(adjacent_word))
                {
                    return level + other_processed_words.at(adjacent_word);
                }

                if (!processed_words.contains(adjacent_word))
                {
                    processed_words.try_emplace(adjacent_word, level + 1);
                    word_level_queue.emplace(adjacent_word, level + 1);
                }
            }
        }
    }

    return -1;
}

static int ladderLengthDS2(std::string               beginWord,
                           std::string               endWord,
                           std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/problems/word-ladder/editorial/

    if (0 == std::count(wordList.begin(), wordList.end(), endWord))
    {
        return 0;
    }

    //! All words are the same length
    const auto word_size = static_cast<int>(std::ssize(beginWord));

    //! Map holding combination of words that can be formed from any given word
    //! by changing one letter at a time
    AllComboMap_t word_combo_map;

    for (const auto& word : wordList)
    {
        for (int idx = 0; idx < word_size; ++idx)
        {
            std::string generic_word {
                word.substr(0, idx) + '*' + word.substr(idx + 1, word_size)};

            word_combo_map[std::move(generic_word)].push_back(word);
        }
    }

    //! Queues for bidirectional BFS
    std::queue<std::pair<std::string, int>> begin_word_level_queue;
    std::queue<std::pair<std::string, int>> end_word_level_queue;
    begin_word_level_queue.emplace(beginWord, 1);
    end_word_level_queue.emplace(endWord, 1);

    //! Maps save word and level in BFS. Avoids processing same word.
    std::unordered_map<std::string, int> begin_processed_words;
    std::unordered_map<std::string, int> end_processed_words;
    begin_processed_words.emplace(beginWord, 1);
    end_processed_words.emplace(endWord, 1);

    int num_words {-1};

    while (!begin_word_level_queue.empty() && !end_word_level_queue.empty())
    {
        //! Progress forward one step from the shorter queue
        if (begin_word_level_queue.size() <= end_word_level_queue.size())
        {
            num_words = visitWord(begin_word_level_queue,
                                  begin_processed_words,
                                  end_processed_words,
                                  word_combo_map,
                                  word_size);
        }
        else
        {
            num_words = visitWord(end_word_level_queue,
                                  end_processed_words,
                                  begin_processed_words,
                                  word_combo_map,
                                  word_size);
        }

        if (num_words > -1)
        {
            return num_words;
        }
    }

    return 0;
}

TEST_CASE("Example 1", "[ladderLength]")
{
    const std::string        beginWord {"hit"};
    const std::string        endWord {"cog"};
    std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};

    REQUIRE(5 == ladderLengthDS1(beginWord, endWord, wordList));
    REQUIRE(5 == ladderLengthDS2(beginWord, endWord, wordList));
}

TEST_CASE("Example 2", "[ladderLength]")
{
    const std::string        beginWord {"hit"};
    const std::string        endWord {"cog"};
    std::vector<std::string> wordList {"hot", "dot", "dog", "lot", "log"};

    REQUIRE(0 == ladderLengthDS1(beginWord, endWord, wordList));
    REQUIRE(0 == ladderLengthDS2(beginWord, endWord, wordList));
}
