#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

static std::vector<int> partitionLabelsFA(std::string s)
{
    //! @details leetcode.com/explore/interview/card/amazon/82/others/3004
}

TEST_CASE("Example 1", "[partitionLabels]")
{
    const std::string      s {"ababcbacadefegdehijhklij"};
    const std::vector<int> expected_output {9, 7, 8};

    REQUIRE(expected_output == partitionLabelsFA(s));
}

TEST_CASE("Example 2", "[partitionLabels]")
{
    const std::string      s {"eccbbbbdec"};
    const std::vector<int> expected_output {10};

    REQUIRE(expected_output == partitionLabelsFA(s));
}
