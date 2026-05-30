/*
 * ============================================================================
 * TOPIC    : Graphs — Number of Islands
 * FILE     : number_of_islands.cpp
 * PROBLEM  : Count connected '1' components in grid
 * LEETCODE : 200 — Number of Islands
 * APPROACH : DFS/BFS flood fill on grid
 * COMPLEX  : Time: O(rows*cols)  |  Space: O(rows*cols)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void dfsGrid(vector<vector<char>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != '1') return;
    grid[i][j] = '0';
    dfsGrid(grid, i + 1, j);
    dfsGrid(grid, i - 1, j);
    dfsGrid(grid, i, j + 1);
    dfsGrid(grid, i, j - 1);
}

int numIslands(vector<vector<char>> grid) {
    int ans = 0;
    for (int i = 0; i < (int)grid.size(); i++)
        for (int j = 0; j < (int)grid[0].size(); j++)
            if (grid[i][j] == '1') {
                ans++;
                dfsGrid(grid, i, j);
            }
    return ans;
}

int main() {
    vector<vector<char>> grid = {{'1','1','0'},{'0','1','0'},{'1','0','1'}};
    cout << numIslands(grid) << endl; // 3
    return 0;
}
