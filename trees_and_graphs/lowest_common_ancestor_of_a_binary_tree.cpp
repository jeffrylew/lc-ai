#include "TreeNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>

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

    //! root == nullptr: Neither p nor q can exist so return nullptr
    //! root == p || root == q: If root is either p or q then return root
    if (root == nullptr || root == p || root == q)
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

static TreeNode* lowestCommonAncestorDS4(TreeNode* root,
                                         TreeNode* p,
                                         TreeNode* q)
{
    //! @details https://leetcode.com/problems
    //!          /lowest-common-ancestor-of-a-binary-tree/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in binary tree.
    //!          In the worst case, we might be visiting all nodes in the tree.
    //!          The advantage of this approach is that we prune backtracking.
    //!          We return once both p and q are found.
    //!          Space complexity O(N). In the worst case, the space used by the
    //!          stack would be N since the height of a skewed binary tree is N.

    enum class Children_state
    {
        //! Both left and right traversal are pending for a node
        //! The children of a node have not been traversed yet
        BOTH_PENDING,
        //! Left traversal is done
        LEFT_DONE,
        //! Both left and right traversals have finished for a node
        //! Indicates that the node can be popped off the stack
        BOTH_DONE
    };

    //! Stack of <node, children processed state>. Initialize with root node.
    std::stack<std::pair<TreeNode*, Children_state>> node_child_state;
    node_child_state.emplace(root, Children_state::BOTH_PENDING);

    //! Flag is set when either one of p or q is found
    bool one_node_found {};

    //! lca_node keeps track of the lowest common ancestor
    TreeNode* lca_node {nullptr};

    //! Assists with processing children
    TreeNode* child_node {nullptr};

    //! Do a post order traveral of binary tree
    while (!node_child_state.empty())
    {
        auto& [parent_node, parent_state] = node_child_state.top();

        //! If parent_state isn't BOTH_DONE then parent_node can't be popped yet
        if (parent_state != Children_state::BOTH_DONE)
        {
            //! If both child traversals are pending
            if (parent_state == Children_state::BOTH_PENDING)
            {
                //! Check if current parent_node is either p or q
                if (parent_node == p || parent_node == q)
                {
                    //! If one_node_found was already set then we found p and q
                    if (one_node_found)
                    {
                        return lca_node;
                    }

                    //! Else, set one_node_found to true to mark p or q as found
                    one_node_found = true;

                    //! Save parent_node as the LCA
                    lca_node = parent_node;
                }

                //! Since both child traversals are pending,
                //! traverse the left child first
                child_node = parent_node->left;

                //! Update parent_state to reflect status after processing left
                parent_state = Children_state::LEFT_DONE;
            }
            else // parent_state == Children_state::LEFT_DONE
            {
                //! Traverse the right child
                child_node = parent_node->right;

                //! Update parent_state to reflect status after processing right
                parent_state = Children_state::BOTH_DONE;

            } // else -> if (parent_state == Children_state::BOTH_PENDING)

            //! Add the child_node to the stack for traversal
            if (child_node != nullptr)
            {
                node_child_state.emplace(child_node,
                                         Children_state::BOTH_PENDING);
            }
        }
        else // parent_state == Children_state::BOTH_DONE
        {
            node_child_state.pop();

            //! If the parent_state is BOTH_DONE then the top node can be
            //! popped off of the stack. Update lca_node to be the next top node
            if (lca_node == parent_node && one_node_found)
            {
                lca_node = node_child_state.top().first;
            }

        } // else -> if (parent_state != Children_state::BOTH_DONE)

    } // while (!node_child_state.empty())

    return nullptr;
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

    auto* lca_ds4 = lowestCommonAncestorDS4(&three, &five, &one);
    REQUIRE(lca_ds4 != nullptr);
    REQUIRE(lca_ds4->val == 3);
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

    auto* lca_ds4 = lowestCommonAncestorDS4(&three, &five, &four);
    REQUIRE(lca_ds4 != nullptr);
    REQUIRE(lca_ds4->val == 5);
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

    auto* lca_ds4 = lowestCommonAncestorDS4(&one, &one, &two);
    REQUIRE(lca_ds4 != nullptr);
    REQUIRE(lca_ds4->val == 1);
}
