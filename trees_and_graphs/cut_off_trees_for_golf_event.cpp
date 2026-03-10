#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

static int cutOffTreeFA(const std::vector<std::vector<int>>& forest)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2986/
    //!
    //!          First attempt solution does not pass Example 1

    const auto num_rows    = static_cast<int>(std::ssize(forest));
    const auto num_cols    = static_cast<int>(std::ssize(forest.at(0)))
    auto       forest_copy = forest;

    int min_steps {};
    int prev_tree_height {1};

    //! Keep track of whether a tree at an index has been cut
    //! If the value at a cell is 0 or 1 then is_cut will store true
    std::vector<bool> is_tree_cut(num_rows * num_cols, false);

    const auto pos_to_index = [=](int row, int col) -> int {
        return row * num_cols + col;
    };

    const std::vector<std::pair<int, int>> directions {
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    const auto is_pos_valid = [=](int row, int col) -> bool {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    };

    //! Min heap/priority queue of tuple<tree height, row, col>
    //! where the smallest tree height is at the top
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>> neighbors;

    std::queue<std::pair<int, int>> pos_queue;
    pos_queue.emplace(0, 0);

    while (!pos_queue.empty())
    {
        const auto pos_queue_size = static_cast<int>(std::ssize(pos_queue));

        for (int num_cells = 0; num_cells < pos_queue_size; ++num_cells)
        {
            const auto [curr_row, curr_col] = pos_queue.front();
            pos_queue.pop();

            auto&     curr_height = forest_copy[curr_row][curr_col];
            const int curr_idx {pos_to_index(curr_row, curr_col)};

            if (curr_height == 0)
            {
                is_tree_cut[curr_idx] = true;
                continue;
            }

            is_tree_cut[curr_idx] = true;

            if (curr_height > prev_tree_height)
            {
                prev_tree_height = curr_height;
            }

            curr_height = 1;
            neighbors   = {};

            for (const auto& [drow, dcol] : directions)
            {
                const int next_row {curr_row + drow};
                const int next_col {curr_col + dcol};

                if (!is_pos_valid(next_row, next_col)
                    || forest_copy[next_row][next_col] == 0
                    || is_tree_cut[pos_to_index(next_row, next_col)])
                {
                    continue;
                }

                const int next_height {forest_copy[next_row][next_col]};

                if (next_height == 1)
                {
                    pos_queue.emplace(next_row, next_col);
                    continue;
                }

                neighbors.emplace(next_height, next_row, next_col);
            }

            if (!neighbors.empty())
            {
                const auto [min_height, min_row, min_col] = neighbors.top();
                pos_queue.emplace(min_row, min_col);
            }
        }

        ++min_steps;
    }

    return std::ranges::any_of(is_tree_cut, [](bool is_cut) { return !is_cut; })
        ? -1
        : min_steps;
}

static int cutOffTreeDS1(const std::vector<std::vector<int>>& forest)
{
    //! @details https://leetcode.com/problems/cut-off-trees-for-golf-event
    //!          /solutions/107403/c-sort-bfs-with-explanation-by-zestypand-8ebp

    if (forest.empty() || forest.front().empty())
    {
        return 0;
    }

    const auto num_rows = static_cast<int>(std::ssize(forest));
    const auto num_cols = static_cast<int>(std::ssize(forest.front()));

    //! Stores <tree height, row, col>
    std::vector<std::tuple<int, int, int>> trees;

    //! Get all the tree positions and sort based on height
    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (forest.at(row).at(col) > 1)
            {
                trees.emplace_back(forest.at(row).at(col), row, col);
            }
        }
    }

    //! Default comparator for tuples compares the first element before others
    std::ranges::sort(trees);

    const auto is_pos_valid = [=](int row, int col) -> bool {
        return row >= 0 && row < nums_rows && col >= 0 && col < num_cols;
    };

    const auto min_steps_between_trees = [&](int start_row,
                                             int start_col,
                                             int end_row,
                                             int end_col) -> int {
        if (start_row == end_row && start_col == end_col)
        {
            return 0;
        }

        std::queue<std::pair<int, int>> pos_queue;
        pos_queue.emplace(start_row, start_col);

        std::unordered_set<std::pair<int, int>> visited_pos;
        visited_pos.emplace(start_row, start_col);
    };

    int total_min_steps {};
    int curr_row {};
    int curr_col {};

    for (const auto& [next_tree_height, next_row, next_col] : trees)
    {
        const int min_steps {
            min_steps_between_trees(curr_row, curr_col, next_row, next_col)};

        //! If next tree cannot be reached then min_steps = -1
        if (min_steps == -1)
        {
            return -1;
        }

        total_min_steps += min_steps;
        curr_row = next_row;
        curr_col = next_col;
    }

    return total_min_steps;
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

    REQUIRE(-1 == cutOffTreeFA(forest));
    REQUIRE(6 != cutOffTreeFA(forest));
    REQUIRE(6 == cutOffTreeDS1(forest));
}

TEST_CASE("Example 2", "[cutOffTree]")
{
    // 1 2 3
    // 0 0 0
    // 7 6 5
    const std::vector<std::vector<int>> forest {
        {1, 2, 3}, {0, 0, 0}, {7, 6, 5}};

    // REQUIRE(-1 == cutOffTreeFA(forest));
    REQUIRE(-1 == cutOffTreeDS1(forest));
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

    // REQUIRE(6 == cutOffTreeFA(forest));
    REQUIRE(6 == cutOffTreeDS1(forest));
}
