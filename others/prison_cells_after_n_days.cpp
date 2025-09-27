#include <catch2/catch_test_macros.hpp>

#include <vector>

static std::vector<int> prisonAfterNDaysFA(const std::vector<int>& cells, int n)
{
    //! @todo
}

TEST_CASE("Example 1", "[prisonAfterNDays]")
{
    //! @todo
}

TEST_CASE("Example 2", "[prisonAfterNDays]")
{
    const std::vector<int> cells {1, 0, 0, 1, 0, 0, 1, 0};
    constexpr int          n {1000000000};

    const std::vector<int> expected_output {0, 0, 1, 1, 1, 1, 1, 0};

    REQUIRE(expected_output == prisonAfterNDaysFA(cells, n));
}
