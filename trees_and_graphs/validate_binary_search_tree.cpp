#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

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

    if (root->left != nullptr && root->left->val >= root->val)
    {
        return false;
    }

    if (root->right != nullptr && root->right->val <= root->val)
    {
        return false;
    }

    return isValidBSTFA(root->left) && isValidBSTFA(root->right);

} // static bool isValidBSTFA( ...

[[nodiscard]] static bool
    validate_bst(TreeNode* root, TreeNode* low_node, TreeNode* high_node)
{
    //! Empty tree is a valid BST
    if (root == nullptr)
    {
        return true;
    }

    //! Current node's value must be between low_node and high_node
    if ((low_node != nullptr && root->val <= low_node->val)
        || (high_node != nullptr && root->val >= high_node->val))
    {
        return false;
    }

    //! Left and right subtrees must be valid
    return validate_bst(root->right, root, high_node)
        && validate_bst(root->left, low_node, root);
}

//! @brief Recursive traversal with valid range discussion solution
//! @param[in] root Pointer to root TreeNode
//! @return True if binary tree is a valid binary search tree, else false
static bool isValidBSTDS1(TreeNode* root)
{
    //! @details https://leetcode.com/problems/validate-binary-search-tree/
    //!
    //!          Time complexity O(N) to visit each node exactly once
    //!          Space complexity O(N) to store up to the entire tree

    return validate_bst(root, nullptr, nullptr);
}

TEST_CASE("Example 1", "[isValidBST]")
{
    TreeNode one {1};
    TreeNode three {3};
    TreeNode two {2, &one, &three};

    REQUIRE(isValidBSTFA(&two));
    REQUIRE(isValidBSTDS1(&two));
}

TEST_CASE("Example 2", "[isValidBST]")
{
    TreeNode one {1};
    TreeNode three {3};
    TreeNode six {6};

    TreeNode four {4, &three, &six};
    TreeNode five {5, &one, &four};

    REQUIRE(!isValidBSTFA(&five));
    REQUIRE(!isValidBSTDS1(&five));
}

TEST_CASE("Example 3", "[isValidBST]")
{
    TreeNode neg_one {-1};
    TreeNode zero {0, &neg_one, nullptr};

    REQUIRE(isValidBSTFA(&zero));
    REQUIRE(isValidBSTDS1(&zero));
}

TEST_CASE("Example 4", "[isValidBST]")
{
    TreeNode three {3};
    TreeNode four {4};
    TreeNode seven {7};

    TreeNode six {6, &three, &seven};
    TreeNode five {5, &four, &six};

    // REQUIRE(!isValidBSTFA(&five));
    REQUIRE(!isValidBSTDS1(&five));
}
