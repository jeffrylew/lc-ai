#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

static TreeNode* lowestCommonAncestorFA(TreeNode* root,
                                        TreeNode* p,
                                        TreeNode* q)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/78
    //!          /trees-and-graphs/2984/

    //! @todo
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

    auto* lca_fa = lowestCommonAncestorFA(&three, &five, &one);
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

    auto* lca_fa = lowestCommonAncestorFA(&three, &five, &four);
    REQUIRE(lca_fa != nullptr);
    REQUIRE(lca_fa->val == 5);
}

TEST_CASE("Example 3", "[lowestCommonAncestor]")
{
    TreeNode two {2};
    TreeNode one {1, &two, nullptr};

    auto* lca_fa = lowestCommonAncestorFA(&one, &one, &two);
    REQUIRE(lca_fa != nullptr);
    REQUIRE(lca_fa->val == 1);
}
