#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <string>
#include <utility>
#include <vector>

static bool existFA(const std::vector<std::vector<char>>& board,
                    const std::string&                    word)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/84
    //!          /recursion/2989/
    //!
    //!          First attempt solution does not pass Example 4.
    //!          Need to backtrack and use recursion instead since visited cells
    //!          can be revisited later in the word.

    const auto num_rows = static_cast<int>(std::ssize(board));
    const auto num_cols = static_cast<int>(std::ssize(board[0]));

    const std::vector<std::pair<int, int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    const auto is_valid = [&](int row, int col) {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    };

    std::queue<std::pair<int, int>> cell_pos_queue;

    int word_idx {};

    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (board[row][col] != word[0])
            {
                continue;
            }

            //! Avoid creating a 2D vector multiple times
            std::vector<std::vector<bool>> visited_cells(
                num_rows, std::vector<bool>(num_cols));

            cell_pos_queue.emplace(row, col);

            while (!cell_pos_queue.empty())
            {
                if (word_idx == std::ssize(word) - 1)
                {
                    return true;
                }

                const auto curr_num_cells =
                    static_cast<int>(std::ssize(cell_pos_queue));

                ++word_idx;

                for (int cell = 0; cell < curr_num_cells; ++cell)
                {
                    const auto [curr_row, curr_col] = cell_pos_queue.front();
                    cell_pos_queue.pop();

                    visited_cells[curr_row][curr_col] = true;

                    for (const auto& [drow, dcol] : directions)
                    {
                        const int next_row {curr_row + drow};
                        const int next_col {curr_col + dcol};

                        if (is_valid(next_row, next_col)
                            && !visited_cells[next_row][next_col]
                            && board[next_row][next_col] == word[word_idx])
                        {
                            cell_pos_queue.emplace(next_row, next_col);
                        }
                    }
                }
            }

            word_idx = 0;
        }
    }

    return false;

} // static bool existFA( ...

static bool existSA(const std::vector<std::vector<char>>& board,
                    const std::string&                    word)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/84
    //!          /recursion/2989/

    const auto num_rows = static_cast<int>(std::ssize(board));
    const auto num_cols = static_cast<int>(std::ssize(board[0]));

    const std::vector<std::pair<int, int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    const auto is_valid = [&](int row, int col) {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    };

    std::vector<std::vector<bool>> visited_cells(
        num_rows, std::vector<bool>(num_cols));

    const std::function<bool(int, int, int)> word_exists =
        [&](int row, int col, int word_idx) {
            visited_cells[row][col] = true;

            if (word_idx == std::ssize(word) - 1)
            {
                return word.back() == board[row][col];
            }

            if (word[word_idx] != board[row][col])
            {
                return false;
            }

            bool exists {};

            for (const auto& [drow, dcol] : directions)
            {
                const int next_row {row + drow};
                const int next_col {col + dcol};

                if (is_valid(next_row, next_col)
                    && !visited_cells[next_row][next_col])
                {
                    exists =
                        exists || word_exists(next_row, next_col, word_idx + 1);

                    visited_cells[next_row][next_col] = false;
                }
            }

            return exists;
        };

    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (word_exists(row, col, 0))
            {
                return true;
            }

            visited_cells = std::vector<std::vector<bool>>(
                num_rows, std::vector<bool>(num_cols));
        }
    }

    return false;
}

static bool existDS1(const std::vector<std::vector<char>>& board,
                     const std::string&                    word)
{
    //! @details https://leetcode.com/problems/word-search/editorial/
    //!
    //!          Time complexity O(N * 3 ^ L) where N = number of cells in the
    //!          board and L is the length of the word to match. For the
    //!          backtracking function, we have 3 directions to explore since we
    //!          can't go back to where we came from. Therefore, in the worst
    //!          case, the total number of invocations would be the number of
    //!          nodes in a full 3-ary tree, which is about 3 ^ L.
    //!          Space complexity O(L) for the maximum length of the call stack,
    //!          which is the length of the word.

    auto board_copy = board;

    const auto num_rows = static_cast<int>(std::ssize(board_copy));
    const auto num_cols = static_cast<int>(std::ssize(board_copy[0]));

    std::function<bool(int, int, int)> backtrack =
        [&](int row, int col, int index) {
            if (index >= std::ssize(word))
            {
                return true;
            }

            if (row < 0
                || row == num_rows
                || col < 0
                || col == num_cols
                || board_copy[row][col] != word[index])
            {
                return false;
            }

            bool word_exists {};

            //! Mark path before exploring neighbors
            board_copy[row][col] = '#';

            const std::vector<std::pair<int, int>> offsets {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            for (const auto& [row_offset, col_offset] : offsets)
            {
                /*
                word_exists = backtrack(row + row_offset,
                                        col + col_offset,
                                        index + 1);
                if (word_exists)
                {
                    break;
                }
                 */

                //! Alternatively, without restoring board or board_copy
                if (backtrack(row + row_offset, col + col_offset, index + 1))
                {
                    return true;
                }
            }

            board_copy[row][col] = word[index];
            // return word_exists;
            return false;
        };

    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (backtrack(row, col, 0))
            {
                return true;
            }
        }
    }

    return false;
}

TEST_CASE("Example 1", "[exist]")
{
    const std::vector<std::vector<char>> board {{'A', 'B', 'C', 'E'},
                                                {'S', 'F', 'C', 'S'},
                                                {'A', 'D', 'E', 'E'}};

    const std::string word {"ABCCED"};

    REQUIRE(existFA(board, word));
    REQUIRE(existSA(board, word));
    REQUIRE(existDS1(board, word));
}

TEST_CASE("Example 2", "[exist]")
{
    const std::vector<std::vector<char>> board {{'A', 'B', 'C', 'E'},
                                                {'S', 'F', 'C', 'S'},
                                                {'A', 'D', 'E', 'E'}};

    const std::string word {"SEE"};

    REQUIRE(existFA(board, word));
    REQUIRE(existSA(board, word));
    REQUIRE(existDS1(board, word));
}

TEST_CASE("Example 3", "[exist]")
{
    const std::vector<std::vector<char>> board {{'A', 'B', 'C', 'E'},
                                                {'S', 'F', 'C', 'S'},
                                                {'A', 'D', 'E', 'E'}};

    const std::string word {"ABCB"};

    REQUIRE(!existFA(board, word));
    REQUIRE(!existSA(board, word));
    REQUIRE(!existDS1(board, word));
}

TEST_CASE("Example 4", "[exist]")
{
    const std::vector<std::vector<char>> board {{'A', 'B', 'C', 'E'},
                                                {'S', 'F', 'E', 'S'},
                                                {'A', 'D', 'E', 'E'}};

    const std::string word {"ABCESEEEFS"};

    // REQUIRE(existFA(board, word));
    // REQUIRE(existSA(board, word));
    REQUIRE(existDS1(board, word));
}
