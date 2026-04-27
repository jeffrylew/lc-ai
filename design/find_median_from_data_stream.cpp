#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <functional>
#include <iterator>
#include <priority_queue>
#include <set>
#include <vector>

//! @class MedianFinderFA
//! @details https://leetcode.com/explore/interview/card/amazon/81/design/495/
//!
//!          First attempt solution does not pass Example 3.
class MedianFinderFA
{
public:
    void addNum(int num)
    {
        if (num >= 0)
        {
            min_heap.push(num);
        }
        else
        {
            max_heap.push(num);
        }

        if (min_heap.size() > max_heap.size())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
        else if (max_heap.size() > min_heap.size())
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }
    }

    double findMedian()
    {
        if (max_heap.size() > min_heap.size())
        {
            return static_cast<double>(max_heap.top());
        }

        if (min_heap.size() > max_heap.size())
        {
            return static_cast<double>(min_heap.top());
        }

        return static_cast<double>(min_heap.top() + max_heap.top()) / 2.0;
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    std::priority_queue<int>                                      max_heap;
};

//! @class MedianFinderDS1
//! @details leetcode.com/problems/find-median-from-data-stream/editorial
//!
//!          Simple sorting discussion solution runs into Time Limit Exceeded
//!          Time complexity O(N * log N) where N = number of elements in data
//!          stream. Adding a number takes amortized O(1) for a container with
//!          an efficient resizing scheme. Sorting takes O(N * log N).
//!          Space complexity O(N) to store the input in a container. No extra
//!          space is needed since sorting can usually be done in-place.
class MedianFinderDS1
{
public:
    //! Adds a number into the data stream
    void addNum(int num)
    {
        store.push_back(num);
    }

    //! Returns the median of the current data stream
    double findMedian()
    {
        std::ranges::sort(store);

        const auto store_size = static_cast<int>(std::ssize(store));
        const auto half_store = store_size / 2;

        //! If store_size is odd then return middle (store_size % 2 == 1)
        return store_size & 1
            ? static_cast<double>(store[half_store])
            : 0.5 * (store[half_store - 1] + store[half_store]);
    }

private:
    std::vector<int> store;
};

//! @class MedianFinderDS2
//! @details leetcode.com/problems/find-median-from-data-stream/editorial
//!
//!          Time complexity O(N) where N = number of elements in data stream.
//!          Binary search takes O(log N) to find the correct insertion position
//!          but insertion can take up to O(N) since elements have to be shifted
//!          to make room for the new element.
//!          Space complexity O(N) to hold the input in a container.
class MedianFinderDS2
{
public:
    void addNum(int num)
    {
        if (store.empty())
        {
            store.push_back(num);
        }
        else
        {
            //! Binary search followed by insertion
            auto num_lower_bound_it =
                std::lower_bound(store.begin(), store.end(), num);
            store.insert(num_lower_bound_it, num);
        }
    }

    double findMedian()
    {
        const auto store_size = static_cast<int>(std::ssize(store));
        const auto half_store = store_size / 2;

        return store_size & 1
            ? static_cast<double>(store[half_store])
            : 0.5 * (store[half_store - 1] + store[half_store]);
    }

private:
    std::vector<int> store;
};

//! @class MedianFinderDS3
//! @details leetcode.com/problems/find-median-from-data-stream/editorial
//!
//!          Time complexity O(5 * log N) + O(1) = O(log N) where N = number of
//!          elements in data stream. At worst, there are three heap insertions
//!          and two heap deletions from the top. Each takes O(log N). Finding
//!          the median takes O(1) since the tops of the heaps are directly
//!          accessible.
//!          Space complexity O(N) to store the input in containers.
class MedianFinderDS3
{
public:
    void addNum(int num)
    {
        //! Add to max heap
        max_heap.push(num);

        //! Balancing step
        min_heap.push(max_heap.top());
        max_heap.pop();

        //! Maintain size property
        if (max_heap.size() < min_heap.size())
        {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    double findMedian()
    {
        return max_heap.size() > min_heap.size()
            ? static_cast<double>(max_heap.top())
            : 0.5 * (max_heap.top() + min_heap.top());
    }

private:
    //! min_heap stores larger half of input numbers
    //! - All numbers in min_heap are >= to top element of min_heap
    //! max_heap stores smaller half of input numbers. It is allowed to store
    //! one more element than the min_heap in the worst case.
    //! - All numbers in max_heap are <= to top element of max_heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    std::priority_queue<int>                                      max_heap;
};

//! @class MedianFinderDS4
//! @details leetcode.com/problems/find-median-from-data-stream/editorial
class MedianFinderDS4
{
public:
    void addNum(int num)
    {
        const auto data_size = static_cast<int>(std::ssize(data));
        data.insert(num);

        if (data_size == 0)
        {
            //! First element inserted
            mid = data.begin();
        }
        else if (num < *mid)
        {
            //! Median is decreased
            mid = data_size & 1 ? mid : std::prev(mid);
        }
        else
        {
            //! Median is increased
            mid = data_size & 1 ? std::next(mid) : mid;
        }
    }

    double findMedian()
    {
        const auto data_size = static_cast<int>(std::ssize(data));
        return 0.5 * (*mid + *std::next(mid, data_size % 2 - 1));
    }

private:
    std::multiset<int> data;
    auto               mid = data.end();
};

TEST_CASE("Example 1", "[MedianFinder]")
{
    MedianFinderFA median_finder_fa;

    // min: [1] -> []
    // max: []  -> [1], retrieve from max.top()
    // min: [2] -> [2]
    // max: [1] -> [1], average min.top() and max.top()
    // min: [2, 3] -> [3]
    // max: [1]    -> [2, 1], retrieve from max.top()
    // min: [3, 4] -> [3, 4]
    // max: [2, 1] -> [2, 1], average min.top() and max.top()
    median_finder_fa.addNum(1);                  // arr = [1]
    median_finder_fa.addNum(2);                  // arr = [1, 2]
    CHECK(1.5 == median_finder_fa.findMedian()); // return 1.5 = (1 + 2) / 2
    median_finder_fa.addNum(3);                  // arr = [1, 2, 3]
    CHECK(2.0 == median_finder_fa.findMedian()); // return 2.0

    MedianFinderDS1 median_finder_ds1;
    median_finder_ds1.addNum(1);
    median_finder_ds1.addNum(2);
    CHECK(1.5 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(3);
    CHECK(2.0 == median_finder_ds1.findMedian());

    MedianFinderDS2 median_finder_ds2;
    median_finder_ds2.addNum(1);
    median_finder_ds2.addNum(2);
    CHECK(1.5 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(3);
    CHECK(2.0 == median_finder_ds2.findMedian());

    MedianFinderDS3 median_finder_ds3;
    median_finder_ds3.addNum(1);
    median_finder_ds3.addNum(2);
    CHECK(1.5 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(3);
    CHECK(2.0 == median_finder_ds3.findMedian());

    MedianFinderDS4 median_finder_ds4;
    median_finder_ds4.addNum(1);
    median_finder_ds4.addNum(2);
    CHECK(1.5 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(3);
    CHECK(2.0 == median_finder_ds4.findMedian());
}

TEST_CASE("Example 2", "[MedianFinder]")
{
    MedianFinderFA median_finder_fa;

    // min: []   -> [-1], retrieve from min.top()
    // max: [-1] -> []
    // min: [-1] -> [-1], average min.top() and max.top()
    // max: [-2] -> [-2]
    // min: [-1]     -> [-2, -1], retrieve from min.top()
    // max: [-2, -3] -> [-3]
    // min: [-2, -1] -> [-2, -1], average min.top() and max.top()
    // max: [-3, -4] -> [-3, -4]
    // min: [-2, -1]     -> [-3, -2, -1], retrieve from min.top()
    // max: [-3, -4, -5] -> [-4, -5]
    median_finder_fa.addNum(-1);                  // arr = [-1]
    CHECK(-1.0 == median_finder_fa.findMedian()); // return -1.0
    median_finder_fa.addNum(-2);                  // arr = [-1, -2]
    CHECK(-1.5 == median_finder_fa.findMedian()); // return -1.5
    median_finder_fa.addNum(-3);                  // arr = [-1, -2, -3]
    CHECK(-2.0 == median_finder_fa.findMedian()); // return -2.0
    median_finder_fa.addNum(-4);                  // arr = [-1, -2, -3, -4]
    CHECK(-2.5 == median_finder_fa.findMedian()); // return -2.5
    median_finder_fa.addNum(-5);                  // arr = [-1, -2, -3, -4, -5]
    CHECK(-3.0 == median_finder_fa.findMedian()); // return -3.0

    MedianFinderDS1 median_finder_ds1;
    median_finder_ds1.addNum(-1);
    CHECK(-1.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(-2);
    CHECK(-1.5 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(-3);
    CHECK(-2.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(-4);
    CHECK(-2.5 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(-5);
    CHECK(-3.0 == median_finder_ds1.findMedian());

    MedianFinderDS2 median_finder_ds2;
    median_finder_ds2.addNum(-1);
    CHECK(-1.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(-2);
    CHECK(-1.5 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(-3);
    CHECK(-2.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(-4);
    CHECK(-2.5 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(-5);
    CHECK(-3.0 == median_finder_ds2.findMedian());

    MedianFinderDS3 median_finder_ds3;
    median_finder_ds3.addNum(-1);
    CHECK(-1.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(-2);
    CHECK(-1.5 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(-3);
    CHECK(-2.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(-4);
    CHECK(-2.5 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(-5);
    CHECK(-3.0 == median_finder_ds3.findMedian());

    MedianFinderDS4 median_finder_ds4;
    median_finder_ds4.addNum(-1);
    CHECK(-1.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(-2);
    CHECK(-1.5 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(-3);
    CHECK(-2.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(-4);
    CHECK(-2.5 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(-5);
    CHECK(-3.0 == median_finder_ds4.findMedian());
}

TEST_CASE("Example 3", "[MedianFinder]")
{
    MedianFinderFA median_finder_fa;

    median_finder_fa.addNum(6);                     // arr = [6]
    // CHECK(6.0 == median_finder_fa.findMedian()); // return 6.0
    median_finder_fa.addNum(10);                    // arr = [6, 10]
    // CHECK(8.0 == median_finder_fa.findMedian()); // return 8.0
    median_finder_fa.addNum(2);                     // arr = [2, 6, 10]
    // CHECK(6.0 == median_finder_fa.findMedian()); // return 6.0
    median_finder_fa.addNum(6);                     // arr = [2, 6, 6, 10]
    // CHECK(6.0 == median_finder_fa.findMedian()); // return 6.0
    median_finder_fa.addNum(5);                     // arr = [2, 5, 6, 6, 10]
    // CHECK(6.0 == median_finder_fa.findMedian()); // return 6.0

    // arr = [0, 2, 5, 6, 6, 10]
    median_finder_fa.addNum(0);
    // CHECK(5.5 == median_finder_fa.findMedian());

    // arr = [0, 2, 5, 6, 6, 6, 10]
    median_finder_fa.addNum(6);
    // CHECK(6.0 == median_finder_fa.findMedian());

    // arr = [0, 2, 3, 5, 6, 6, 6, 10]
    median_finder_fa.addNum(3);
    // CHECK(5.5 == median_finder_fa.findMedian());

    // arr = [0, 1, 2, 3, 5, 6, 6, 6, 10]
    median_finder_fa.addNum(1);
    // CHECK(5.0 == median_finder_fa.findMedian());

    // arr = [0, 0, 1, 2, 3, 5, 6, 6, 6, 10]
    median_finder_fa.addNum(0);
    // CHECK(4.0 == median_finder_fa.findMedian());

    // arr = [0, 0, 0, 1, 2, 3, 5, 6, 6, 6, 10]
    median_finder_fa.addNum(0);
    // CHECK(3.0 == median_finder_fa.findMedian());

    MedianFinderDS1 median_finder_ds1;
    median_finder_ds1.addNum(6);
    CHECK(6.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(10);
    CHECK(8.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(2);
    CHECK(6.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(6);
    CHECK(6.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(5);
    CHECK(6.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(0);
    CHECK(5.5 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(6);
    CHECK(6.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(3);
    CHECK(5.5 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(1);
    CHECK(5.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(0);
    CHECK(4.0 == median_finder_ds1.findMedian());
    median_finder_ds1.addNum(0);
    CHECK(3.0 == median_finder_ds1.findMedian());

    MedianFinderDS2 median_finder_ds2;
    median_finder_ds2.addNum(6);
    CHECK(6.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(10);
    CHECK(8.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(2);
    CHECK(6.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(6);
    CHECK(6.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(5);
    CHECK(6.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(0);
    CHECK(5.5 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(6);
    CHECK(6.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(3);
    CHECK(5.5 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(1);
    CHECK(5.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(0);
    CHECK(4.0 == median_finder_ds2.findMedian());
    median_finder_ds2.addNum(0);
    CHECK(3.0 == median_finder_ds2.findMedian());

    MedianFinderDS3 median_finder_ds3;
    median_finder_ds3.addNum(6);
    CHECK(6.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(10);
    CHECK(8.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(2);
    CHECK(6.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(6);
    CHECK(6.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(5);
    CHECK(6.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(0);
    CHECK(5.5 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(6);
    CHECK(6.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(3);
    CHECK(5.5 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(1);
    CHECK(5.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(0);
    CHECK(4.0 == median_finder_ds3.findMedian());
    median_finder_ds3.addNum(0);
    CHECK(3.0 == median_finder_ds3.findMedian());

    MedianFinderDS4 median_finder_ds4;
    median_finder_ds4.addNum(6);
    CHECK(6.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(10);
    CHECK(8.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(2);
    CHECK(6.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(6);
    CHECK(6.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(5);
    CHECK(6.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(0);
    CHECK(5.5 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(6);
    CHECK(6.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(3);
    CHECK(5.5 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(1);
    CHECK(5.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(0);
    CHECK(4.0 == median_finder_ds4.findMedian());
    median_finder_ds4.addNum(0);
    CHECK(3.0 == median_finder_ds4.findMedian());
}

TEST_CASE("Two Heaps Example", "[MedianFinder]")
{
    MedianFinderDS3 median_finder_ds3;

    //! max_heap: [41]
    //! min_heap: []
    median_finder_ds3.addNum(41);
    CHECK(41.0 == median_finder_ds3.findMedian());

    //! max_heap: [35]
    //! min_heap: [41]
    median_finder_ds3.addNum(35);
    CHECK(38.0 == median_finder_ds3.findMedian());

    //! max_heap: [41, 35]
    //! min_heap: [62]
    median_finder_ds3.addNum(62);
    CHECK(41.0 == median_finder_ds3.findMedian());

    //! max_heap: [35, 4]
    //! min_heap: [41, 62]
    median_finder_ds3.addNum(4);
    CHECK(38.0 == median_finder_ds3.findMedian());

    //! max_heap: [41, 35, 4]
    //! min_heap: [62, 97]
    median_finder_ds3.addNum(97);
    CHECK(41.0 == median_finder_ds3.findMedian());

    //! max_heap: [41, 35, 4]
    //! min_heap: [62, 97, 108]
    median_finder_ds3.addNum(108);
    CHECK(51.5 == median_finder_ds3.findMedian());
}
