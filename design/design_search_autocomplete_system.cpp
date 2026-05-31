#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

//! @class AutocompleteSystemFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/others/3000/
class AutocompleteSystemFA
{
public:
    AutocompleteSystemFA(const std::vector<std::string>& sentences,
                         const std::vector<int>&         time)
    {
    }

    std::vector<std::string> input(char c)
    {
        //! @todo
    }
};

TEST_CASE("Example 1", "[AutocompleteSystem]")
{
    const std::vector<std::string> sentences {
        "i love you", "island", "ironman", "i love leetcode"};
    const std::vector<int> time {5, 3, 2, 2};

    const std::vector<std::string> expected_output1 {
        "i love you", "island", "i love leetcode"};
    const std::vector<std::string> expected_output2 {
        "i love you", "i love leetcode"};

    AutocompleteSystemFA system_fa {sentences, time};

    //! There are four sentences that have prefix 'i'. Among them, "ironman" and
    //! "i love leetcode" have the same hot degree. Since ' ' has ASCII code 32
    //! and 'r' has ASCII code 114, "i love leetcode" should be in front of
    //! "ironman". Also, we only need to output the top 3 hot sentences, so
    //! "ironman" will be ignored.
    CHECK(expected_output1 == system_fa.input('i'));

    //! There are only two sentences that have prefix "i "
    CHECK(expected_output2 == system_fa.input(' '));

    //! There are no sentences that have prefix "i a"
    CHECK(system_fa.input('a').empty());

    //! The user finished the input, the sentence "i a" should be saved as a
    //! historical sentence in the system. And the following input will be
    //! counted as a new search.
    CHECK(system_fa.input('#').empty());
}
