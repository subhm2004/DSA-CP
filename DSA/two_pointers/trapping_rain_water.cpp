/*
 * ============================================================================
 * TOPIC    : Two Pointers — Trapping Rain Water
 * FILE     : trapping_rain_water.cpp
 * PROBLEM  : Total water trapped between bars
 * LEETCODE : 42 — Trapping Rain Water
 * APPROACH : Two pointers with leftMax/rightMax
 * COMPLEX  : Time: O(n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int trap(vector<int> &h) {
    int l = 0, r = h.size() - 1, leftMax = 0, rightMax = 0, water = 0;
    while (l < r) {
        if (h[l] < h[r]) {
            leftMax = max(leftMax, h[l]);
            water += leftMax - h[l];
            l++;
        } else {
            rightMax = max(rightMax, h[r]);
            water += rightMax - h[r];
            r--;
        }
    }
    return water;
}

int main() {
    vector<int> h = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << trap(h) << endl; // 6
    return 0;
}
