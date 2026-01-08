#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <vector>

static std::vector<int> productExceptSelfDS1(const std::vector<int>& nums)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/76
    //!          /array-and-strings/499/

    const auto nums_size = static_cast<int>(std::ssize(nums));

    std::vector<int> left_product(nums.size());
    std::vector<int> right_product(nums.size());
    std::vector<int> product_except_self(nums.size());

    //! left_product[idx] contains the product of all elements to the left
    //! @note There are no elements left of index 0 so left_product[0] = 1
    left_product[0] = 1;
    for (int idx = 1; idx < nums_size; ++idx)
    {
        //! left_product[idx - 1] already contains the product of elements to
        //! the left of idx - 1. Multiplying it with nums[idx - 1] gives the
        //! product of all elements to the left of index idx
        left_product[idx] = nums[idx - 1] * left_product[idx - 1];
    }

    //! right_product[idx] contains the product of all elements to the right
    //! @note There are no elements to the right of index nums_size - 1 so
    //! right_product[nums_size - 1] = 1
    right_product[nums_size - 1] = 1;
    for (int idx = nums_size - 2; idx >= 0; --idx)
    {
        //! right_product[idx + 1] already contains the product of elements to
        //! the right of idx + 1. Multiplying it with nums[idx + 1] gives the
        //! product of all elements to the right of index idx
        right_product[idx] = nums[idx + 1] * right_product[idx + 1];
    }

    //! Construct the answer
    for (int idx = 0; idx < nums_size; ++idx)
    {
        //! For the first element, right_product[idx] is the product except self
        //! For the last element, left_product[idx] is the product except self
        //! Else, multiply product of all elements to the left and to the right
        product_except_self[idx] = left_product[idx] * right_product[idx];
    }

    return product_except_self;
}

TEST_CASE("Example 1", "[productExceptSelf]")
{
    const std::vector<int> nums {1, 2, 3, 4};
    const std::vector<int> expected_output {24, 12, 8, 6};

    REQUIRE(expected_output == productExceptSelfDS1(nums));
}

TEST_CASE("Example 2", "[productExceptSelf]")
{
    const std::vector<int> nums {-1, 1, 0, -3, 3};
    const std::vector<int> expected_output {0, 0, 9, 0, 0};

    REQUIRE(expected_output == productExceptSelfDS1(nums));
}
