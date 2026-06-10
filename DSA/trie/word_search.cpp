/*
 * ============================================================================
 * TOPIC    : Trie + Backtracking — Word Search
 * FILE     : word_search.cpp
 * PROBLEM  : Find if word exists in character grid
 * LEETCODE : 79 — Word Search
 * APPROACH : DFS from each cell; mark visited with '#'
 * COMPLEX  : Time: O(m*n*4^L)  |  Space: O(L)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// WORD SEARCH — Grid mein word exist karta hai ya nahi?
// ────────────────────────────────────────────────────────────────────────────
// Har cell se DFS/backtracking — 4 directions explore karo
// Visited mark: cell ko '#' se replace, backtrack pe restore
// Word match ho gaya (idx == len) -> true
// Har (i,j) se start try karo — koi bhi path mila to answer YES
// ════════════════════════════════════════════════════════════════════════════

// ── dfs: (i,j) se word[idx..] match kar sakte hain? ─────────────────────────
//   1) idx == word.size() -> poora word match, true return
//   2) bounds / char mismatch -> false
//   3) current cell '#' mark karo (visited)
//   4) 4 directions mein recurse — koi bhi true ho to found
//   5) backtrack: cell restore karo, found return
bool dfs(vector<vector<char>> &board, string &word, int idx, int i, int j) {
    if (idx == (int)word.size()) return true;
    int n = board.size(), m = board[0].size();
    if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != word[idx]) return false;

    char save = board[i][j];
    board[i][j] = '#';
    int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
    bool found = false;
    for (int d = 0; d < 4; d++)
        if (dfs(board, word, idx + 1, i + dx[d], j + dy[d])) {
            found = true;
            break;
        }
    board[i][j] = save;
    return found;
}

// ── exist: board mein word kahin bhi mil sakta hai? ─────────────────────────
//   1) har cell (i,j) pe loop
//   2) dfs(board, word, 0, i, j) se path dhundho
//   3) koi bhi cell se true -> word exist
//   4) sab fail -> false
bool exist(vector<vector<char>> &board, string word) {
    for (int i = 0; i < (int)board.size(); i++)
        for (int j = 0; j < (int)board[0].size(); j++)
            if (dfs(board, word, 0, i, j)) return true;
    return false;
}

int main() {
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    cout << (exist(board, "ABCCED") ? "YES" : "NO") << endl;
    return 0;
}
