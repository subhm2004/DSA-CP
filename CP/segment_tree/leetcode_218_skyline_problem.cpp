#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 218 — The Skyline Problem
// ────────────────────────────────────────────────────────────────────────────
// Problem: Buildings [[L,R,H],...] se skyline key points nikalo
// Approach: Sweep line + multiset (active heights track karo)
//   Har building: start pe +H, end pe -H event
//   x sort karo, multiset se current max height lo
//   Max change ho to [x, newMax] answer me daalo
//
// Note: Segment tree se bhi ho sakta (compressed x pe range max),
//       lekin sweep + multiset O(n log n) me sabse clean hai.
// Complexity: O(n log n)
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    // ── getSkyline: sweep line se skyline points ──────────────────────────────
    //   1) har building ke liye (L, +H) aur (R, -H) events banao
    //   2) x ascending, same x pe end (-H) pehle process (height hatao)
    //   3) multiset me height add/remove, current max = *rbegin()
    //   4) max badla to result me {x, max} push
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
    {
        vector<pair<int, int>> events; // (x, delta height)

        for (const vector<int> &b : buildings)
        {
            int L = b[0], R = b[1], H = b[2];
            events.push_back({L, H});
            events.push_back({R, -H});
        }

        sort(events.begin(), events.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            if (a.first != b.first)
                return a.first < b.first;
            return a.second > b.second; // same x: start (+H) pehle, end (-H) baad
        });

        multiset<int> active;
        active.insert(0);
        vector<vector<int>> ans;
        int prevMax = 0;

        for (const pair<int, int> &ev : events)
        {
            int x = ev.first;
            int h = ev.second;

            if (h > 0)
                active.insert(h);
            else
                active.erase(active.find(-h));

            int curMax = *active.rbegin();
            if (curMax != prevMax)
            {
                ans.push_back({x, curMax});
                prevMax = curMax;
            }
        }

        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    vector<vector<int>> skyline = sol.getSkyline(buildings);

    cout << "Skyline key points:\n";
    for (const vector<int> &p : skyline)
        cout << "[" << p[0] << ", " << p[1] << "]\n";

    return 0;
}
