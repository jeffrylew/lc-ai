#include <catch2/catch_test_macros.hpp>

#include <algorithm>
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

static void transpose(std::vector<std::vector<int>>& matrix)
{
    const auto matrix_size = static_cast<int>(std::ssize(matrix));

    for (int i = 0; i < matrix_size; ++i)
    {
        for (int j = i + 1; j < matrix_size; ++j)
        {
            std::swap(matrix[j][i], matrix[i][j]);
        }
    }
}

static void reflect(std::vector<std::vector<int>>& matrix)
{
    const auto matrix_size = static_cast<int>(std::ssize(matrix));

    for (int row = 0; row < matrix_size; ++row)
    {
        for (int col = 0; col < matrix_size / 2; ++col)
        {
            std::swap(matrix[row][col], matrix[row][matrix_size - col - 1]);
        }
    }
}

static void rotateDS2(std::vector<std::vector<int>>& matrix)
{
    //! @details https://leetcode.com/problems/rotate-image/editorial/
    //!
    //!          Time complexity O(M) where M = number of cells in the grid. We
    //!          transpose the matrix and reverse each row. Transposing the
    //!          matrix costs O(M) since we're moving the value of each cell
    //!          once. Reversing each row also costs O(M) for the same reason.
    //!          Space complexity O(1).

    transpose(matrix);
    reflect(matrix);
}

TEST_CASE("Example 1", "[rotate]")
{
    // 1 2 3    7 4 1
    // 4 5 6 -> 8 5 2
    // 7 8 9    9 6 3
    const std::vector<std::vector<int>> matrix {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto matrix_copy = matrix;

    const std::vector<std::vector<int>> expected_output {
        {7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

    // for i = 0 to (3 + 1) / 2 = 2
    //   for j = 0 to 3 / 2 = 1
    //     - i = 0; j = 0
    //       temp     = mc[3 - 1 - 0][0]         = mc[2][0] // temp     = 7
    //       mc[2][0] = mc[3 - 1 - 0][3 - 0 - 1] = mc[2][2] // mc[2][0] = 9
    //       mc[2][2] = mc[0][3 - 1 - 0]         = mc[0][2] // mc[2][2] = 3
    //       mc[0][2] = mc[0][0]                            // mc[0][2] = 1
    //       mc[0][0] = temp                                // mc[0][0] = 7
    //     - i = 1; j = 0
    //       temp     = mc[3 - 1 - 0][1]         = mc[2][1] // temp     = 8
    //       mc[2][1] = mc[3 - 1 - 1][3 - 0 - 1] = mc[1][2] // mc[2][1] = 6
    //       mc[1][2] = mc[0][3 - 1 - 1]         = mc[0][1] // mc[1][2] = 2
    //       mc[0][1] = mc[1][0]                            // mc[0][1] = 4
    //       mc[1][0] = temp                                // mc[1][0] = 8
    REQUIRE(expected_output == rotateDS1(matrix_copy));

    //       Transpose  Reflect/Reverse
    // 1 2 3    1 4 7    7 4 1
    // 4 5 6 -> 2 5 8 -> 8 5 2
    // 7 8 9    3 6 9    9 6 3

    //         Reflect  Transpose
    // 1 2 3    3 2 1    3 6 9
    // 4 5 6 -> 6 5 4 -> 2 5 8     INCORRECT, must transpose before reflect
    // 7 8 9    9 8 7    1 4 7
    REQUIRE(expected_output == rotateDS2(matrix_copy));
}

TEST_CASE("Example 2", "[rotate]")
{
    // 05 01 09 11    15 13 02 05
    // 02 04 08 10 -> 14 03 04 01
    // 13 03 06 07    12 06 08 09
    // 15 14 12 16    16 07 10 11
    const std::vector<std::vector<int>> matrix {
        {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
    auto matrix_copy = matrix;

    const std::vector<std::vector<int>> expected_output {
        {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}};

    REQUIRE(expected_output == rotateDS1(matrix_copy));
    REQUIRE(expected_output == rotateDS2(matrix_copy));
}
