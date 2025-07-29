#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

[[nodiscard]] static bool are_symmetric_FA(TreeNode* node1, TreeNode* node2)
{
    if (node1 == nullptr && node2 == nullptr)
    {
        return true;
    }

    if (node1 == nullptr || node2 == nullptr)
    {
        return false;
    }

    if (node1->val != node2->val)
    {
        return false;
    }

    return are_symmetric_FA(node1->left, node2->right)
        && are_symmetric_FA(node1->right, node2->left);
}

//! @brief First attempt solution to check if binary tree is a mirror of itself
//! @param[in] root Pointer to root TreeNode
//! @return True if binary tree is symmetric around its center, else false
static bool isSymmetricFA(TreeNode* root)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/507/
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree
    //!          Space complexity O(N) for a mirrored complete binary tree.
    //!          For a level L, there are 2 ^ L calls to are_symmetric_FA. When
    //!          L = the height of the tree, there will be 2 ^ (log N) = N calls
    //!          to are_symmetric_FA on the recursion stack.

    if (root == nullptr)
    {
        return false;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return true;
    }

    if (root->left == nullptr || root->right == nullptr)
    {
        return false;
    }

    return are_symmetric_FA(root->left, root->right);

} // static bool isSymmetricFA( ...

TEST_CASE("Example 1", "[isSymmetric]")
{
    TreeNode lhs_three {3};
    TreeNode lhs_four {4};
    TreeNode lhs_two {2, &lhs_three, &lhs_four};

    TreeNode rhs_four {4};
    TreeNode rhs_three {3};
    TreeNode rhs_two {2};

    TreeNode one {1, &lhs_two, &rhs_two};

    REQUIRE(isSymmetricFA(&one));
}

TEST_CASE("Example 2", "[isSymmetric]")
{
    TreeNode lhs_three {3};
    TreeNode lhs_two {2, nullptr, &lhs_three};

    TreeNode rhs_three {3};
    TreeNode rhs_two {2, nullptr, &rhs_three};

    TreeNode one {1, &lhs_two, &rhs_two};

    REQUIRE(!isSymmetric(&one));
}
