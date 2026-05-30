/*
 * ============================================================================
 * TOPIC    : Graphs — Number of Closed Islands
 * FILE     : number_of_closed_islands.cpp
 * PROBLEM  : Islands of 1s completely surrounded by 0s (not touching border)
 * LEETCODE : 1254 — Number of Closed Islands
 * APPROACH : Skip border-connected land via flood fill; count inner islands
 * COMPLEX  : Time: O(m*n)  |  Space: O(m*n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

void eraseLand(vector<vector<int>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) return;
    grid[i][j] = 0;
    eraseLand(grid, i + 1, j);
    eraseLand(grid, i - 1, j);
    eraseLand(grid, i, j + 1);
    eraseLand(grid, i, j - 1);
}

int closedIsland(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && grid[i][j] == 1)
                eraseLand(grid, i, j);

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1) {
                ans++;
                eraseLand(grid, i, j);
            }
    return ans;
}

int main() {
    vector<vector<int>> grid = {{1,1,1},{1,0,1},{1,1,1}};
    cout << closedIsland(grid) << endl; // 1
    return 0;
}
