/*
 * ============================================================================
 * TOPIC    : Bit Manipulation — Meet in Middle (basic)
 * FILE     : meet_in_middle.cpp
 * PROBLEM  : Subset with sum = target (n ≤ 40)
 * NOTE     : Full MITM templates → CP/meet_in_the_middle/
 * APPROACH : Split array in half, store sums, binary search complement
 * COMPLEX  : Time: O(2^(n/2) log 2^(n/2))  |  Space: O(2^(n/2))
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

bool subsetSumMeetInMiddle(const vector<int> &a, int target) {
    int n = a.size(), mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());

    auto allSums = [](const vector<int> &v) {
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
    };

    vector<long long> L = allSums(left), R = allSums(right);

    for (long long x : L) {
        long long need = target - x;
        if (binary_search(R.begin(), R.end(), need))
            return true;
    }
    return false;
}

int main() {
    vector<int> a = {3, 34, 4, 12, 5, 2};
    int target = 9;
    cout << "Subset sum " << target << " exists: "
         << (subsetSumMeetInMiddle(a, target) ? "YES" : "NO") << endl;
    return 0;
}
