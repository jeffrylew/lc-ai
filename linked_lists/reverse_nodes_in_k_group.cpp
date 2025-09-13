#include "ListNode.hpp"

#include <catch2/catch_test_macros.hpp>

#include <vector>

static ListNode* reverseKGroupFA(ListNode* head, int k)
{
    //! @details https://leetcode.com/problems/reverse-nodes-in-k-group
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(k) for k_group_nodes vector

    if (k == 1)
    {
        return head;
    }

    ListNode* sentinel_head {nullptr};

    ListNode* k_group_head {nullptr};
    ListNode* k_group_tail {nullptr};
    ListNode* k_group_next {nullptr};

    ListNode* prev {nullptr};
    ListNode* curr {head};

    std::vector<ListNode*> k_group_nodes;

    while (curr != nullptr)
    {
        k_group_nodes.clear();

        for (int node = 0; node < k; ++node)
        {
            if (curr == nullptr)
            {
                break;
            }

            k_group_nodes.push_back(curr);
            prev = curr;
            curr = curr->next;
        }

        if (std::ssize(k_group_nodes) != k)
        {
            return sentinel_head;
        }

        if (k_group_tail != nullptr)
        {
            k_group_tail->next = k_group_nodes.back();
        }

        k_group_head = k_group_nodes.back();
        if (sentinel_head == nullptr)
        {
            sentinel_head = k_group_head;
        }
        k_group_tail = k_group_nodes.front();
        k_group_next = prev->next;

        for (int node = k - 1; node > 0; --node)
        {
            k_group_nodes[node]->next = k_group_nodes[node - 1];
        }
        k_group_nodes.front()->next = k_group_next;
    }

    return sentinel_head;
}

static ListNode* reverseLinkedList(ListNode* head, int k)
{
    //! @todo
}

static ListNode* reverseKGroupDS1(ListNode* head, int k)
{
    //! @details leetcode.com/problems/reverse-nodes-in-k-group/editorial

    int node_count {};

    ListNode* ptr = head;

    while (node_count < k && ptr != nullptr)
    {
        ptr = ptr->next;
        ++node_count;
    }

    if (node_count == k)
    {
        auto* reversed_head = reverseLinkedList(head, k);

        head->next = reverseKGroupDS1(ptr, k);

        return reversed_head;
    }

    return head;
}

TEST_CASE("Example 1", "[reverseKGroup]")
{
    constexpr int k {2};

    ListNode five {5};
    ListNode four {4, &five};
    ListNode three {3, &four};
    ListNode two {2, &three};
    ListNode one {1, &two};

    const std::vector<int> expected_output {2, 1, 4, 3, 5};

    auto* head_fa = reverseKGroupFA(&one, k);
    for (const int node : expected_output)
    {
        REQUIRE(nullptr != head_fa);
        REQUIRE(node == head_fa->val);
        head_fa = head_fa->next;
    }
}

TEST_CASE("Example 2", "[reverseKGroup]")
{
    constexpr int k {3};

    ListNode five {5};
    ListNode four {4, &five};
    ListNode three {3, &four};
    ListNode two {2, &three};
    ListNode one {1, &two};

    const std::vector<int> expected_output {3, 2, 1, 4, 5};

    auto* head_fa = reverseKGroupFA(&one, k);
    for (const int node : expected_output)
    {
        REQUIRE(nullptr != head_fa);
        REQUIRE(node == head_fa->val);
        head_fa = head_fa->next;
    }
}

TEST_CASE("Example 3", "[reverseKGroup]")
{
    constexpr int k {1};

    ListNode five {5};
    ListNode four {4, &five};
    ListNode three {3, &four};
    ListNode two {2, &three};
    ListNode one {1, &two};

    const std::vector<int> expected_output {1, 2, 3, 4, 5};

    auto* head_fa = reverseKGroupFA(&one, k);
    for (const int node : expected_output)
    {
        REQUIRE(nullptr != head_fa);
        REQUIRE(node == head_fa->val);
        head_fa = head_fa->next;
    }
}

TEST_CASE("Example 4", "[reverseKGroup]")
{
    constexpr int k {2};

    ListNode two {2};
    ListNode one {1, &two};

    const std::vector<int> expected_output {2, 1};

    auto* head_fa = reverseKGroupFA(&one, k);
    for (const int node : expected_output)
    {
        REQUIRE(nullptr != head_fa);
        REQUIRE(node == head_fa->val);
        head_fa = head_fa->next;
    }
}
