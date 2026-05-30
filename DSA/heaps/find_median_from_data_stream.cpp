/*
 * ============================================================================
 * TOPIC    : Heaps — Find Median from Data Stream (Two Heaps)
 * FILE     : find_median_from_data_stream.cpp
 * PROBLEM  : Maintain median after each addNum call
 * LEETCODE : 295 — Find Median from Data Stream
 * APPROACH : Max-heap for lower half, min-heap for upper half; balance sizes
 * COMPLEX  : addNum: O(log n)  |  findMedian: O(1)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
    priority_queue<int> lo; // max-heap: lower half
    priority_queue<int, vector<int>, greater<int>> hi; // min-heap: upper half

    void balance() {
        if (lo.size() > hi.size() + 1) {
            hi.push(lo.top());
            lo.pop();
        } else if (hi.size() > lo.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

public:
    void addNum(int num) {
        if (lo.empty() || num <= lo.top())
            lo.push(num);
        else
            hi.push(num);
        balance();
    }

    double findMedian() {
        if (lo.size() == hi.size())
            return (lo.top() + hi.top()) / 2.0;
        return lo.top();
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << mf.findMedian() << endl; // 1.5
    mf.addNum(3);
    cout << mf.findMedian() << endl; // 2
    return 0;
}
