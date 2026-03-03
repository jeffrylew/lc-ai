#include <catch2/catch_test_macros.hpp>

#include <vector>

static int cutOffTreeFA(const std::vector<std::vector<int>>& forest)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2986/


}

TEST_CASE("Example 1", "[cutOffTree]")
{
    // 1 -> 2 -> 3
    //           v
    // 0    0    4
    //           v
    // 7 <- 6 <- 5
    const std::vector<std::vector<int>> forest {
        {1, 2, 3}, {0, 0, 4}, {7, 6, 5}};

    REQUIRE(6 == cutOffTreeFA(forest));
}

TEST_CASE("Example 2", "[cutOffTree]")
{
    // 1 2 3
    // 0 0 0
    // 7 6 5
    const std::vector<std::vector<int>> forest {
        {1, 2, 3}, {0, 0, 0}, {7, 6, 5}};

    REQUIRE(-1 == cutOffTreeFA(forest));
}

TEST_CASE("Example 3", "[cutOffTree]")
{
    // 2 -> 3 -> 4
    //           v
    // 0    0    5
    //           v
    // 8 <- 7 <- 6
    const std::vector<std::vector<int>> forest {
        {2, 3, 4}, {0, 0, 5}, {8, 7, 6}};

    REQUIRE(6 == cutOffTreeFA(forest));
}
