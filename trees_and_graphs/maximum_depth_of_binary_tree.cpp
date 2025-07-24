#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

//! @brief First attempt solution to get max depth of binary tree
//! @param[in] root Pointer to root TreeNode
//! @return Maximum depth of binary tree
static int maxDepthFA(TreeNode* root)
{
    //! @details https://leetcode.com/problems/maximum-depth-of-binary-tree
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree
    //!          Space complexity O(1)

    if (root == nullptr)
    {
        return 0;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return 1;
    }

    return 1 + std::max(maxDepthFA(root->left), maxDepthFA(root->right));
}

TEST_CASE("Example 1", "[MaxDepth]")
{
    constexpr TreeNode seven {7};
    constexpr TreeNode nine {9};
    constexpr TreeNode fifteen {15};

    const TreeNode twenty {20, &fifteen, &seven};
    const TreeNode three {3, &nine, &twenty};

    REQUIRE(3 == maxDepthFA(&three));
}

TEST_CASE("Example 2", "[MaxDepth]")
{
    constexpr TreeNode two {2};
    const     TreeNode one {1, nullptr, &two};

    REQUIRE(2 == maxDepthFA(&one));
}