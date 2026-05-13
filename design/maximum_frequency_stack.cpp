#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <unordered_map>
#include <vector>

struct Element
{
    int              value {-1};
    std::vector<int> indices;
};

//! @class FreqStackFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/design/3001/
class FreqStackFA
{
public:
    void push(int val)
    {
        val_indices[val].push_back(last_index);
        ++last_index;
    }

    int pop()
    {
        //! @todo
    }

private:
    int last_index {};

    //! Map of <element value, indices that value is at>
    std::unordered_map<int, std::vector<int>> val_indices;

    // std::priority_queue<Element, std::vector<Element>, Compare> 
};

TEST_CASE("Example 1", "[FreqStack]")
{
    FreqStackFA freq_stack_fa;
    freq_stack_fa.push(5); // stack is [5]
    freq_stack_fa.push(7); // stack is [5, 7]
    freq_stack_fa.push(5); // stack is [5, 7, 5]
    freq_stack_fa.push(7); // stack is [5, 7, 5, 7]
    freq_stack_fa.push(4); // stack is [5, 7, 5, 7, 4]
    freq_stack_fa.push(5); // stack is [5, 7, 5, 7, 4, 5]

    //! Return 5 since it is the most frequent. stack becomes [5, 7, 5, 7, 4]
    CHECK(5 == freq_stack_fa.pop());

    //! Return 7 since 5 and 7 are the most frequent but 7 is closest to the top
    //! stack becomes [5, 7, 5, 4]
    CHECK(7 == freq_stack_fa.pop());

    //! Return 5 since it is the most frequent. stack becomes [5, 7, 4]
    CHECK(5 == freq_stack_fa.pop());

    //! Return 4 since 4, 5, and 7 are the most frequent but 4 is closest to the
    //! top. stack becomes [5, 7]
    CHECK(4 == freq_stack_fa.pop());
}
