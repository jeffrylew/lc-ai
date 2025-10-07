#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

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

    auto* lca_fa = lowestCommonAncestorDS1(&three, &five, &one);
    REQUIRE(lca_fa != nullptr);
    REQUIRE(lca_fa->val == 3);
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

    auto* lca_fa = lowestCommonAncestorDS1(&three, &five, &four);
    REQUIRE(lca_fa != nullptr);
    REQUIRE(lca_fa->val == 5);
}

TEST_CASE("Example 3", "[lowestCommonAncestor]")
{
    TreeNode two {2};
    TreeNode one {1, &two, nullptr};

    auto* lca_fa = lowestCommonAncestorDS1(&one, &one, &two);
    REQUIRE(lca_fa != nullptr);
    REQUIRE(lca_fa->val == 1);
}
