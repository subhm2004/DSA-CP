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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 695 — Max Area of Island
// ────────────────────────────────────────────────────────────────────────────
// Problem: Binary grid me 1 = land, 0 = water. Sabse bada connected
//          island (1s ka group) ka area (cell count) dhundho.
//
// Approach: DFS Flood Fill + Max Tracking
//   - Har unvisited 1 cell se DFS — connected 1s count karo
//   - Visit karte waqt 1→0 mark karo (visited)
//   - Har component ka size = 1 + sum of 4 neighbor DFS returns
//   - Global max update karo
//
// Complexity: Time O(m×n)  |  Space O(m×n) recursion stack
// ════════════════════════════════════════════════════════════════════════════

// ── dfs: (i,j) se connected land ka area (cell count) return ──
//   1) Out of bounds ya water (0) → 0 return
//   2) grid[i][j] = 0 — visited mark (dobara count na ho)
//   3) Current cell = 1 + 4 directions ka dfs sum
//   4) Poora connected component ka total area return
int dfs(vector<vector<int>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) return 0;  // water ya boundary
    grid[i][j] = 0;  // sink land — visited + avoid double count
    return 1 + dfs(grid, i + 1, j) + dfs(grid, i - 1, j)
             + dfs(grid, i, j + 1) + dfs(grid, i, j - 1);  // 1 + all 4 neighbors
}

// ── maxAreaOfIsland: grid me sabse bada island area ──
//   1) best = 0 initialize
//   2) Har cell scan — grid[i][j]==1 mila to naya island
//   3) dfs se us island ka area nikalo
//   4) best = max(best, area) update
//   5) Sab cells scan hone ke baad best return
int maxAreaOfIsland(vector<vector<int>> grid) {
    int best = 0;
    for (int i = 0; i < (int)grid.size(); i++)
        for (int j = 0; j < (int)grid[0].size(); j++)
            if (grid[i][j] == 1)
                best = max(best, dfs(grid, i, j));  // har naye island ka area try karo
    return best;
}

int main() {
    vector<vector<int>> grid = {{0,0,1,0,0},{0,0,0,0,0},{0,1,1,0,0}};
    cout << maxAreaOfIsland(grid) << endl; // 3
    return 0;
}
