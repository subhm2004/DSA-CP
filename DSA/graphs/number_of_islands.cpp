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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 200 — Number of Islands
// ────────────────────────────────────────────────────────────────────────────
// Problem: 2D grid me '1' = land, '0' = water. Kitne alag islands (connected
//          '1' components) hain? 4-directional connectivity.
//
// Approach: DFS Flood Fill + Count
//   - Grid scan karo — '1' mila to ans++ (naya island)
//   - dfsGrid se poora connected component '0' mark karo (sink)
//   - Dobara count nahi hoga kyunki visited = '0'
//
// Complexity: Time O(rows×cols)  |  Space O(rows×cols) recursion stack
// ════════════════════════════════════════════════════════════════════════════

// ── dfsGrid: (i,j) se connected land ko sink karo (DFS) ──
//   1) Bounds check + '1' hona chahiye, warna return
//   2) grid[i][j] = '0' — visited/sunk mark
//   3) 4 directions me recursively dfsGrid — poora island sink
//   4) Ek island ek baar hi process hoga
void dfsGrid(vector<vector<char>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] != '1') return;
    grid[i][j] = '0';  // land sink — visited mark
    dfsGrid(grid, i + 1, j);
    dfsGrid(grid, i - 1, j);
    dfsGrid(grid, i, j + 1);
    dfsGrid(grid, i, j - 1);
}

// ── numIslands: total connected land components count ──
//   1) ans = 0 initialize
//   2) Har cell scan — '1' mila to naya island
//   3) ans++ aur dfsGrid se poora island sink karo
//   4) Sunk cells dobara count nahi honge
//   5) Final ans return
int numIslands(vector<vector<char>> grid) {
    int ans = 0;
    for (int i = 0; i < (int)grid.size(); i++)
        for (int j = 0; j < (int)grid[0].size(); j++)
            if (grid[i][j] == '1') {
                ans++;  // naya island discover
                dfsGrid(grid, i, j);  // poora component mark kar do
            }
    return ans;
}

int main() {
    vector<vector<char>> grid = {{'1','1','0'},{'0','1','0'},{'1','0','1'}};
    cout << numIslands(grid) << endl; // 3
    return 0;
}
