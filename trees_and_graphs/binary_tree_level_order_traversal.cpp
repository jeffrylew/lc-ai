#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <vector>

//! @brief First attempt solution for getting level order traversal
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing level order traversal of node values
static std::vector<std::vector<int>> levelOrderFA(TreeNode* root)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/506
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree.
    //!          Space complexity O(N). For a complete binary tree, each level
    //!          will have 2 ^ L nodes, where L is the current level from 0 to
    //!          log N (the height of the tree). So in the worst case, the last
    //!          level will have 2 ^ (log N) = N nodes in the queue.

    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> level_order_traversal;

    std::queue<TreeNode*> node_queue;
    node_queue.push(root);

    while (!node_queue.empty())
    {
        const auto num_nodes_in_curr_level =
            static_cast<int>(std::ssize(node_queue));

        auto& curr_level = level_order_traversal.emplace_back();
        curr_level.reserve(num_nodes_in_curr_level);

        for (int node_idx = 0; node_idx < num_nodes_in_curr_level; ++node_idx)
        {
            auto* curr_node = node_queue.front();
            node_queue.pop();
    
            curr_level.push_back(curr_node->val);

            if (curr_node->left != nullptr)
            {
                node_queue.push(curr_node->left);
            }

            if (curr_node->right != nullptr)
            {
                node_queue.push(curr_node->right);
            }
        }
    }

    return level_order_traversal;

} // static std::vector<std::vector<int>> levelOrderFA( ...

TEST_CASE("Example 1", "[LevelOrder]")
{
    constexpr TreeNode seven {7};
    constexpr TreeNode nine {9};
    constexpr TreeNode fifteen {15};

    const TreeNode twenty {20, &fifteen, &seven};
    const TreeNode three {3, &nine, &twenty};

    const std::vector<std::vector<int>> expected_output {{3}, {9, 20}, {15, 7}};

    REQUIRE(expected_output == levelOrderFA(&three));
}

TEST_CASE("Example 2", "[LevelOrder]")
{
    constexpr TreeNode one {1};

    const std::vector<std::vector<int>> expected_output {{1}};

    REQUIRE(expected_output == levelOrderFA(&one));
}

TEST_CASE("Example 3", "[LevelOrder]")
{
    REQUIRE(levelOrderFA(nullptr).empty());
}
