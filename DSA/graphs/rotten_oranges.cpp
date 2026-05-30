/*
 * ============================================================================
 * TOPIC    : Graphs — Rotten Oranges (Multi-source BFS)
 * FILE     : rotten_oranges.cpp
 * PROBLEM  : Minutes until all oranges rot
 * LEETCODE : 994 — Rotting Oranges
 * APPROACH : BFS from all rotten cells simultaneously
 * COMPLEX  : Time: O(rows*cols)  |  Space: O(rows*cols)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int orangesRotting(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 2) q.push({i, j});
            else if (grid[i][j] == 1) fresh++;

    int minutes = 0;
    int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    while (!q.empty() && fresh > 0) {
        int sz = q.size();
        minutes++;
        while (sz--) {
            auto [i, j] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == 1) {
                    grid[ni][nj] = 2;
                    fresh--;
                    q.push({ni, nj});
                }
            }
        }
    }
    return fresh == 0 ? minutes : -1;
}

int main() {
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << orangesRotting(grid) << endl; // 4
    return 0;
}
