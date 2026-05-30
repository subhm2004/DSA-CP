/*
 * ============================================================================
 * TOPIC    : Greedy — Assign Cookies
 * FILE     : assign_cookies.cpp
 * PROBLEM  : Max children satisfied with cookie sizes
 * LEETCODE : 455 — Assign Cookies
 * APPROACH : Sort both; match smallest sufficient cookie
 * COMPLEX  : Time: O(n log n)  |  Space: O(1)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int findContentChildren(vector<int> &g, vector<int> &s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0, happy = 0;
    while (i < (int)g.size() && j < (int)s.size()) {
        if (s[j] >= g[i]) {
            happy++;
            i++;
        }
        j++;
    }
    return happy;
}

int main() {
    vector<int> g = {1,2,3}, s = {1,1};
    cout << findContentChildren(g, s) << endl; // 1
    return 0;
}
