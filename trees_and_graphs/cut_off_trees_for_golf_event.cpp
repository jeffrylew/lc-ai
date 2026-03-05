#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

static int cutOffTreeFA(const std::vector<std::vector<int>>& forest)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2986/

    const auto num_rows    = static_cast<int>(std::ssize(forest));
    const auto num_cols    = static_cast<int>(std::ssize(forest.at(0)))
    auto       forest_copy = forest;

    int min_steps {};

    //! Keep track of whether a tree at an index has been cut
    //! If the value at a cell is 0 or 1 then is_cut will store true
    std::vector<bool> is_tree_cut(num_rows * num_cols, false);

    constexpr auto pos_to_index = [=](int row, int col) -> int {
        return row * num_cols + col;
    };

    const std::vector<std::pair<int, int>> directions {
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    constexpr auto is_pos_valid = [=](int row, int col) -> bool {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    };

    std::queue<std::pair<int, int>> pos_queue;
    pos_queue.emplace(0, 0);

    while (!pos_queue.empty())
    {
        const auto pos_queue_size = static_cast<int>(std::ssize(pos_queue));

        for (int num_cells = 0; num_cells < pos_queue_size; ++num_cells)
        {
            const auto [curr_row, curr_col] = pos_queue.front();
            pos_queue.pop();

            auto&     cell_value = forest_copy[curr_row][curr_col];
            const int curr_idx {pos_to_index(curr_row, curr_col)};

            if (cell_value == 0)
            {
                is_tree_cut[curr_idx] = true;
                continue;
            }

            is_tree_cut[curr_idx] = true;

            cell_value = 1;

            for (const auto& [drow, dcol] : directions)
            {
                const int next_row {curr_row + drow};
                const int next_col {curr_col + dcol};

                if (!is_pos_valid(next_row, next_col)
                    || forest_copy[next_row][next_col] == 0)
                {
                    continue;
                }

                //! @todo
            }
        }

        ++min_steps;
    }

    return std::ranges::any_of(is_tree_cut, [](bool is_cut) { return !is_cut; })
        ? -1
        : min_steps;
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
