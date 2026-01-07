#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <vector>

static std::vector<int> productExceptSelfFA(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/499/

    int produc
    auto products = nums;
    std::transform(products.begin(),
                   products.end(),
                   products.begin(),
                   [](int num) { return static_cast<int>(std::pow(num, -1)); });

}

TEST_CASE("Example 1", "[productExceptSelf]")
{
    const std::vector<int> nums {1, 2, 3, 4};
    const std::vector<int> expected_output {24, 12, 8, 6};

    REQUIRE(expected_output == productExceptSelfFA(nums));
}

TEST_CASE("Example 2", "[productExceptSelf]")
{
    const std::vector<int> nums {-1, 1, 0, -3, 3};
    const std::vector<int> expected_output {0, 0, 9, 0, 0};

    REQUIRE(expected_output == productExceptSelfFA(nums));
}
