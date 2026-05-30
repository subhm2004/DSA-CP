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

void markSafe(vector<vector<char>> &board, int i, int j) {
    int n = board.size(), m = board[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != 'O') return;
    board[i][j] = 'S';
    markSafe(board, i + 1, j);
    markSafe(board, i - 1, j);
    markSafe(board, i, j + 1);
    markSafe(board, i, j - 1);
}

void solve(vector<vector<char>> &board) {
    if (board.empty()) return;
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++) {
        markSafe(board, i, 0);
        markSafe(board, i, m - 1);
    }
    for (int j = 0; j < m; j++) {
        markSafe(board, 0, j);
        markSafe(board, n - 1, j);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'S') board[i][j] = 'O';
        }
}

int main() {
    vector<vector<char>> board = {
        {'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};
    solve(board);
    cout << board[1][1] << board[3][1] << endl; // XX
    return 0;
}
