#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

static std::vector<std::string> reorderLogFilesFA(
    const std::vector<std::string>& logs)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2974/
    //!
    //!          Time complexity O(N * log N) where N = logs.size(). In the
    //!          worst case, all logs are letter-logs so we need to sort N logs
    //!          lexicographically.
    //!          Space complexity O(N * M) to store N logs with an average of
    //!          M characters per log.

    struct Letter_log
    {
        std::string_view              log_view;
        std::string_view              identifier;
        std::vector<std::string_view> words;

        constexpr Letter_log(std::string_view log_line)
            : log_view {log_line}
        {
            const auto first_space_pos = log_view.find_first_of(' ');
            identifier                 = log_view.substr(0, first_space_pos);

            auto range_of_word_views =
                log_view.substr(first_space_pos + 1U) | std::views::split(' ');
            for (const auto& word_view : range_of_word_views)
            {
                words.emplace_back(word_view.begin(), word_view.end());
            }
        }
    };

    std::vector<Letter_log>       letter_logs;
    std::vector<std::string_view> digit_logs;

    for (const auto& log : logs)
    {
        const std::string_view log_view {log};

        if (std::isdigit(static_cast<unsigned char>(log.back())) != 0)
        {
            digit_logs.push_back(log_view);
            continue;
        }

        letter_logs.emplace_back(log_view);
    }

    std::ranges::sort(letter_logs,
                      [](const Letter_log& lhs, const Letter_log& rhs) {
                          if (lhs.words == rhs.words)
                          {
                              return lhs.identifier < rhs.identifier;
                          }
    
                          return lhs.words < rhs.words;
                      });

    std::vector<std::string> final_order;
    final_order.reserve(logs.size());

    for (const auto& letter_log : letter_logs)
    {
        final_order.emplace_back(std::string {letter_log.log_view});
    }

    for (const auto& digit_log : digit_logs)
    {
        final_order.emplace_back(std::string {digit_log});
    }

    return final_order;
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
