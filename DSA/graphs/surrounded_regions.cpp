/*
 * ============================================================================
 * TOPIC    : Graphs — Surrounded Regions
 * FILE     : surrounded_regions.cpp
 * PROBLEM  : Capture 'O' regions not connected to border
 * LEETCODE : 130 — Surrounded Regions
 * APPROACH : Flood fill from border 'O's; flip inner remaining 'O' to 'X'
 * COMPLEX  : Time: O(m*n)  |  Space: O(m*n)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 130 — Surrounded Regions
// ────────────────────────────────────────────────────────────────────────────
// Problem: Board me 'O' regions jo border se connected NAHI hain unhe 'X'
//          se capture karo. Border-touching 'O' safe rehne chahiye.
//
// Approach: Reverse Thinking — Border Flood Fill
//   - Border ke saare 'O' aur unke connected 'O' ko 'S' (safe) mark karo
//   - Jo 'O' bacha = surrounded → 'X' banao
//   - 'S' wapas 'O' me convert karo
//
// Complexity: Time O(m×n)  |  Space O(m×n) recursion stack
// ════════════════════════════════════════════════════════════════════════════

// ── markSafe: border-connected 'O' ko 'S' mark karo (DFS) ──
//   1) Invalid bounds ya non-'O' cell → return
//   2) 'O' ko 'S' se replace — ye safe hai, capture nahi hoga
//   3) 4 directions me recursively markSafe — poora safe region mark
//   4) DFS se border se connected saare 'O' mil jayenge
void markSafe(vector<vector<char>> &board, int i, int j) {
    int n = board.size(), m = board[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != 'O') return;
    board[i][j] = 'S';  // safe mark — border se reachable
    markSafe(board, i + 1, j);
    markSafe(board, i - 1, j);
    markSafe(board, i, j + 1);
    markSafe(board, i, j - 1);
}

// ── solve: surrounded 'O' regions capture karo ──
//   1) Empty board ho to return
//   2) 4 borders scan — har border 'O' se markSafe DFS
//   3) Interior scan: 'O' → 'X' (surrounded), 'S' → 'O' (restore safe)
//   4) In-place modification — extra space nahi
void solve(vector<vector<char>> &board) {
    if (board.empty()) return;
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++) {
        markSafe(board, i, 0);      // left border
        markSafe(board, i, m - 1);  // right border
    }
    for (int j = 0; j < m; j++) {
        markSafe(board, 0, j);      // top border
        markSafe(board, n - 1, j);  // bottom border
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';      // surrounded — capture
            else if (board[i][j] == 'S') board[i][j] = 'O';   // safe wapas restore
        }
}

int main() {
    vector<vector<char>> board = {
        {'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};
    solve(board);
    cout << board[1][1] << board[3][1] << endl; // XX
    return 0;
}
