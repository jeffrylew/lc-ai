#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <stack>
#include <unordered_set>
#include <utility>
#include <vector>

static std::vector<std::vector<int>> floodFillFA(
    const std::vector<std::vector<int>>& image,
    int                                  sr,
    int                                  sc,
    int                                  color)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2987/
    //!
    //!          Time complexity O(R * C) where R = number of rows in image and
    //!          C = number of columns in image. In the worst case, DFS will
    //!          visit each pixel in the image.
    //!          Space complexity O(R * C) since visited_pos could contain the
    //!          indices of all cells in the worst case.

    const auto num_rows = static_cast<int>(std::ssize(image));
    const auto num_cols = static_cast<int>(std::ssize(image[0]));

    const auto is_pos_valid = [num_rows, num_cols](int row, int col) -> bool {
        return row >= 0 && row < num_rows && col >= 0 && col < num_cols;
    };

    const auto pos_to_index = [num_cols](int row, int col) -> int {
        return row * num_cols + col;
    };

    const std::vector<std::pair<int, int>> neighbors {
        {0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    auto                            filled_image = image;
    std::unordered_set<int>         visited_pos;
    std::stack<std::pair<int, int>> pos_stack;
    pos_stack.emplace(sr, sc);

    const int start_color {filled_image[sr][sc]};

    while (!pos_stack.empty())
    {
        const auto [curr_row, curr_col] = pos_stack.top();
        pos_stack.pop();
        visited_pos.insert(pos_to_index(curr_row, curr_col));

        filled_image[curr_row][curr_col] = color;

        for (const auto& [drow, dcol] : neighbors)
        {
            const int next_row {curr_row + drow};
            const int next_col {curr_col + dcol};

            if (!is_pos_valid(next_row, next_col)
                || filled_image[next_row][next_col] != start_color
                || visited_pos.contains(pos_to_index(next_row, next_col)))
            {
                continue;
            }

            pos_stack.emplace(next_row, next_col);
        }
    }

    return filled_image;
}

static std::vector<std::vector<int>> floodFillDS1(
    const std::vector<std::vector<int>>& image,
    int                                  sr,
    int                                  sc,
    int                                  color)
{
    //! @details https://leetcode.com/problems/flood-fill/editorial/
    //!
    //!          Time complexity O(N) where N = num_rows * num_cols i.e. the
    //!          number of pixels in the image. We might process every pixel.
    //!          Space complexity O(N) for the size of the call stack when
    //!          calling flood_fill_dfs.

    auto       filled_image = image;
    const auto num_rows     = static_cast<int>(std::ssize(filled_image));
    const auto num_cols     = static_cast<int>(std::ssize(filled_image[0]));
    const int  start_color {filled_image[sr][sc]};

    const std::function<void(int, int)> flood_fill_dfs = [&](int row, int col) {
        if (filled_image[row][col] != start_color)
        {
            return;
        }
    
        filled_image[row][col] = color;

        if (row >= 1)
        {
            flood_fill_dfs(row - 1, col);
        }

        if (col >= 1)
        {
            flood_fill_dfs(row, col - 1);
        }

        if (row + 1 < num_rows)
        {
            flood_fill_dfs(row + 1, col);
        }

        if (col + 1 < num_cols)
        {
            flood_fill_dfs(row, col + 1);
        }
    };

    if (start_color != color)
    {
        flood_fill_dfs(sr, sc);
    }

    return filled_image;
}

TEST_CASE("Example 1", "[floodFill]")
{
    constexpr int sr {1};
    constexpr int sc {1};
    constexpr int color {2};

    const std::vector<std::vector<int>> image {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    const std::vector<std::vector<int>> expected_output {
        {2, 2, 2}, {2, 2, 0}, {2, 0, 1}};

    REQUIRE(expected_output == floodFillFA(image, sr, sc, color));
    REQUIRE(expected_output == floodFillDS1(image, sr, sc, color));
}

TEST_CASE("Example 2", "[floodFill]")
{
    constexpr int sr {};
    constexpr int sc {};
    constexpr int color {};

    const std::vector<std::vector<int>> image {{0, 0, 0}, {0, 0, 0}};
    const auto                          expected_output = image;

    REQUIRE(expected_output == floodFillFA(image, sr, sc, color));
    REQUIRE(expected_output == floodFillDS1(image, sr, sc, color));
}
