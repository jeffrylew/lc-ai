#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <stack>
#include <unordered_map>
#include <unordered_set>

static TreeNode* lowestCommonAncestorDS1(TreeNode* root,
                                         TreeNode* p,
                                         TreeNode* q)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2984/
    //!          https://leetcode.com/problems
    //!          /lowest-common-ancestor-of-a-binary-tree/solutions/6750643
    //!          /video-for-everyone-who-doesnt-understand-oxf6/
    //!
    //!          Time complexity O(N) where N = number of nodes in the tree.
    //!          Space complexity O(H) where H is the height of the tree.

    if (root == nullptr)
    {
        return nullptr;
    }

    if (root == p || root == q)
    {
        return root;
    }

    const auto left  = lowestCommonAncestorDS1(root->left, p, q);
    const auto right = lowestCommonAncestorDS1(root->right, p, q);

    if (left != nullptr && right != nullptr)
    {
        return root;
    }

    if (left != nullptr)
    {
        return left;
    }

    return right;
}

static TreeNode* lowestCommonAncestorDS2(TreeNode* root,
                                         TreeNode* p,
                                         TreeNode* q)
{
    //! @details https://leetcode.com/problems
    //!          /lowest-common-ancestor-of-a-binary-tree/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in the binary
    //!          tree. In the worst case, we visit all nodes of the tree.
    //!          Space complexity O(N). The max amount of space used by the
    //!          recursion stack would be N since the height of a skewed binary
    //!          tree could be N.

    TreeNode* lca_node {nullptr};

    std::function<bool(TreeNode*)> recurse_tree = [&](TreeNode* node) {
        if (node == nullptr || lca_node != nullptr)
        {
            return false;
        }

        const int left {recurse_tree(node->left) ? 1 : 0};
        const int right {recurse_tree(node->right) ? 1 : 0};
        const int mid {(node == p || node == q) ? 1 : 0};

        if (mid + left + right == 2)
        {
            lca_node = node;
        }

        return (mid + left + right > 0);
    };

    recurse_tree(root);
    return lca_node;
}

static TreeNode* lowestCommonAncestorDS3(TreeNode* root,
                                         TreeNode* p,
                                         TreeNode* q)
{
    //! @details https://leetcode.com/problems
    //!          /lowest-common-ancestor-of-a-binary-tree/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree.
    //!          In the worst case, we visit all nodes of the binary tree.
    //!          Space complexity O(N). In the worst case of a skewed binary
    //!          with height N, the child_to_parent_map and p_ancestors set use
    //!          O(N) space. The node_stack uses O(N) in the worst case when p
    //!          and q are leaves at opposite ends of a complete binary tree.

    //! Stack for tree traversal
    std::stack<TreeNode*> node_stack;
    node_stack.push(root);

    //! Map of <pointer to child node, pointer to parent node>
    std::unordered_map<TreeNode*, TreeNode*> child_to_parent_map;
    child_to_parent_map[root] = nullptr;

    //! Iterate until we find both nodes p and q
    while (!child_to_parent_map.contains(p) || !child_to_parent_map.contains(q))
    {
        auto* curr_node = node_stack.top();
        node_stack.pop();

        //! While traversing the tree, save the pointers to parent nodes
        if (curr_node->left != nullptr)
        {
            child_to_parent_map[curr_node->left] = curr_node;
            node_stack.push(curr_node->left);
        }

        if (curr_node->right != nullptr)
        {
            child_to_parent_map[curr_node->right] = curr_node;
            node_stack.push(curr_node->right);
        }
    }

    //! Set of ancestors for node p
    std::unordered_set<TreeNode*> p_ancestors;

    //! Process all ancestors of node p
    while (p != nullptr)
    {
        p_ancestors.insert(p);
        p = child_to_parent_map[p];
    }

    //! The first ancestor of q that appears in p's ancestor set
    //! is their lowest common ancestor
    while (!p_ancestors.contains(q))
    {
        q = child_to_parent_map[q];
    }

    return q;
}

TEST_CASE("Example 1", "[lowestCommonAncestor]")
{
    TreeNode zero {0};
    TreeNode four {4};
    TreeNode six {6};
    TreeNode seven {7};
    TreeNode eight {8};

    TreeNode one {1, &zero, &eight};
    TreeNode two {2, &seven, &four};

    TreeNode five {5, &six, &two};
    TreeNode three {3, &five, &one};

    auto* lca_ds1 = lowestCommonAncestorDS1(&three, &five, &one);
    REQUIRE(lca_ds1 != nullptr);
    REQUIRE(lca_ds1->val == 3);

    auto* lca_ds2 = lowestCommonAncestorDS2(&three, &five, &one);
    REQUIRE(lca_ds2 != nullptr);
    REQUIRE(lca_ds2->val == 3);

    auto* lca_ds3 = lowestCommonAncestorDS3(&three, &five, &one);
    REQUIRE(lca_ds3 != nullptr);
    REQUIRE(lca_ds3->val == 3);
}

TEST_CASE("Example 2", "[lowestCommonAncestor]")
{
    TreeNode zero {0};
    TreeNode four {4};
    TreeNode six {6};
    TreeNode seven {7};
    TreeNode eight {8};

    TreeNode one {1, &zero, &eight};
    TreeNode two {2, &seven, &four};

    TreeNode five {5, &six, &two};
    TreeNode three {3, &five, &one};

    auto* lca_ds1 = lowestCommonAncestorDS1(&three, &five, &four);
    REQUIRE(lca_ds1 != nullptr);
    REQUIRE(lca_ds1->val == 5);

    auto* lca_ds2 = lowestCommonAncestorDS2(&three, &five, &four);
    REQUIRE(lca_ds2 != nullptr);
    REQUIRE(lca_ds2->val == 5);

    auto* lca_ds3 = lowestCommonAncestorDS3(&three, &five, &four);
    REQUIRE(lca_ds3 != nullptr);
    REQUIRE(lca_ds3->val == 5);
}

TEST_CASE("Example 3", "[lowestCommonAncestor]")
{
    TreeNode two {2};
    TreeNode one {1, &two, nullptr};

    auto* lca_ds1 = lowestCommonAncestorDS1(&one, &one, &two);
    REQUIRE(lca_ds1 != nullptr);
    REQUIRE(lca_ds1->val == 1);

    auto* lca_ds2 = lowestCommonAncestorDS2(&one, &one, &two);
    REQUIRE(lca_ds2 != nullptr);
    REQUIRE(lca_ds2->val == 1);

    auto* lca_ds3 = lowestCommonAncestorDS3(&one, &one, &two);
    REQUIRE(lca_ds3 != nullptr);
    REQUIRE(lca_ds3->val == 1);
}
