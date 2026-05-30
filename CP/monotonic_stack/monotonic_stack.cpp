/*
 * ============================================================================
 * TOPIC    : Monotonic Stack
 * FILE     : monotonic_stack.cpp
 * PROBLEM  : Next Greater Element, Largest Rectangle in Histogram
 * LEETCODE : 496 — Next Greater Element I / 84 — Largest Rectangle in Histogram
 * APPROACH : Maintain decreasing/increasing stack
 * COMPLEX  : O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(const vector<int> &a) {
    int n = a.size();
    vector<int> ans(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            ans[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}

long long largestRectangleHistogram(const vector<int> &h) {
    int n = h.size();
    stack<int> st;
    long long best = 0;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n) ? 0 : h[i];
        while (!st.empty() && h[st.top()] > cur) {
            int height = h[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            best = max(best, 1LL * height * width);
        }
        st.push(i);
    }
    return best;
}

int main() {
    vector<int> a = {4, 5, 2, 10, 8};
    auto nge = nextGreaterElement(a);
    cout << "Next Greater: ";
    for (int x : nge) cout << x << " ";
    cout << endl;

    vector<int> h = {2, 1, 5, 6, 2, 3};
    cout << "Max rectangle area = " << largestRectangleHistogram(h) << endl;
    return 0;
}
