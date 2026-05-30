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

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

void dfs(const vector<vector<int>> &h, vector<vector<bool>> &vis, int i, int j) {
    vis[i][j] = true;
    for (int d = 0; d < 4; d++) {
        int ni = i + dx[d], nj = j + dy[d];
        if (ni < 0 || nj < 0 || ni >= (int)h.size() || nj >= (int)h[0].size()) continue;
        if (vis[ni][nj] || h[ni][nj] < h[i][j]) continue;
        dfs(h, vis, ni, nj);
    }
}

vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    int n = heights.size(), m = heights[0].size();
    vector<vector<bool>> pac(n, vector<bool>(m)), atl(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        dfs(heights, pac, i, 0);
        dfs(heights, atl, i, m - 1);
    }
    for (int j = 0; j < m; j++) {
        dfs(heights, pac, 0, j);
        dfs(heights, atl, n - 1, j);
    }

    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (pac[i][j] && atl[i][j])
                ans.push_back({i, j});
    return ans;
}

int main() {
    vector<vector<int>> h = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    cout << pacificAtlantic(h).size() << endl; // 7
    return 0;
}
