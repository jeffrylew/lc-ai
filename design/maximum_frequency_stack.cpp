#include <catch2/catch_test_macros.hpp>

#include <queue>
#include <unordered_map>
#include <unordered_set>
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
        value_indices[val].push_back(last_index);
        ++last_index;

        const int prev_count {value_counts[val]};
        const int curr_count {++value_counts[val]};
        if (prev_count > 0)
        {
            frequency_values
        }
    }

    int pop()
    {
        //! Get the most frequent element
        const int most_frequent_element {};

        value_indices[most_frequent_element].pop_back();
        if (value_indices[most_frequent_element].empty())
        {
            value_indices.erase(most_frequent_element);
        }

        return most_frequent_element;
    }

    // Need to keep track of most frequent element and remove it
    // Need to keep track of most frequent element closest to the top if tied
    // Map to keep track of element value and indices that element is at
    // Max heap of iterators in map that returns iterator to most frequent ele
    // Map of <element frequency, vector of element values with this frequency>

private:
    int last_index {};

    //! Map of <element value, indices that value is at>
    std::unordered_map<int, std::vector<int>> value_indices;

    //! Map of <element value, element count>
    std::unordered_map<int, int> value_counts;

    //! Map of <element frequency, element values at this frequen
    std::unordered_map<int, std::vector<int>> frequency_values;

    auto element_comparator = [](const Element& lhs, const Element& rhs) {
        return lhs.indices.size() < rhs.indices.size()
            || lhs.indices.back() < rhs.indices.back();
    };

    std::priority_queue<Element,
                        std::vector<Element>,
                        decltype(element_comparator)> element_heap;
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
