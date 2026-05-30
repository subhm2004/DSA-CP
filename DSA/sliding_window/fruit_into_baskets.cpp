/*
 * ============================================================================
 * TOPIC    : Sliding Window — Fruit Into Baskets
 * FILE     : fruit_into_baskets.cpp
 * PROBLEM  : Longest subarray with at most 2 distinct types
 * LEETCODE : 904 — Fruit Into Baskets
 * APPROACH : Variable window — shrink when >2 types in map
 * COMPLEX  : Time: O(n)  |  Space: O(1) types
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int totalFruit(vector<int> &fruits) {
    unordered_map<int, int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < (int)fruits.size(); r++) {
        cnt[fruits[r]]++;
        while ((int)cnt.size() > 2) {
            if (--cnt[fruits[l]] == 0) cnt.erase(fruits[l]);
            l++;
        }
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    vector<int> fruits = {1,2,1,2,3,2,2};
    cout << totalFruit(fruits) << endl; // 4
    return 0;
}
