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

static std::vector<std::string> reorderLogFilesDS1(
    const std::vector<std::string>& logs)
{
    //! @details leetcode.com/problems/reorder-data-in-log-files/editorial
    //!
    //!          Time complexity O(M * N * log N) where M = the max length of a
    //!          single log and N = the number of logs in the list. The time
    //!          complexity of std::ranges::stable_sort is O(N * log N) if extra
    //!          memory is available (O(N * log^2(N)) otherwise), where the
    //!          lambda is invoked O(N * log N) times. Each invocation can take
    //!          up to O(M) since we compare the contents of the logs.
    //!          Space complexity O(M * log N) in the worst case when sufficient
    //!          extra memory is not available, otherwise O(M * N). If enough
    //!          extra memory is available then std::ranges::sort takes O(N),
    //!          where N is the number of logs. Since each log can use O(M)
    //!          space, the space complexity is O(M * N). Each invocation of the
    //!          lambda uses O(1) space due to the use of std::string_view.

    auto reordered_logs = logs;

    const auto is_digit = [](char ch) -> bool {
        return std::isdigit(static_cast<unsigned char>(ch)) != 0;
    };

    std::ranges::stable_sort(
        reordered_logs,
        [&](std::string_view lhs_log, std::string_view rhs_log) -> bool {
            const auto lhs_space_pos = lhs_log.find(' ');
            // assert(lhs_space_pos != std::string_view::npos);
            std::string_view lhs_identifier {lhs_log.substr(0, lhs_space_pos)};
            std::string_view lhs_words {lhs_log.substr(lhs_space_pos + 1)};

            const auto rhs_space_pos = rhs_log.find(' ');
            // assert(rhs_space_pos != std::string_view::npos);
            std::string_view rhs_identifier {rhs_log.substr(0, rhs_space_pos)};
            std::string_view rhs_words {rhs_log.substr(rhs_space_pos + 1)};

            //! Case 1) Both logs are letter-logs
            if (!is_digit(lhs_words[0]) && !is_digit(rhs_words[0]))
            {
                //! Log have same content, compare the identifiers
                if (lhs_words == rhs_words)
                {
                    return lhs_identifier < rhs_identifier;
                }

                //! Logs don't have the same content
                return lhs_words < rhs_words;
            }

            //! Case 2) One of the logs is a digit-log
            if (!is_digit(lhs_words[0]) && is_digit(rhs_words[0]))
            {
                //! lhs letter-log comes before the rhs digit-log
                //! i.e. (lhs_log < rhs_log) is true
                return true;
            }
            else if (is_digit(lhs_words[0]) && !is_digit(rhs_words[0]))
            {
                //! lhs digit-log comes after the rhs letter-log
                //! i.e. (lhs_log < rhs_log) is false
                return false;
            }

            //! Case 3) Both logs are digit-logs
            //! The lhs digit-log should be equal to the rhs digit-log so they
            //! do not get sorted and instead their relative order is maintained
            //! i.e. (lhs_log < rhs_log) is false since (lhs_log == rhs_log)
            return false;
        });

    return reordered_logs;
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
    REQUIRE(expected_output == reorderLogFilesDS1(logs));
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
    REQUIRE(expected_output == reorderLogFilesDS1(logs));
}
