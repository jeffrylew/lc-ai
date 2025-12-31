#include <catch2/catch_test_macros.hpp>

#include <vector>

static void rotateFA(const std::vector<std::vector<int>>& matrix)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2969/

    //! @todo
}

TEST_CASE("Example 1", "[rotate]")
{
    const std::vector<std::vector<int>> matrix {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    const std::vector<std::vector<int>> expected_output {
        {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

    REQUIRE(expected_output == rotateFA(matrix));
}

TEST_CASE("Example 2", "[rotate]")
{
    const std::vector<std::vector<int>> matrix {
        {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};

    const std::vector<std::vector<int>> expected_output {
        {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};

    REQUIRE(expected_output == rotateFA(matrix));
}
