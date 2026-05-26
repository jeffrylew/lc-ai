#include <catch2/catch_test_macros.hpp>

#include <vector>

//! @class TicTacToeFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/design/517/
class TicTacToeFA
{
public:
    explicit TicTacToeFA(int n)
        : board_size {n}
        , board {std::vector<std::vector<int>>(n, std::vector<int>(n, 0))}
    {
    }

    int move(int row, int col, int player)
    {
        board[row][col] = player;

        if (++num_moves < 2 * board_size - 1)
        {
            //! Less than the minimum required number of moves
            return 0;
        }

        if ((board_size - row - 1 == col && is_winner_on_anti_diagonal(player))
            || (row == col && is_winner_on_diagonal(player))
            || is_winner_on_row(player, row)
            || is_winner_on_col(player, col))
        {
            return player;
        }

        return 0;
    }

private:
    int board_size {};
    int num_moves {};

    std::vector<std::vector<int>> board; 

    //! @brief Check if player is a winner on the left-to-right diagonal
    //! @param[in] player Player ID
    //! @return True if player is a winner on left-to-right diagonal, else false
    [[nodiscard]] bool is_winner_on_diagonal(int player)
    {
        for (int idx = 0; idx < board_size; ++idx)
        {
            if (board[idx][idx] != player)
            {
                return false;
            }
        }

        return true;
    }

    //! @brief Check if player is a winner on the right-to-left diagonal
    //! @param[in] player Player ID
    //! @return True if player is a winner on right-to-left diagonal, else false
    [[nodiscard]] bool is_winner_on_anti_diagonal(int player)
    {
        for (int idx = 0; idx < board_size; ++idx)
        {
            if (board[idx][board_size - idx - 1] != player)
            {
                return false;
            }
        }

        return true;
    }

    //! @brief Check if player is a winner on row
    //! @param[in] player Player ID
    //! @return True if player is a winner on row, else false
    [[nodiscard]] bool is_winner_on_row(int player, int row)
    {
        for (int col = 0; col < board_size; ++col)
        {
            if (board[row][col] != player)
            {
                return false;
            }
        }

        return true;
    }

    //! @brief Check if player is a winner on col
    //! @param[in] player Player ID
    //! @return True if player is a winner on col, else false
    [[nodiscard]] bool is_winner_on_col(int player, int col)
    {
        for (int row = 0; row < board_size; ++row)
        {
            if (board[row][col] != player)
            {
                return false;
            }
        }

        return true;
    }
};

//! @class TicTacToeDS1
//! @details https://leetcode.com/problems/design-tic-tac-toe/editorial/
class TicTacToeDS1
{
public:
    explicit TicTacToeDS1(int n)
        : board_size {n}
        , board {std::vector<std::vector<int>>(n, std::vector<int>(n, 0))}
    {
    }

    int move(int row, int col, int player)
    {
        board[row][col] = player;

        if (check_col(col, player)
            || check_row(row, player)
            || (row == col && check_diagonal(player))
            || (row == board_size - col - 1 && check_anti_diagonal(player)))
        {
            return player;
        }

        //! No one wins
        return 0;
    }

private:
    int board_size {};

    std::vector<std::vector<int>> board; 
};

TEST_CASE("Example 1", "[TicTacToe]")
{
    //! Assume player 1 is 'X' and player 2 is 'O'
    TicTacToeFA tictactoefa {3};

    //! Player 1 makes a move at (0, 0). Return 0, no one wins.
    //! |X| | |
    //! | | | |
    //! | | | |
    CHECK(0 == tictactoefa.move(0, 0, 1));

    //! Player 2 makes a move at (0, 2). Return 0, no one wins.
    //! |X| |O|
    //! | | | |
    //! | | | |
    CHECK(0 == tictactoefa.move(0, 2, 2));

    //! Player 1 makes a move at (2, 2). Return 0, no one wins.
    //! |X| |O|
    //! | | | |
    //! | | |X|
    CHECK(0 == tictactoefa.move(2, 2, 1));

    //! Player 2 makes a move at (1, 1). Return 0, no one wins.
    //! |X| |O|
    //! | |O| |
    //! | | |X|
    CHECK(0 == tictactoefa.move(1, 1, 2));

    //! Player 1 makes a move at (2, 0). Return 0, no one wins.
    //! |X| |O|
    //! | |O| |
    //! |X| |X|
    CHECK(0 == tictactoefa.move(2, 0, 1));

    //! Player 2 makes a move at (1, 0). Return 0, no one wins.
    //! |X| |O|
    //! |O|O| |
    //! |X| |X|
    CHECK(0 == tictactoefa.move(1, 0, 2));

    //! Player 1 makes a move at (2, 1). Return 1, player 1 wins.
    //! |X| |O|
    //! |O|O| |
    //! |X|X|X|
    CHECK(1 == tictactoefa.move(2, 1, 1));

    TicTacToeDS1 tictactoeds1 {3};
    CHECK(0 == tictactoeds1.move(0, 0, 1));
    CHECK(0 == tictactoeds1.move(0, 2, 2));
    CHECK(0 == tictactoeds1.move(2, 2, 1));
    CHECK(0 == tictactoeds1.move(1, 1, 2));
    CHECK(0 == tictactoeds1.move(2, 0, 1));
    CHECK(0 == tictactoeds1.move(1, 0, 2));
    CHECK(1 == tictactoeds1.move(2, 1, 1));
}
