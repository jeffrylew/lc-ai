#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

static bool is_(TreeNode* node, TreeNode* parent)
{

}

//! @brief First attempt solution to determine if a binary tree is a valid BST
//! @param[in] root Pointer to root TreeNode
//! @return True if binary tree is a valid binary search tree, else false
static bool isValidBSTFA(TreeNode* root)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/514
    //!
    //!          First attempt solution currently does not pass Example 4
    //!          Time complexity O(N) where N = number of nodes in binary tree
    //!          Space complexity O(N). Each level in the binary tree spawns
    //!          2 ^ H calls to isValidBSTFA, where H = the current index of
    //!          the level in the tree starting from 0. The max level index is
    //!          when H = log N, the height of the tree and the corresponding
    //!          level will place 2 ^ (log N) calls on the stack for O(N) usage.

    if (root == nullptr)
    {
        return true;
    }

    if (root->left == nullptr && root->right == nullptr)
    {
        return true;
    }

    if (root->left != nullptr)
    {
        if (root->left->val >= root->val)
        {
            return false;
        }
    }

    if (root->right != nullptr)
    {
        if (root->right->val <= root->val)
        {
            return false;
        }
    }

    /*
    if (root->left != nullptr && root->left->val >= root->val)
    {
        return false;
    }

    if (root->right != nullptr && root->right->val <= root->val)
    {
        return false;
    }
    */

    return isValidBSTFA(root->left) && isValidBSTFA(root->right);

} // static bool isValidBSTFA( ...

TEST_CASE("Example 1", "[isValidBST]")
{
    TreeNode one {1};
    TreeNode three {3};
    TreeNode two {2, &one, &three};

    REQUIRE(isValidBSTFA(&two));
}

TEST_CASE("Example 2", "[isValidBST]")
{
    TreeNode one {1};
    TreeNode three {3};
    TreeNode six {6};

    TreeNode four {4, &three, &six};
    TreeNode five {5, &one, &four};

    REQUIRE(!isValidBSTFA(&five));
}

TEST_CASE("Example 3", "[isValidBST]")
{
    TreeNode neg_one {-1};
    TreeNode zero {0, &neg_one, nullptr};

    REQUIRE(isValidBSTFA(&zero));
}

TEST_CASE("Example 4", "[isValidBST]")
{
    TreeNode three {3};
    TreeNode four {4};
    TreeNode seven {7};

    TreeNode six {6, &three, &seven};
    TreeNode five {5, &four, &six};

    // REQUIRE(!isValidBSTFA(&five));
}
