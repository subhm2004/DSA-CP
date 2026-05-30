/*
 * ============================================================================
 * TOPIC    : Two Pointers — Container With Most Water
 * FILE     : container_with_most_water.cpp
 * PROBLEM  : Max area between vertical lines
 * LEETCODE : 11 — Container With Most Water
 * APPROACH : Two pointers from ends — move shorter line inward
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int maxArea(vector<int> &h) {
    int l = 0, r = h.size() - 1, best = 0;
    while (l < r) {
        best = max(best, min(h[l], h[r]) * (r - l));
        if (h[l] < h[r]) l++;
        else r--;
    }
    return best;
}

int main() {
    vector<int> h = {1,8,6,2,5,4,8,3,7};
    cout << maxArea(h) << endl; // 49
    return 0;
}
