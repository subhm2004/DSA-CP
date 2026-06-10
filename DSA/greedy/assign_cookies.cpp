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

// ════════════════════════════════════════════════════════════════════════════
// ASSIGN COOKIES — Chhote greed se match karo
// ────────────────────────────────────────────────────────────────────────────
// g = bachcho ki greed (min cookie size chahiye)
// s = cookie sizes — dono sort karo
// Sabse chhote bachche ko sabse chhoti sufficient cookie do
// Cookie chhoti hai to j++ (badi cookie try) — bachcha wait nahi karta
// ════════════════════════════════════════════════════════════════════════════

// ── findContentChildren: max khush bachche count ───────────────────────────
//   1) g aur s dono sort — chhota pehle
//   2) two pointers i (child), j (cookie)
//   3) s[j] >= g[i] -> happy++, dono aage
//   4) warna sirf j++ — badi cookie dhundho
int findContentChildren(vector<int> &g, vector<int> &s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    int i = 0, j = 0, happy = 0;
    while (i < (int)g.size() && j < (int)s.size()) {
        if (s[j] >= g[i]) {
            happy++;
            i++;
        }
        j++; // cookie hamesha aage badhti hai
    }
    return happy;
}

// ── main: g={1,2,3}, s={1,1} -> 1 child ────────────────────────────────────
int main() {
    vector<int> g = {1,2,3}, s = {1,1};
    cout << findContentChildren(g, s) << endl; // 1
    return 0;
}
