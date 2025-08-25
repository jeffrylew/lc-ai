#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

static bool wordBreakDS1(std::string                     s,
                         const std::vector<std::string>& wordDict)
{
    //! @details https://leetcode.com/problems/word-break/editorial/

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

TEST_CASE("Example 1", "[wordBreak]")
{
    const std::string              s {"leetcode"};
    const std::vector<std::string> wordDict {"leet", "code"};

    REQUIRE(wordBreakDS1(s, wordDict));
}

TEST_CASE("Example 2", "[wordBreak]")
{
    const std::string              s {"applepenapple"};
    const std::vector<std::string> wordDict {"apple", "pen"};

    REQUIRE(wordBreakDS1(s, wordDict));
}

TEST_CASE("Example 3", "[wordBreak]")
{
    const std::string              s {"catsandog"};
    const std::vector<std::string> wordDict {
        "cats", "dog", "sand", "and", "cat"};

    REQUIRE(!wordBreakDS1(s, wordDict));
}
