/*
 * ============================================================================
 * TOPIC    : Difference Array Technique
 * FILE     : difference_array_1d.cpp
 * PROBLEM  : Range update [l,r] += val on array (offline / batch updates)
 * APPROACH : diff[l] += val, diff[r+1] -= val, then prefix sum
 * COMPLEX  : Update O(1), Rebuild O(n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<long long> applyDifferenceArray(int n, const vector<tuple<int, int, long long>> &updates) {
    vector<long long> diff(n + 1, 0);

    for (auto [l, r, val] : updates) {
        diff[l] += val;
        if (r + 1 <= n)
            diff[r + 1] -= val;
    }

    vector<long long> arr(n);
    long long cur = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        arr[i] = cur;
    }
    return arr;
}

int main() {
    int n = 5;
    vector<tuple<int, int, long long>> updates = {
        {0, 2, 3}, {1, 3, 2}, {2, 4, 1}
    };

    vector<long long> result = applyDifferenceArray(n, updates);
    cout << "After range updates: ";
    for (long long x : result)
        cout << x << " ";
    cout << endl;
    return 0;
}
