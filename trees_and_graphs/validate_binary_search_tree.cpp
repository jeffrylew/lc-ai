#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <stack>

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

//! @struct BoundedTreeNode
//! @brief Pointer to TreeNode and the low and high bounding TreeNodes
struct BoundedTreeNode
{
    TreeNode* node {nullptr};
    TreeNode* low_node {nullptr};
    TreeNode* high_node {nullptr};
};

//! @brief Iterative traversal with valid range discussion solution
//! @param[in] root Pointer to root TreeNode
//! @return True if binary tree is a valid binary search tree, else false
static bool isValidBSTDS2(TreeNode* root)
{
    //! @details https://leetcode.com/problems/validate-binary-search-tree/
    //!
    //!          Time complexity O(N) to visit each node exactly once
    //!          Space complexity O(N) to store up to the entire tree

    std::stack<BoundedTreeNode> bounded_node_stack;
    bounded_node_stack.emplace(root, nullptr, nullptr);

    while (!bounded_node_stack.empty())
    {
        auto bounded_node = bounded_node_stack.top();
        bounded_node_stack.pop();

        if (bounded_node.node == nullptr)
        {
            continue;
        }

        if (bounded_node.low_node != nullptr
            && bounded_node.node->val <= bounded_node.low_node->val)
        {
            return false;
        }

        if (bounded_node.high_node != nullptr
            && bounded_node.node->val >= bounded_node.high_node->val)
        {
            return false;
        }

        bounded_node_stack.emplace(bounded_node.node->right,
                                   bounded_node.node,
                                   bounded_node.high_node);
        bounded_node_stack.emplace(bounded_node.node->left,
                                   bounded_node.low_node,
                                   bounded_node.node);
    }

    return true;

} // static bool isValidBSTDS2( ...

//! @brief Recursive inorder traversal discussion solution
//! @param[in] root Pointer to root TreeNode
//! @return True if binary tree is a valid binary search tree, else false
static bool isValidBSTDS3(TreeNode* root)
{
    //! @details https://leetcode.com/problems/validate-binary-search-tree/
    //!
    //!          Time complexity O(N) in the worst case when the tree is a BST
    //!          or the "bad" element is a rightmost leaf.
    //!          Space complexity O(N) for the space on the run-time stack.

    TreeNode* prev {nullptr};

    std::functional<bool(TreeNode*)> is_inorder = [&](TreeNode* curr) {
        if (curr == nullptr)
        {
            return true;
        }

        if (!is_inorder(curr->left))
        {
            return false;
        }

        if (prev != nullptr && curr->val <= prev->val)
        {
            return false;
        }

        prev = curr;

        return is_inorder(curr->right);
    };

    return is_inorder(root);

} // static bool isValidBSTDS3( ...

TEST_CASE("Example 1", "[isValidBST]")
{
    TreeNode one {1};
    TreeNode three {3};
    TreeNode two {2, &one, &three};

    REQUIRE(isValidBSTFA(&two));
    REQUIRE(isValidBSTDS1(&two));
    REQUIRE(isValidBSTDS2(&two));
    REQUIRE(isValidBSTDS3(&two));
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
    REQUIRE(!isValidBSTDS2(&five));
    REQUIRE(!isValidBSTDS3(&five));
}

TEST_CASE("Example 3", "[isValidBST]")
{
    TreeNode neg_one {-1};
    TreeNode zero {0, &neg_one, nullptr};

    REQUIRE(isValidBSTFA(&zero));
    REQUIRE(isValidBSTDS1(&zero));
    REQUIRE(isValidBSTDS2(&zero));
    REQUIRE(isValidBSTDS3(&zero));
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
    REQUIRE(!isValidBSTDS2(&five));
    REQUIRE(!isValidBSTDS3(&five));
}
