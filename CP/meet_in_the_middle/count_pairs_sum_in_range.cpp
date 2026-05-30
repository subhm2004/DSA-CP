/*
 * ============================================================================
 * TOPIC    : Meet in the Middle — Count Pairs with Sum in Range
 * FILE     : count_pairs_sum_in_range.cpp
 * PROBLEM  : Count pairs (i,j) with L ≤ a[i]+a[j] ≤ R (n ≤ 40)
 * APPROACH : Split into halves; count pairs from left-sum + right-sum in range
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

long long countPairsSumInRange(const vector<int> &a, long long L, long long R) {
    int n = a.size(), mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());
    vector<long long> Ls = allSubsetSums(left), Rs = allSubsetSums(right);

    long long ans = 0;
    for (long long x : Ls) {
        auto lo = lower_bound(Rs.begin(), Rs.end(), L - x);
        auto hi = upper_bound(Rs.begin(), Rs.end(), R - x);
        ans += hi - lo;
    }
    return ans;
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6};
    cout << countPairsSumInRange(a, 5, 8) << endl;
    return 0;
}
