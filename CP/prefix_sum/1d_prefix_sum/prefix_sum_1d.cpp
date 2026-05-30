/*
 * ============================================================================
 * TOPIC    : Prefix Sum — 1D
 * FILE     : prefix_sum_1d.cpp
 * PROBLEM  : Range sum queries on static array
 * APPROACH : prefix[i] = sum of arr[0..i-1]
 * COMPLEX  : Build O(n), Query O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct PrefixSum1D {
    vector<long long> pref;

    PrefixSum1D(const vector<int> &a) {
        pref.assign(a.size() + 1, 0);
        for (int i = 0; i < (int)a.size(); i++)
            pref[i + 1] = pref[i] + a[i];
    }

    long long rangeSum(int l, int r) const {
        return pref[r + 1] - pref[l];
    }
};

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    PrefixSum1D ps(a);
    cout << "Sum [1,3] = " << ps.rangeSum(1, 3) << endl;
    cout << "Sum [0,4] = " << ps.rangeSum(0, 4) << endl;
    return 0;
}
