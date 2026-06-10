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

// ════════════════════════════════════════════════════════════════════════════
// MEDIAN FROM STREAM — Do heaps se running median
// ────────────────────────────────────────────────────────────────────────────
// lo = max-heap: lower half (chhote numbers) — top = max of lower half
// hi = min-heap: upper half (bade numbers) — top = min of upper half
// Balance: lo.size == hi.size ya lo.size == hi.size+1
// Median: equal size -> average of tops; odd -> lo.top()
// ════════════════════════════════════════════════════════════════════════════

class MedianFinder {
    priority_queue<int> lo; // max-heap: lower half
    priority_queue<int, vector<int>, greater<int>> hi; // min-heap: upper half

    // ── balance: dono heaps ka size maintain karo ──────────────────────────
    //   1) lo zyada bada (size > hi+1) -> lo.top hi me shift
    //   2) hi zyada bada -> hi.top lo me shift
    //   3) hamesha lo.size >= hi.size aur diff max 1
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
    // ── addNum: naya number sahi heap me daalo ───────────────────────────
    //   1) lo khali ya num <= lo.top -> lo me (lower half)
    //   2) warna hi me (upper half)
    //   3) balance() se sizes fix karo
    void addNum(int num) {
        if (lo.empty() || num <= lo.top())
            lo.push(num);
        else
            hi.push(num);
        balance();
    }

    // ── findMedian: current median return ──────────────────────────────────
    //   1) equal size -> (lo.top + hi.top) / 2.0
    //   2) odd total -> lo.top() (lower half me extra element)
    double findMedian() {
        if (lo.size() == hi.size())
            return (lo.top() + hi.top()) / 2.0;
        return lo.top();
    }
};

// ── main: stream demo — 1,2 -> 1.5; phir 3 -> 2 ────────────────────────────
int main() {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << mf.findMedian() << endl; // 1.5
    mf.addNum(3);
    cout << mf.findMedian() << endl; // 2
    return 0;
}
