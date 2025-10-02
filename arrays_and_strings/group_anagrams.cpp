#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

static std::vector<std::vector<std::string>>
    groupAnagramsFA(const std::vector<std::string>& strs)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2970/

    
}

TEST_CASE("Example 1", "[groupAnagrams]")
{
    const std::vector<std::string> strs {
        "eat", "tea", "tan", "ate", "nat", "bat"};

    const std::vector<std::vector<std::string>> expected_output {
        {"bat"}, {"nat", "tan"}, {"ate", "eat", "tea"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}

TEST_CAST("Example 2", "[groupAnagrams]")
{
    const std::vector<std::string> strs {""};

    const std::vector<std::vector<std::string>> expected_output {{""}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}

TEST_CAST("Example 3", "[groupAnagrams]")
{
    const std::vector<std::string> strs {"a"};

    const std::vector<std::vector<std::string>> expected_output {{"a"}};

    REQUIRE(expected_output == groupAnagramsFA(strs));
}
