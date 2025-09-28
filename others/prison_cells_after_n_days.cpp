#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <unordered_map>
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

[[nodiscard]] constexpr int cells_to_bitmap_DS1(const std::vector<int>& cells)
{
    int bitmap_of_cells {};

    //! Leading bit is 0 to indicate a positive 32-bit signed integer
    for (const int cell : cells)
    {
        bitmap_of_cells <<= 1;
        bitmap_of_cells |= cell;
    }

    return bitmap_of_cells;
}

[[nodiscard]] static std::vector<int>
    prison_tomorrow_DS1(const std::vector<int>& cells_today)
{
    std::vector<int> cells_tomorrow(cells_today.size());

    for (int cell = 1; cell < std::ssize(cells_today) - 1; ++cell)
    {
        cells_tomorrow[cell] =
            (cells_today[cell - 1] == cells_today[cell + 1]) ? 1 : 0;
    }

    return cells_tomorrow;
}

static std::vector<int> prisonAfterNDaysDS1(const std::vector<int>& cells,
                                            int                     n)
{
    //! @details leetcode.com/problems/prison-cells-after-n-days/editorial
    //!
    //!          Time complexity O(min(n, 2 ^ K) * K) where K = cells.size() and
    //!          n = number of steps/days. We can have 2 ^ K possible states at
    //!          most. We might need to run the simulation min(n, 2 ^ K) days
    //!          without fast-forwarding in the worst case. Each simulation day
    //!          takes O(K) to process K cells.
    //!          Space complexity O(2 ^ K) for the visited_states hash map used
    //!          to keep track of the cells states that are each encoded as an
    //!          int. We assume K does not exceed 31 (K = 8 in the problem).

    std::unordered_map<int, int> visited_states;

    auto prison_cells = cells;
    int  remaining_days {n};
    bool is_fast_forwarded {};

    //! Run the simulation with the visited_states hash map
    while (remaining_days > 0)
    {
        if (!is_fast_forwarded)
        {
            const int bitmap_of_cells {cells_to_bitmap_DS1(prison_cells)};

            if (visited_states.contains(bitmap_of_cells))
            {
                //! The length of the cycle is
                //! visited_states[bitmap_of_cells] - remaining_days
                const int days_in_cycle {
                    visited_states[bitmap_of_cells] - remaining_days};

                remaining_days %= days_in_cycle;
                is_fast_forwarded = true;
            }
            else
            {
                visited_states[bitmap_of_cells] = remaining_days;
            }
        }

        //! Check if there are still days left with or without fast-forwarding
        if (remaining_days > 0)
        {
            --remaining_days;
            prison_cells = prison_tomorrow_DS1(prison_cells);
        }
    }

    return prison_cells;
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
    REQUIRE(expected_output == prisonAfterNDaysDS1(cells, n));
}

TEST_CASE("Example 2", "[prisonAfterNDays]")
{
    const std::vector<int> cells {1, 0, 0, 1, 0, 0, 1, 0};
    constexpr int          n {1000000000};

    const std::vector<int> expected_output {0, 0, 1, 1, 1, 1, 1, 0};

    REQUIRE(expected_output == prisonAfterNDaysFA(cells, n));
    REQUIRE(expected_output == prisonAfterNDaysDS1(cells, n));
}
