/*
 * ============================================================================
 * TOPIC    : Graphs — Max Area of Island
 * FILE     : max_area_of_island.cpp
 * PROBLEM  : Largest connected group of 1s in grid
 * LEETCODE : 695 — Max Area of Island
 * APPROACH : Flood fill DFS; track component size
 * COMPLEX  : Time: O(m*n)  |  Space: O(m*n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) return 0;
    grid[i][j] = 0;
    return 1 + dfs(grid, i + 1, j) + dfs(grid, i - 1, j)
             + dfs(grid, i, j + 1) + dfs(grid, i, j - 1);
}

int maxAreaOfIsland(vector<vector<int>> grid) {
    int best = 0;
    for (int i = 0; i < (int)grid.size(); i++)
        for (int j = 0; j < (int)grid[0].size(); j++)
            if (grid[i][j] == 1)
                best = max(best, dfs(grid, i, j));
    return best;
}

int main() {
    vector<vector<int>> grid = {{0,0,1,0,0},{0,0,0,0,0},{0,1,1,0,0}};
    cout << maxAreaOfIsland(grid) << endl; // 3
    return 0;
}
