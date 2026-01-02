#include <catch2/catch_test_macros.hpp>

#include <vector>

static void rotateDS1(std::vector<std::vector<int>>& matrix)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/2969/
    //!
    //!          Time complexity O(M) where M = number of cells in the matrix.
    //!          Each cell is read and written once.
    //!          Space complexity O(1).

    const auto n = static_cast<int>(std::ssize(matrix));

    for (int i = 0; i < (n + 1) / 2; ++i)
    {
        for (int j = 0; j < n / 2; ++j)
        {
            const int temp {matrix[n - 1 - j][i]};

            matrix[n - 1 - j][i]         = matrix[n - 1 - i][n - j - 1];
            matrix[n - 1 - i][n - j - 1] = matrix[j][n - 1 - i];
            matrix[j][n - 1 - i]         = matrix[i][j];
            matrix[i][j]                 = temp;
        }
    }
}

TEST_CASE("Example 1", "[rotate]")
{
    const std::vector<std::vector<int>> matrix {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto matrix_copy = matrix;

    const std::vector<std::vector<int>> expected_output {
        {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

    REQUIRE(expected_output == rotateDS1(matrix_copy));
}

TEST_CASE("Example 2", "[rotate]")
{
    const std::vector<std::vector<int>> matrix {
        {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
    auto matrix_copy = matrix;

    const std::vector<std::vector<int>> expected_output {
        {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};

    REQUIRE(expected_output == rotateDS1(matrix_copy));
}
