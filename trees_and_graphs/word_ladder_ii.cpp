#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static std::vector<std::vector<std::string>> findLaddersFA(
    std::string                     beginWord,
    std::string                     endWord,
    const std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/483/
    //!
    //!          First attempt solution results in Memory Limit Exceeded

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
    std::queue<std::vector<std::string>>  seq_queue;
    seq_queue.push({beginWord});

    int min_sequence_size {1000};

    while (!seq_queue.empty())
    {
        const auto seq_queue_size = static_cast<int>(std::ssize(seq_queue));

        for (int seq_idx = 0; seq_idx < seq_queue_size; ++seq_idx)
        {
            auto seq_vec = std::move(seq_queue.front());
            seq_queue.pop();

            const auto& last_word = seq_vec.back();
            if (last_word == endWord)
            {
                const auto seq_vec_size = static_cast<int>(std::ssize(seq_vec));
                if (seq_vec_size > min_sequence_size)
                {
                    break;
                }

                min_sequence_size = seq_vec_size;
                shortest_sequences.push_back(std::move(seq_vec));
                continue;
            }

            const auto last_word_size = static_cast<int>(std::ssize(last_word));
            for (int word_idx = 0; word_idx < last_word_size; ++word_idx)
            {
                std::string last_word_neighbor {last_word};
                last_word_neighbor[word_idx] = '#';

                if (!word_neighbor_map.contains(last_word_neighbor))
                {
                    continue;
                }

                for (const auto neighbor_sv
                     : word_neighbor_map[last_word_neighbor])
                {
                    auto next_seq_vec = seq_vec;
                    next_seq_vec.emplace_back(std::string {neighbor_sv});
                    seq_queue.push(std::move(next_seq_vec));
                }
            }
        }
    }

    return shortest_sequences;
}

[[nodiscard]] static std::vector<std::string> find_neighbors(
    std::string                            word,
    const std::unordered_set<std::string>& word_set)
{
    std::vector<std::string> neighbors;

    for (auto& word_char : word)
    {
        const char orig_char {word_char};

        //! Replace word_char with all letters from
        //! a to z except for the original character
        for (char replacement = 'a'; replacement <= 'z'; ++replacement)
        {
            word_char = replacement;

            if (replacement == orig_char || !word_set.contains(word))
            {
                continue;
            }

            neighbors.push_back(word);
        }

        word_char = orig_char;
    }

    return neighbors;
}

static std::vector<std::vector<std::string>> findLaddersDS1(
    std::string                     beginWord,
    std::string                     endWord,
    const std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/problems/word-ladder-ii/editorial/

    std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());

    std::vector<std::vector<std::string>> shortest_paths;

    //! Build the DAG using BFS
    build_dag_using_bfs(beginWord, endWord, word_set);

    //! Every path will start from endWord
    std::vector<std::string> curr_path {endWord};

    //! Traverse the DAG to find all paths between endWord and beginWord
    backtrack_to_traverse_dag(endWord, beginWord);

    return shortest_paths;
}

TEST_CASE("Example 1", "[findLadders]")
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};

    const std::vector<std::vector<std::string>> expected_output {
        {"hit", "hot", "dot", "dog", "cog"},
        {"hit", "hot", "lot", "log", "cog"}};

    REQUIRE(expected_output == findLaddersFA("hit", "cog", wordList));
    REQUIRE(expected_output == findLaddersDS1("hit", "cog", wordList));
}

TEST_CASE("Example 2", "[findLadders]")
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log"};

    REQUIRE(findLaddersFA("hit", "cog", wordList).empty());
    REQUIRE(findLaddersDS1("hit", "cog", wordList).empty());
}
