/*
 * ============================================================================
 * TOPIC    : Stacks — Largest Rectangle in Histogram (Max Area)
 * FILE     : largest_rectangle_histogram.cpp
 * PROBLEM  : Max rectangle area in histogram bars
 * LEETCODE : 84 — Largest Rectangle in Histogram
 * APPROACH : Monotonic increasing stack; pop when bar shorter than current
 * COMPLEX  : Time: O(n)  |  Space: O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        stack<int> st;
        int best = 0;
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : heights[i];
            while (!st.empty() && heights[st.top()] > cur) {
                int h = heights[st.top()];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                best = max(best, h * w);
            }
            st.push(i);
        }
        return best;
    }
};

int main() {
    vector<int> h = {2, 1, 5, 6, 2, 3};
    cout << Solution().largestRectangleArea(h) << endl; // 10
    return 0;
}
