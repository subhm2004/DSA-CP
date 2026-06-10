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

// ════════════════════════════════════════════════════════════════════════════
// LARGEST RECTANGLE IN HISTOGRAM — monotonic stack se max area
// ────────────────────────────────────────────────────────────────────────────
// increasing stack of indices; chhoti bar aaye → pop karke area calculate
// width = i - stack.top() - 1 (ya i agar stack empty)
// sentinel 0 end pe — sab bars flush karne ke liye
// ════════════════════════════════════════════════════════════════════════════

class Solution {
public:
    // ── largestRectangleArea: histogram mein max rectangle area ─────────────
    //   1) index stack — heights ke indices rakho
    //   2) har bar (ya end sentinel 0): jab heights[top] > cur → pop
    //   3) pop pe area = h * w compute, best update
    //   4) current index push
    int largestRectangleArea(vector<int> &heights) {
        int n = heights.size();
        stack<int> st;
        int best = 0;
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : heights[i]; // sentinel 0 — sab flush
            while (!st.empty() && heights[st.top()] > cur) {
                int h = heights[st.top()];
                st.pop();                      // chhoti bar — rectangle band
                int w = st.empty() ? i : i - st.top() - 1;
                best = max(best, h * w);
            }
            st.push(i);                        // current bar index push
        }
        return best;
    }
};

int main() {
    vector<int> h = {2, 1, 5, 6, 2, 3};
    cout << Solution().largestRectangleArea(h) << endl; // 10
    return 0;
}
