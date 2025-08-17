#include <catch2/catch_test_macros.hpp>

#include <string>
#include <vector>

//! @brief lee's discussion solution to get the max int with total cost = target
//! @param[in] cost   Vector of ints where cost[i] is the cost of digit (i + 1)
//! @param[in] target The total cost of painting all digits
//! @return The max int that can be painted as a string
static std::string largestNumberDS1(const std::vector<int>& cost, int target)
{
    //! @details https://leetcode.com/problems
    //!         /form-largest-integer-with-digits-that-add-up-to-target

    //! max_digits_for_num[i] = Max digits we can sum to exactly equal number i
    std::vector<int> max_digits_for_num(target + 1, -10000);
    max_digits_for_num[0] = 0;

    //! Determine the max number of digits that can be summed to equal num
    //! for all values of num from 1 to target
    for (int num = 1; num <= target; ++num)
    {
        for (const int digit_cost : cost)
        {
            if (num >= digit_cost)
            {
                max_digits_for_num[num] =
                    std::max(max_digits_for_num[num],
                             max_digits_for_num[num - digit_cost] + 1);
            }
        }
    }

    //! Impossible to reach target
    if (max_digits_for_num[target] < 0)
    {
        return "0";
    }

    std::string largest_number;

    for (int digit = 9; digit >= 1; --digit)
    {
        while (target >= cost[digit - 1]
               && max_digits_for_num[target]
                  == max_digits_for_num[target - cost[digit - 1]] + 1)
        {
            largest_number += static_cast<char>(digit + '0');
            target -= cost[digit - 1];
        }
    }

    return largest_number;
}

TEST_CASE("Example 1", "[largestNumber]")
{
    // Index:                    0  1  2  3  4  5  6  7  8
    // Digit:                    1  2  3  4  5  6  7  8  9
    const std::vector<int> cost {4, 3, 2, 5, 6, 7, 2, 5, 5};
    constexpr int          target {9};

    //! Explanation:
    //! The cost to paint the digit '7' is 2 and paint the digit '2' is 3.
    //! Then cost("7772") = 2 * 3 + 3 * 1 = 9. You could also paint "977" but
    //! "7772" is the largest number. 
    REQUIRE("7772" == largestNumberDS1(cost, target));
}

TEST_CASE("Example 2", "[largestNumber]")
{
    // Index:                    0  1  2  3  4  5  6  7  8
    // Digit:                    1  2  3  4  5  6  7  8  9
    const std::vector<int> cost {7, 6, 5, 5, 5, 6, 8, 7, 8};
    constexpr int          target {12};

    //! Explanation:
    //! The cost to paint the digit '8' is 7 and paint the digit '5' is 5.
    //! Then cost("85") = 7 + 5 = 12.
    REQUIRE("85" == largestNumberDS1(cost, target));
}

TEST_CASE("Example 3", "[largestNumber]")
{
    // Index:                    0  1  2  3  4  5  6  7  8
    // Digit:                    1  2  3  4  5  6  7  8  9
    const std::vector<int> cost {2, 4, 6, 2, 4, 6, 4, 4, 4};
    constexpr int          target {5};

    //! Explanation:
    //! It is impossible to paint any integer with total cost equal to target.
    REQUIRE("0" == largestNumberDS1(cost, target));
}
