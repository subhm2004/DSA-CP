/*
 * ============================================================================
 * TOPIC    : Monotonic Queue (Deque)
 * FILE     : monotonic_queue.cpp
 * PROBLEM  : Sliding window minimum / maximum
 * LEETCODE : 239 — Sliding Window Maximum
 * APPROACH : Deque storing indices in increasing/decreasing order
 * COMPLEX  : O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> slidingWindowMinimum(const vector<int> &a, int k) {
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            ans.push_back(a[dq.front()]);
    }
    return ans;
}

vector<int> slidingWindowMaximum(const vector<int> &a, int k) {
    deque<int> dq;
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            ans.push_back(a[dq.front()]);
    }
    return ans;
}

int main() {
    vector<int> a = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    cout << "Window min: ";
    for (int x : slidingWindowMinimum(a, k)) cout << x << " ";
    cout << "\nWindow max: ";
    for (int x : slidingWindowMaximum(a, k)) cout << x << " ";
    cout << endl;
    return 0;
}
