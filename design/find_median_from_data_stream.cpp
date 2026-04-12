#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <priority_queue>
#include <vector>

//! @class MedianFinderFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/design/495/
class MedianFinderFA
{
public:
    void addNum(int num)
    {
        min_heap.push(num);
        if (min_heap.size() > max_heap.size())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double findMedian()
    {
        if (max_heap.size() > min_heap.size())
        {
            return static_cast<double>(max_heap.top());
        }

        return static_cast<double>(min_heap.top() + max_heap.top()) / 2.0;
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    std::priority_queue<int>                                      max_heap;
};

TEST_CASE("Example 1", "[MedianFinder]")
{
    MedianFinderFA median_finder;

    // min: [1] -> []
    // max: []  -> [1], retrieve from max for first median b/c sizes not equal
    // min: [2] -> [2]
    // max: [1] -> [1], average min.top() and max.top()
    // min: [2, 3] -> [3]
    // max: [1]    -> [2, 1], retrieve from max.top()
    // min: [3, 4] -> [3, 4]
    // max: [2, 1] -> [2, 1], average min.top() and max.top()
    median_finder.addNum(1);                  // arr = [1]
    median_finder.addNum(2);                  // arr = [1, 2]
    CHECK(1.5 == median_finder.findMedian()); // return 1.5 = (1 + 2) / 2
    median_finder.addNum(3);                  // arr = [1, 2, 3]
    CHECK(2.0 == median_finder.findMedian()); // return 2.0
}
