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

    int  min_sequence_size {1000};
    auto sequence_it {shortest_sequences.begin()};

    while (sequence_it != shortest_sequences.end())
    {
        const auto curr_seq_size = static_cast<int>(std::ssize(*sequence_it));
        if (curr_seq_size <= min_sequence_size)
        {
            min_sequence_size = curr_seq_size;
            ++sequence_it;
            continue;
        }

        break;
    }
    shortest_sequences.erase(sequence_it, shortest_sequences.end());

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
