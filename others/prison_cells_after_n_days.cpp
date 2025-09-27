#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <vector>

static std::vector<int> prisonAfterNDaysFA(const std::vector<int>& cells, int n)
{
    //! @details leetcode.com/explore/interview/card/amazon/82/others/3005
    //!
    //!          First attempt solution has TLE for Example 2.
    //!          Time complexity O(n * C) where C = cells.size() = 8. There's
    //!          probably a bitwise operation solution.
    //!          Space complexity O(C) for prev_cells and curr_cells.

    auto prev_cells = cells;
    auto curr_cells = cells;

    constexpr int num_cells {8};

    for (int day = 1; day <= n; ++day)
    {
        curr_cells.front() = 0;
        curr_cells.back()  = 0;

        for (int cell = 1; cell < num_cells - 1; ++cell)
        {
            curr_cells[cell] =
                (prev_cells[cell - 1] == prev_cells[cell + 1]) ? 1 : 0;
        }

        prev_cells = curr_cells;
    }

    return curr_cells;
}

TEST_CASE("Example 1", "[prisonAfterNDays]")
{
    const std::vector<int> cells {0, 1, 0, 1, 1, 0, 0, 1};
    constexpr int          n {7};

    /*
     Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
     Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
     Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
     Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
     Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
     Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
     Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
     Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
     */
    const std::vector<int> expected_output {0, 0, 1, 1, 0, 0, 0, 0};

    REQUIRE(expected_output == prisonAfterNDaysFA(cells, n));
}

TEST_CASE("Example 2", "[prisonAfterNDays]")
{
    const std::vector<int> cells {1, 0, 0, 1, 0, 0, 1, 0};
    constexpr int          n {1000000000};

    const std::vector<int> expected_output {0, 0, 1, 1, 1, 1, 1, 0};

    REQUIRE(expected_output == prisonAfterNDaysFA(cells, n));
}
