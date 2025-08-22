#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

static int ladderLengthFA(std::string               beginWord,
                          std::string               endWord,
                          std::vector<std::string>& wordList)
{

}

TEST_CASE("Example 1", "[ladderLength]")
{
    const std::string        beginWord {"hit"};
    const std::string        endWord {"cog"};
    std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};

    REQUIRE(5 == ladderLengthFA(beginWord, endWord, wordList));
}

TEST_CASE("Example 2", "[ladderLength]")
{
    const std::string        beginWord {"hit"};
    const std::string        endWord {"cog"};
    std::vector<std::string> wordList {"hot", "dot", "dog", "lot", "log"};

    REQUIRE(0 == ladderLengthFA(beginWord, endWord, wordList));
}
