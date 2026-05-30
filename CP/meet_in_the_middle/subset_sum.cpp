/*
 * ============================================================================
 * TOPIC    : Meet in the Middle — Subset Sum
 * FILE     : subset_sum.cpp
 * PROBLEM  : Does any subset sum to target? (n ≤ 40)
 * LEETCODE : 416 — Partition Equal Subset Sum (MITM for n≤40)
 * APPROACH : Split array; enumerate all sums of each half; binary search complement
 * COMPLEX  : Time: O(2^(n/2) log 2^(n/2))  |  Space: O(2^(n/2))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

vector<long long> allSubsetSums(const vector<int> &v) {
    vector<long long> sums;
    int m = v.size();
    for (int mask = 0; mask < (1 << m); mask++) {
        long long s = 0;
        for (int i = 0; i < m; i++)
            if (mask & (1 << i))
                s += v[i];
        sums.push_back(s);
    }
    sort(sums.begin(), sums.end());
    sums.erase(unique(sums.begin(), sums.end()), sums.end());
    return sums;
}

bool subsetSumMeetInMiddle(const vector<int> &a, long long target) {
    int n = a.size(), mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    vector<long long> L = allSubsetSums(left), R = allSubsetSums(right);
    for (long long x : L) {
        if (binary_search(R.begin(), R.end(), target - x))
            return true;
    }
    return false;
}

int main() {
    vector<int> a = {3, 34, 4, 12, 5, 2};
    cout << (subsetSumMeetInMiddle(a, 9) ? "YES" : "NO") << endl; // YES
    return 0;
}
