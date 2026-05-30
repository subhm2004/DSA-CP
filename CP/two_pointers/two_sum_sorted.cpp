/*
 * ============================================================================
 * TOPIC    : Two Pointers
 * FILE     : two_sum_sorted.cpp
 * PROBLEM  : Two sum in sorted array — find pair with target
 * APPROACH : l=0, r=n-1, move based on sum vs target
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

pair<int, int> twoSumSorted(vector<int> a, int target) {
    sort(a.begin(), a.end());
    int l = 0, r = (int)a.size() - 1;

    while (l < r) {
        long long sum = (long long)a[l] + a[r];
        if (sum == target)
            return {a[l], a[r]};
        if (sum < target)
            l++;
        else
            r--;
    }
    return {-1, -1};
}

int main() {
    vector<int> a = {2, 7, 11, 15};
    int target = 9;
    auto [x, y] = twoSumSorted(a, target);
    cout << "Pair with sum " << target << ": " << x << ", " << y << endl;
    return 0;
}
