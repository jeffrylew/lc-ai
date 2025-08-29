#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <optional>
#include <queue>
#include <string>
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

    std::vector<std::optional<bool>> can_build_cache(s.size());

    const std::function<bool(int)> can_build = [&](int idx) {
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

            if (s.substr(idx - curr_word_size + 1, curr_word_size) == word
               && can_build(idx - curr_size))
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

TEST_CASE("Example 1", "[wordBreak]")
{
    const std::string              s {"leetcode"};
    const std::vector<std::string> wordDict {"leet", "code"};

    REQUIRE(wordBreakDS1(s, wordDict));
    REQUIRE(wordBreakDS2(s, wordDict));
}

TEST_CASE("Example 2", "[wordBreak]")
{
    const std::string              s {"applepenapple"};
    const std::vector<std::string> wordDict {"apple", "pen"};

    REQUIRE(wordBreakDS1(s, wordDict));
    REQUIRE(wordBreakDS2(s, wordDict));
}

TEST_CASE("Example 3", "[wordBreak]")
{
    const std::string              s {"catsandog"};
    const std::vector<std::string> wordDict {
        "cats", "dog", "sand", "and", "cat"};

    REQUIRE(!wordBreakDS1(s, wordDict));
    REQUIRE(!wordBreakDS2(s, wordDict));
}
