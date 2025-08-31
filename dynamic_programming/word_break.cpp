#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static bool wordBreakDS1(std::string                     s,
                         const std::vector<std::string>& wordDict)
{
    //! @details https://leetcode.com/problems/word-break/editorial/
    //!
    //!          Time complexity O(N ^ 3 + M * K) where N = s.size(), M = size
    //!          of wordDict, and K = average length of words in wordDict. There
    //!          are O(N) nodes. We never visit a node more than once due to
    //!          visited_idxs. At each node, we iterate over O(N) nodes in front
    //!          of the current node. For each node end_idx, we create a
    //!          substring, which costs O(N). Thus, handling N nodes costs
    //!          O(N * N ^ 2) = O(N ^ 3) for BFS. We also spent O(M * K) to
    //!          create the words set.
    //!          Space complexity O(N + M * K). We use O(N) space for idx_queue
    //!          and visited_idxs. We use O(M * K) space for the words set.

    std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());

    //! Each index of s can be thought of as a node
    std::vector<bool> visited_idxs(1U + s.size());

    std::queue<int> idx_queue;
    idx_queue.push(0);

    while (!idx_queue.empty())
    {
        const int start_idx {idx_queue.front()};
        idx_queue.pop();

        if (start_idx == std::ssize(s))
        {
            return true;
        }

        for (int end_idx = start_idx + 1; end_idx <= std::ssize(s); ++end_idx)
        {
            if (visited_idxs[end_idx])
            {
                continue;
            }

            if (words.contains(s.substr(start_idx, end_idx - start_idx)))
            {
                idx_queue.push(end_idx);
                visited_idxs[end_idx] = true;
            }
        }
    }

    return false;
}

static bool wordBreakDS2(std::string                     s,
                         const std::vector<std::string>& wordDict)
{
    //! @details https://leetcode.com/problems/word-break/editorial/
    //!
    //!          Time complexity O(N * M * k) where N = s.size(), M = size of
    //!          wordDict, and k = average length of words in wordDict. There
    //!          are N states of can_build(idx) which are calculated once due to
    //!          memoization. To calculate a state, we iterate over M words and
    //!          for each word, we perform substring operations in O(k).
    //!          Space complexity O(N). The can_build_cache vector uses O(N) and
    //!          the recursion call stack can use up to O(N).

    //! Cache memoizing whether there s can be built at each index
    std::vector<std::optional<bool>> can_build_cache(s.size());

    //! Check if it is possible to build s up to and including index idx
    const std::function<bool(int)> can_build = [&](int idx) {
        //! Base case: Represents empty string. Can always build doing nothing.
        if (idx < 0)
        {
            return true;
        }

        if (can_build_cache[idx].has_value())
        {
            return can_build_cache[idx].value();
        }

        for (const auto& word : wordDict)
        {
            const auto curr_word_size = static_cast<int>(std::ssize(word));

            //! Handle out-of-bounds case
            if (idx - curr_word_size + 1 < 0)
            {
                continue;
            }

            //! Recurrence relation requirements:
            //! 1. There needs to be a word from wordDict that ends at idx
            //! 2. If we find a word that ends at idx, it needs to build upon
            //!    another word ending at idx - curr_word_size
            if (s.substr(idx - curr_word_size + 1, curr_word_size) == word
               && can_build(idx - curr_word_size))
            {
                can_build_cache[idx] = true;
                return true;
            }
        }

        can_build_cache[idx] = false;
        return false;
    };

    return can_build(static_cast<int>(std::ssize(s)) - 1);
}

static bool wordBreakDS3(std::string                     s,
                         const std::vector<std::string>& wordDict)
{
    //! @details https://leetcode.com/problems/word-break/editorial/
    //!
    //!          Time complexity O(N * M * k). It costs O(M * k) to calculate
    //!          each state and there are O(N) states in total.
    //!          Space complexity O(N) for can_build vector of size N.

    std::vector<bool> can_build(s.size());

    //! Top-down approach started at s.size() - 1 and ended at base cases
    //! Bottom-up approach starts at idx = 0 and ends at s.size() - 1
    for (int idx = 0; idx < std::ssize(s); ++idx)
    {
        for (const auto& word : wordDict)
        {
            const auto curr_word_size = static_cast<int>(std::ssize(word));

            //! Handle out-of-bounds case
            if (idx < curr_word_size - 1)
            {
                continue;
            }

            //! If idx == curr_word_size - 1 then word ending at idx is first
            //! (don't check can_build[idx - curr_word_size] accessing neg idx)
            if ((idx == curr_word_size - 1 || can_build[idx - curr_word_size])
                && s.substr(idx - curr_word_size + 1, curr_word_size) == word)
            {
                can_build[idx] = true;
                break;
            }
        }
    }

    return can_build.back();
}

struct TrieNode
{
    bool is_word {};

    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
};

static bool wordBreakDS4(std::string                     s,
                         const std::vector<std::string>& wordDict)
{
    //! @details https://leetcode.com/problems/word-break/editorial/
    //!
    //!          Time complexity O(M * k + N * k) where N = s.size(), M = size
    //!          of wordDict, and k = average length of words in wordDict.
    //!          Building the trie involves iterating over all characters of all
    //!          words in O(M * k). Once we build the trie, we fill can_build.
    //!          For each start_idx, we iterate over indices after start_idx up
    //!          to O(k) since the inner loop will stop after k steps.
    //!          Space complexity O(M * k + N). The trie can have up to M * k
    //!          nodes and the can_build vector takes O(N) space.

    TrieNode root;

    for (const auto& word : wordDict)
    {
        auto* curr = &root;
        for (const char letter : word)
        {
            auto [child_it, exists] = curr->children.try_emplace(
                letter, std::make_unique<TrieNode>());

            curr = child_it->second.get();
        }

        curr->is_word = true;
    }

    const auto        str_size = static_cast<int>(std::ssize(s));
    std::vector<bool> can_build(s.size());

    for (int start_idx = 0; start_idx < str_size; ++start_idx)
    {
        if (start_idx != 0 && !can_build[start_idx - 1])
        {
            continue;
        }

        auto* curr = &root;
        for (int end_idx = start_idx; end_idx < str_size; ++end_idx)
        {
            const char end_letter {s[end_idx]};

            if (!curr->children.contains(end_letter))
            {
                //! No words exist
                break;
            }

            curr = curr->children[end_letter].get();
            if (curr->is_word)
            {
                can_build[end_idx] = true;
            }
        }
    }

    return can_build.back();
}

TEST_CASE("Example 1", "[wordBreak]")
{
    const std::string              s {"leetcode"};
    const std::vector<std::string> wordDict {"leet", "code"};

    REQUIRE(wordBreakDS1(s, wordDict));
    REQUIRE(wordBreakDS2(s, wordDict));
    REQUIRE(wordBreakDS3(s, wordDict));
    REQUIRE(wordBreakDS4(s, wordDict));
}

TEST_CASE("Example 2", "[wordBreak]")
{
    const std::string              s {"applepenapple"};
    const std::vector<std::string> wordDict {"apple", "pen"};

    REQUIRE(wordBreakDS1(s, wordDict));
    REQUIRE(wordBreakDS2(s, wordDict));
    REQUIRE(wordBreakDS3(s, wordDict));
    REQUIRE(wordBreakDS4(s, wordDict));
}

TEST_CASE("Example 3", "[wordBreak]")
{
    const std::string              s {"catsandog"};
    const std::vector<std::string> wordDict {
        "cats", "dog", "sand", "and", "cat"};

    REQUIRE(!wordBreakDS1(s, wordDict));
    REQUIRE(!wordBreakDS2(s, wordDict));
    REQUIRE(!wordBreakDS3(s, wordDict));
    REQUIRE(!wordBreakDS4(s, wordDict));
}
