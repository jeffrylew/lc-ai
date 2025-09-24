#include "ListNode.hpp"

#include <catch2/catch_test_macros.hpp>

static ListNode* reverseListFA(ListNode* head)
{
    //! @details https://leetcode.com/explore/interview/card/amazon/77
    //!          /linked-list/2979/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list.
    //!          Space complexity O(1).

    ListNode* new_head {nullptr};
    ListNode* curr_node {head};

    while (curr_node != nullptr)
    {
        auto* next_node = curr_node->next;
        curr_node->next = new_head;
        new_head        = curr_node;
        curr_node       = next_node;
    }

    return new_head;
}

//! DS1 is same as FA

static ListNode* reverseListDS2(ListNode* head)
{
    //! @details https://leetcode.com/problems/reverse-linked-list/editorial/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list.
    //!          Space complexity O(N) due to implicit stack space for recursion
    //!          that can go up to N levels deep.

    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    auto* new_head   = reverseListDS2(head->next);
    head->next->next = head;
    head->next       = nullptr;

    return new_head;
}

TEST_CASE("Example 1", "[reverseList]")
{
    ListNode five {5};
    ListNode four {4, &five};
    ListNode three {3, &four};
    ListNode two {2, &three};
    ListNode one {1, &two};

    auto* reversed_head_fa = reverseListFA(&one);

    REQUIRE(reversed_head_fa != nullptr);
    REQUIRE(reversed_head_fa->val == 5);
    REQUIRE(reversed_head_fa->next != nullptr);
    REQUIRE(reversed_head_fa->next->val == 4);
    REQUIRE(reversed_head_fa->next->next != nullptr);
    REQUIRE(reversed_head_fa->next->next->val == 3);
    REQUIRE(reversed_head_fa->next->next->next != nullptr);
    REQUIRE(reversed_head_fa->next->next->next->val == 2);
    REQUIRE(reversed_head_fa->next->next->next->next != nullptr);
    REQUIRE(reversed_head_fa->next->next->next->next->val == 1);

    /*
    auto* reversed_head_ds2 = reverseListDS2(&one);

    REQUIRE(reversed_head_ds2 != nullptr);
    REQUIRE(reversed_head_ds2->val == 5);
    REQUIRE(reversed_head_ds2->next != nullptr);
    REQUIRE(reversed_head_ds2->next->val == 4);
    REQUIRE(reversed_head_ds2->next->next != nullptr);
    REQUIRE(reversed_head_ds2->next->next->val == 3);
    REQUIRE(reversed_head_ds2->next->next->next != nullptr);
    REQUIRE(reversed_head_ds2->next->next->next->val == 2);
    REQUIRE(reversed_head_ds2->next->next->next->next != nullptr);
    REQUIRE(reversed_head_ds2->next->next->next->next->val == 1);
     */
}

TEST_CASE("Example 2", "[reverseList]")
{
    ListNode two {2};
    ListNode one {1, &two};

    auto* reversed_head_fa = reverseListFA(&one);

    REQUIRE(reversed_head_fa != nullptr);
    REQUIRE(reversed_head_fa->val == 2);
    REQUIRE(reversed_head_fa->next != nullptr);
    REQUIRE(reversed_head_fa->next->val == 1);

    /*
    auto* reversed_head_ds2 = reverseListDS2(&one);

    REQUIRE(reversed_head_ds2 != nullptr);
    REQUIRE(reversed_head_ds2->val == 2);
    REQUIRE(reversed_head_ds2->next != nullptr);
    REQUIRE(reversed_head_ds2->next->val == 1);
     */
}

TEST_CASE("Example 3", "[reverseList]")
{
    REQUIRE(nullptr == reverseListFA(nullptr));
    REQUIRE(nullptr == reverseListDS2(nullptr));
}
