/*
 * ============================================================================
 * TOPIC    : Sliding Window
 * FILE     : max_sum_subarray_size_k.cpp
 * PROBLEM  : Maximum sum of subarray of fixed size K
 * APPROACH : Classic fixed-size sliding window
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxSumSubarrayK(const vector<int> &a, int k) {
    int n = a.size();
    if (n < k)
        return -1;

    int window = 0;
    for (int i = 0; i < k; i++)
        window += a[i];

    int best = window;
    for (int r = k; r < n; r++) {
        window += a[r] - a[r - k];
        best = max(best, window);
    }
    return best;
}

int main() {
    vector<int> a = {2, 1, 5, 1, 3, 2};
    int k = 3;
    cout << "Max sum of " << k << "-size subarray = " << maxSumSubarrayK(a, k) << endl;
    return 0;
}
