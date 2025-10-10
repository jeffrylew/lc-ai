#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <functional>

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

    auto* lca_ds2 = lowestCommonAncestorDS1(&three, &five, &four);
    REQUIRE(lca_ds2 != nullptr);
    REQUIRE(lca_ds2->val == 5);
}

TEST_CASE("Example 3", "[lowestCommonAncestor]")
{
    TreeNode two {2};
    TreeNode one {1, &two, nullptr};

    auto* lca_ds1 = lowestCommonAncestorDS1(&one, &one, &two);
    REQUIRE(lca_ds1 != nullptr);
    REQUIRE(lca_ds1->val == 1);

    auto* lca_ds2 = lowestCommonAncestorDS1(&one, &one, &two);
    REQUIRE(lca_ds2 != nullptr);
    REQUIRE(lca_ds2->val == 1);
}
