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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 1254 — Number of Closed Islands
// ────────────────────────────────────────────────────────────────────────────
// Problem: Grid me 1=land, 0=water. Closed island = land jo border touch
//          NAHI karta aur poori tarah 0s se surrounded ho. Count karo.
//
// Approach: Two-Phase Flood Fill
//   - Phase 1: Border pe land (1) hai to eraseLand — ye closed nahi ho sakta
//   - Phase 2: Bachi hui land = closed islands — count + erase
//   - eraseLand DFS se connected land ko 0 mark karta hai
//
// Complexity: Time O(m×n)  |  Space O(m×n) recursion stack
// ════════════════════════════════════════════════════════════════════════════

// ── eraseLand: (i,j) se connected land ko water (0) me convert ──
//   1) Bounds check + water (0) → return
//   2) grid[i][j] = 0 — land erase (visited mark)
//   3) 4 directions me recursively eraseLand — poora island wipe
//   4) Border-connected ya closed — dono cases me land hat jati hai
void eraseLand(vector<vector<int>> &grid, int i, int j) {
    int n = grid.size(), m = grid[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) return;
    grid[i][j] = 0;  // land → water, visited bhi
    eraseLand(grid, i + 1, j);
    eraseLand(grid, i - 1, j);
    eraseLand(grid, i, j + 1);
    eraseLand(grid, i, j - 1);
}

// ── closedIsland: completely surrounded islands count ──
//   1) Border scan: border land ko eraseLand — ye closed nahi ho sakte
//   2) Interior scan: bachi 1 = closed island → ans++, eraseLand
//   3) Har naye 1 pe naya closed island mila
//   4) Total ans return
int closedIsland(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((i == 0 || j == 0 || i == n - 1 || j == m - 1) && grid[i][j] == 1)
                eraseLand(grid, i, j);  // border-touching land — not closed

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 1) {
                ans++;  // interior land = closed island
                eraseLand(grid, i, j);  // poora island erase — dobara count na ho
            }
    return ans;
}

int main() {
    vector<vector<int>> grid = {{1,1,1},{1,0,1},{1,1,1}};
    cout << closedIsland(grid) << endl; // 1
    return 0;
}
