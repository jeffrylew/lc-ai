#include <catch2/catch_test_macros.hpp>

//! @class TicTacToeFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/design/517/
class TicTacToeFA
{
public:
    explicit TicTacToeFA(int n)
    {
    }

    int move(int row, int col, int player)
    {
        //! @todo
    }
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
}
