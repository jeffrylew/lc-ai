#include <catch2/catch_test_macros.hpp>

#include <vector>

//! @brief First attempt solution to get number of islands from an M x N grid
//! @param[in] grid Reference to an M x N 2D grid of 1s (land) and 0s (water)
//! @return Number of islands
static int numIslandsFA(const std::vector<std::vector<char>>& grid)
{
    //! @todo
}

TEST_CASE("Example 1", "[NumIslands]")
{
    const std::vector<std::vector<char>> grid {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}};

    REQUIRE(1 == numIslandsFA(grid));
}

TEST_CASE("Example 2", "[NumIslands]")
{
    const std::vector<std::vector<char>> grid {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};

    REQUIRE(1 == numIslandsFA(grid));
}