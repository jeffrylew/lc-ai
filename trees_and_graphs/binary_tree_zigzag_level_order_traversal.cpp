#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <stack>
#include <utility>
#include <vector>

//! @brief First attempt solution to get zigzag level order traversal of nodes
//! @param[in] root Pointer to root TreeNode
//! @return Zigzag level order traversal from left to right and henceforth
static std::vector<std::vector<int>> zigzagLevelOrderFA(TreeNode* root)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2980/
    //!
    //!          First attempt solution does not pass Example 5.

    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> zigzag_traversal;

    bool                  left_to_right {};
    std::queue<TreeNode*> node_queue;
    node_queue.push(root);

    std::stack<TreeNode*> child_node_stack;

    while (!node_queue.empty())
    {
        const auto num_nodes_in_level = node_queue.size();

        std::vector<int> node_values_in_level;
        node_values_in_level.reserve(num_nodes_in_level);

        for (std::size_t count = 0; count < num_nodes_in_level; ++count)
        {
            const auto curr_node = node_queue.front();
            node_queue.pop();

            node_values_in_level.push_back(curr_node->val);

            if (curr_node->right != nullptr)
            {
                if (left_to_right)
                {
                    child_node_stack.push(curr_node->right);
                }
                else
                {
                    node_queue.push(curr_node->right);
                }
            }

            if (curr_node->left != nullptr)
            {
                if (left_to_right)
                {
                    child_node_stack.push(curr_node->left);
                }
                else
                {
                    node_queue.push(curr_node->left);
                }
            }

        } // for (std::size_t count = 0; ...

        zigzag_traversal.push_back(std::move(node_values_in_level));

        while (!child_node_stack.empty())
        {
            node_queue.push(child_node_stack.top());
            child_node_stack.pop();
        }

        left_to_right = !left_to_right;

    } // while (!node_queue.empty())

    return zigzag_traversal;

} // static std::vector<std::vector<int>> zigzagLevelOrderFA( ...

//! @brief BFS discussion solution
//! @param[in] root Pointer to root TreeNode
//! @return Zigzag level order traversal from left to right and henceforth
static std::vector<std::vector<int>> zigzagLevelOrderDS1(TreeNode* root)
{
    //! @details https://leetcode.com/problems
    //!          /binary-tree-zigzag-level-order-traversal/editorial/

    if (root == nullptr)
    {
        return {};
    }

    std::vector<std::vector<int>> zigzag_traversal;

    std::deque<TreeNode*> node_queue;
    node_queue.push_back(root);

    //! Delimiter for a single level
    node_queue.push_back(nullptr);

    std::deque<int> level_values;

    bool is_order_left {true};

    while (!node_queue.empty())
    {
        auto node = node_queue.front();
        node_queue.pop_front();

        if (node != nullptr)
        {
            if (is_order_left)
            {
                level_values.push_back(node->val);
            }
            else
            {
                level_values.push_front(node->val);
            }

            if (node->left != nullptr)
            {
                node_queue.push_back(node->left);
            }

            if (node->right != nullptr)
            {
                node_queue.push_back(node->right);
            }
        }
        else
        {
            //! Add current level to zigzag_traversal and prepare for next level
            zigzag_traversal.push_back(
                std::vector<int> {level_values.begin(), level_values.end()});

            level_values.clear();

            if (!node_queue.empty())
            {
                node_queue.push_back(nullptr);
            }

            is_order_left = !is_order_left;
        }
    }

    return zigzag_traversal;

} // static std::vector<std::vector<int>> zigzagLevelOrderDS1( ...

TEST_CASE("Example 1", "zigzagLevelOrder")
{
    TreeNode seven {7};
    TreeNode nine {9};
    TreeNode fifteen {15};

    TreeNode twenty {20, &fifteen, &seven};
    TreeNode three {3, &nine, &twenty};

    const std::vector<std::vector<int>> expected_output {{3}, {20, 9}, {15, 7}};

    REQUIRE(expected_output == zigzagLevelOrderFA(&three));
    REQUIRE(expected_output == zigzagLevelOrderDS1(&three));
}

TEST_CASE("Example 2", "zigzagLevelOrder")
{
    TreeNode one {1};

    const std::vector<std::vector<int>> expected_output {{1}};

    REQUIRE(expected_output == zigzagLevelOrderFA(&one));
    REQUIRE(expected_output == zigzagLevelOrderDS1(&one));
}

TEST_CASE("Example 3", "zigzagLevelOrder")
{
    REQUIRE(zigzagLevelOrderFA(nullptr).empty());
    REQUIRE(zigzagLevelOrderDS1(nullptr).empty());
}

TEST_CASE("Example 4", "zigzagLevelOrder")
{
    TreeNode four {4};
    TreeNode five {5};

    TreeNode two {2, &four, nullptr};
    TreeNode three {3, nullptr, &five};
    TreeNode one {1, &two, &three};

    const std::vector<std::vector<int>> expected_output {{1}, {3, 2}, {4, 5}};

    REQUIRE(expected_output == zigzagLevelOrderFA(&one));
    REQUIRE(expected_output == zigzagLevelOrderDS1(&one));
}

TEST_CASE("Example 5", "zigzagLevelOrder")
{
    TreeNode one_bottom {1};
    TreeNode five {5};
    TreeNode six {6};
    TreeNode eight {8};

    TreeNode neg_one {-1, nullptr, &eight};
    TreeNode one_top {1, &five, &one_bottom};
    TreeNode three {3, nullptr, &six};

    TreeNode two {2, &one_top, nullptr};
    TreeNode four {4, &three, &neg_one};

    TreeNode zero {0, &two, &four};

    const std::vector<std::vector<int>> expected_output {
        {0}, {4, 2}, {1, 3, -1}, {8, 6, 1, 5}};

    // REQUIRE(expected_output == zigzagLevelOrderFA(&zero));
    REQUIRE(expected_output == zigzagLevelOrderDS1(&zero));
}
