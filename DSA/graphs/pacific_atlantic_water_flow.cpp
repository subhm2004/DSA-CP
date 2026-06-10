/*
 * ============================================================================
 * TOPIC    : Graphs — Pacific Atlantic Water Flow
 * FILE     : pacific_atlantic_water_flow.cpp
 * PROBLEM  : Cells from which water reaches both oceans
 * LEETCODE : 417 — Pacific Atlantic Water Flow
 * APPROACH : Reverse DFS from both oceans; intersection of reachable cells
 * COMPLEX  : Time: O(m*n)  |  Space: O(m*n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 417 — Pacific Atlantic Water Flow
// ────────────────────────────────────────────────────────────────────────────
// Problem: Height grid me wo cells dhundho jahan se water Pacific (top/left)
//          aur Atlantic (bottom/right) DONO oceans tak flow kar sakta hai.
//          Water sirf equal ya higher height pe ja sakta hai.
//
// Approach: Reverse DFS from Ocean Borders
//   - Pacific borders se DFS — water UPSTREAM ja sakta hai (higher/equal)
//   - Atlantic borders se alag DFS
//   - Dono reachable sets ka intersection = answer cells
//   - Reverse thinking: ocean se uphill climb karo
//
// Complexity: Time O(m×n)  |  Space O(m×n) for vis arrays
// ════════════════════════════════════════════════════════════════════════════

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

// ── dfs: ocean border se uphill reachable cells mark karo ──
//   1) vis[i][j] = true — ye cell ocean se reachable
//   2) 4 directions explore: neighbor higher/equal height hona chahiye
//   3) Already visited ya lower height → skip
//   4) Recursively dfs — water reverse flow (uphill) track karo
void dfs(const vector<vector<int>> &h, vector<vector<bool>> &vis, int i, int j) {
    vis[i][j] = true;
    for (int d = 0; d < 4; d++) {
        int ni = i + dx[d], nj = j + dy[d];
        if (ni < 0 || nj < 0 || ni >= (int)h.size() || nj >= (int)h[0].size()) continue;
        if (vis[ni][nj] || h[ni][nj] < h[i][j]) continue;  // uphill only — neighbor >= current
        dfs(h, vis, ni, nj);
    }
}

// ── pacificAtlantic: dono oceans tak flow wale cells return ──
//   1) pac aur atl do vis matrices — Pacific/Atlantic reachable
//   2) Pacific borders (top row + left col) se dfs
//   3) Atlantic borders (bottom row + right col) se dfs
//   4) Dono vis true wale cells ans me push — intersection
//   5) Coordinates list return
vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    int n = heights.size(), m = heights[0].size();
    vector<vector<bool>> pac(n, vector<bool>(m)), atl(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        dfs(heights, pac, i, 0);      // Pacific: left edge
        dfs(heights, atl, i, m - 1);  // Atlantic: right edge
    }
    for (int j = 0; j < m; j++) {
        dfs(heights, pac, 0, j);      // Pacific: top edge
        dfs(heights, atl, n - 1, j);  // Atlantic: bottom edge
    }

    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (pac[i][j] && atl[i][j])
                ans.push_back({i, j});  // dono oceans reachable — answer cell
    return ans;
}

int main() {
    vector<vector<int>> h = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    cout << pacificAtlantic(h).size() << endl; // 7
    return 0;
}
