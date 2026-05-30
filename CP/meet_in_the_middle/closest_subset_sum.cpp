/*
 * ============================================================================
 * TOPIC    : Meet in the Middle — Closest Subset Sum
 * FILE     : closest_subset_sum.cpp
 * PROBLEM  : Subset sum closest to target (n ≤ 40)
 * APPROACH : MITM + two-pointer merge on sorted half-sums
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
    return sums;
}

long long closestSubsetSum(const vector<int> &a, long long target) {
    int n = a.size(), mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    vector<long long> L = allSubsetSums(left), R = allSubsetSums(right);

    long long best = LLONG_MAX, bestSum = 0;
    int j = (int)R.size() - 1;
    for (long long x : L) {
        while (j > 0 && abs(x + R[j] - target) >= abs(x + R[j - 1] - target))
            j--;
        long long cand = x + R[j];
        if (abs(cand - target) < best) {
            best = abs(cand - target);
            bestSum = cand;
        }
    }
    return bestSum;
}

int main() {
    vector<int> a = {3, 9, 7, 1};
    cout << closestSubsetSum(a, 12) << endl; // 10 or 12 depending on subset
    return 0;
}
