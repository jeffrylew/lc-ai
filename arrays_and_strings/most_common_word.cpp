#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cctype>
#include <iterator>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

static std::string mostCommonWordFA(std::string                     paragraph,
                                    const std::vector<std::string>& banned)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2973
    //!
    //!          Code won't run in LC because it uses libstdc++ from GCC 14 and
    //!          I believe std::from_range requires GCC 15. I confirmed the
    //!          desired behavior with godbolt: https://godbolt.org/z/M79neGTqe
    //!
    //!          Time complexity O(P + B) where P = paragraph.size() and
    //!          B = banned.size(). We iterate through paragraph to tokenize it
    //!          into lowercase words in O(P) and creating the banned_words set
    //!          takes O(B).
    //!          Space complexity O(W + B) where W is the number of unique
    //!          words in paragraph (excluding banned words) and B is the number
    //!          of banned words.

    const std::unordered_set<std::string> banned_words(std::from_range, banned);

    auto tokenize = [](std::string_view words) {
        auto adjacent_letters = [](unsigned char lhs, unsigned char rhs) {
            return std::isalpha(lhs) > 0 && std::isalpha(rhs) > 0;
        };

        auto is_letter = [](auto ch) {
            return std::isalpha(static_cast<unsigned char>(ch[0])) > 0;
        };

        return words
            | std::views::chunk_by(adjacent_letters)
            | std::views::filter(is_letter);
    };

    auto to_lowercase_str =
        [](std::ranges::subrange<const char*,
                                 const char*,
                                 std::ranges::subrange_kind::sized>& word_view)
        {
            std::string lowercase_str;
            lowercase_str.reserve(word_view.size());

            auto to_lowercase = [](unsigned char ch) {
                return static_cast<char>(std::tolower(ch));
            };

            std::ranges::transform(word_view.begin(),
                                   word_view.end(),
                                   std::back_inserter(lowercase_str),
                                   to_lowercase);

            return lowercase_str;
        };

    std::unordered_map<std::string, int> word_counts;

    for (auto word_view : tokenize(paragraph))
    {
        auto word = to_lowercase_str(word_view);

        if (!banned_words.contains(word))
        {
            ++word_counts[std::move(word)];
        }
    }

    int         max_word_count {};
    std::string most_freq_word;

    for (auto& [word, word_count] : word_counts)
    {
        if (word_count > max_word_count)
        {
            max_word_count = word_count;
            most_freq_word = std::move(word);
        }
    }

    return most_freq_word;
}

static std::string mostCommonWordDS1(std::string                     paragraph,
                                     const std::vector<std::string>& banned)
{
    //! @details https://leetcode.com/problems/most-common-word/editorial/
    //!
    //!          Time complexity O(N + M) where N = paragraph.size() and
    //!          M = number of characters in the banned list. It takes O(N) time
    //!          to process each stage of the pipeline. Building a set out of
    //!          the banned words takes O(M).
    //!          Space complexity O(N + M). The hashmap counting the frequency
    //!          of each unique word uses O(N) space. The set of banned words
    //!          uses O(M) space.

    //! 1. Replace the punctuation with spaces and convert letters to lower case
    std::regex  capture_punctuation {"[^a-zA-Z0-9 ]"};
    std::string normalized_paragraph {
        std::regex_replace(paragraph, capture_punctuation, " ")};
    std::ranges::transform(normalized_paragraph,
                           normalized_paragraph.begin(),
                           [](unsigned char ch) {
                               return static_cast<char>(std::tolower(ch));
                           });

    //! 2. Convert banned words vector to a set
    const std::unordered_set<std::string> banned_words(
        banned.begin(), banned.end());

    //! 3. Split the string into words and count the appearance of each word,
    //!    excluding the banned words
    std::unordered_map<std::string, int> word_counts;

    std::istringstream word_stream(normalized_paragraph);
    for (std::string word; std::getline(word_stream, word, ' ');)
    {
        if (!word.empty() && !banned_words.contains(word))
        {
            ++word_counts[std::move(word)];
        }
    }

    //! 4. Return the word with the highest frequency
    auto highest_freq_it =
        std::max_element(word_counts.begin(),
                         word_counts.end(),
                         [](const std::pair<std::string, int>& lhs,
                            const std::pair<std::string, int>& rhs) {
                             return lhs.second < rhs.second;
                         });

    //! highest_freq_it only equals end() if word_counts is empty
    return highest_freq_it != word_counts.end() ? highest_freq_it->first : "";
}

static std::string mostCommonWordDS2(std::string                     paragraph,
                                     const std::vector<std::string>& banned)
{
    //! @details https://leetcode.com/problems/most-common-word/editorial/
    //!
    //!          Time complexity O(N + M) where N = paragraph.size() and M is
    //!          the number of characters in the banned list.
    //!          Space complexity O(N + M). We build a hashmap using O(N) to
    //!          count the frequency of each unique word. We also build a set
    //!          out of the banned words list using O(M).

    const std::unordered_set<std::string> banned_words(
        banned.begin(), banned.end());

    std::string word_buffer;
    std::string most_freq_word;
    int         max_word_count {};

    std::unordered_map<std::string, int> word_counts;

    const auto paragraph_size = static_cast<int>(std::ssize(paragraph));

    for (int pos = 0; pos < paragraph_size; ++pos)
    {
        const auto curr_char = static_cast<unsigned char>(paragraph[pos]);

        //! 1. Consume the characters in a word
        if (std::isalpha(curr_char) != 0)
        {
            word_buffer += static_cast<char>(std::tolower(curr_char));
            if (pos != paragraph_size - 1)
            {
                continue;
            }
        }

        //! 2.) At the end of a word or at the end of the paragraph
        if (!word_buffer.empty())
        {
            //! Identify the max count while updating word_counts
            if (!banned_words.contains(word_buffer))
            {
                const int curr_word_count {++word_counts[word_buffer]};

                if (curr_word_count > max_word_count)
                {
                    most_freq_word = std::move(word_buffer);
                    max_word_count = curr_word_count;
                }
            }

            word_buffer.clear();
        }
    }

    return most_freq_word;
}

TEST_CASE("Example 1", "[mostCommonWord]")
{
    const std::string paragraph {
        "Bob hit a ball, the hit BALL flew far after it was hit."};
    const std::vector<std::string> banned {"hit"};

    REQUIRE("ball" == mostCommonWordFA(paragraph, banned));
    REQUIRE("ball" == mostCommonWordDS1(paragraph, banned));
    REQUIRE("ball" == mostCommonWordDS2(paragraph, banned));
}

TEST_CASE("Example 2", "[mostCommonWord]")
{
    const std::string              paragraph {"a."};
    const std::vector<std::string> banned {};

    REQUIRE("a" == mostCommonWordFA(paragraph, banned));
    REQUIRE("a" == mostCommonWordDS1(paragraph, banned));
    REQUIRE("a" == mostCommonWordDS2(paragraph, banned));
}
