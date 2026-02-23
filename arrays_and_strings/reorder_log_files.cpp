#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

static std::vector<std::string> reorderLogFilesFA(
    const std::vector<std::string>& logs)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2974/
}

TEST_CASE("Example 1", "[reorderLogFiles]")
{
    const std::vector<std::string> logs {
        "dig1 8 1 5 1",
        "let1 art can",
        "dig2 3 6",
        "let2 own kit dig",
        "let3 art zero"};

    const std::vector<std::string> expected_output {
        "let1 art can",
        "let3 art zero",
        "let2 own kit dig",
        "dig1 8 1 5 1",
        "dig2 3 6"};

    REQUIRE(expected_output == reorderLogFilesFA(logs));
}

TEST_CASE("Example 2", "[reorderLogFiles]")
{
    const std::vector<std::string> logs {
        "a1 9 2 3 1",
        "g1 act car",
        "zo4 4 7",
        "ab1 off key dog",
        "a8 act zoo"};

    const std::vector<std::string> expected_output {
        "g1 act car",
        "a8 act zoo",
        "ab1 off key dog",
        "a1 9 2 3 1",
        "zo4 4 7"};

    REQUIRE(expected_output == reorderLogFilesFA(logs));
}
