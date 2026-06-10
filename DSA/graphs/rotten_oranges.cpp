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

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 994 — Rotting Oranges
// ────────────────────────────────────────────────────────────────────────────
// Problem: Grid me 0=empty, 1=fresh, 2=rotten. Har minute rotten orange
//          4-directional neighbors ko infect karta hai. Sab fresh kitne
//          minutes me rotten honge? Impossible ho to -1.
//
// Approach: Multi-source BFS (level-order)
//   - Saare rotten (2) cells ko ek saath queue me daalo — time 0
//   - Har level = 1 minute; 4 neighbors me fresh (1) ko 2 banao
//   - fresh counter track karo — 0 ho gaya to minutes return
//   - Queue khatam par fresh bacha → -1
//
// Complexity: Time O(rows×cols)  |  Space O(rows×cols) for queue
// ════════════════════════════════════════════════════════════════════════════

// ── orangesRotting: minimum minutes until all oranges rotten ──
//   1) Grid scan — rotten cells queue me, fresh count karo
//   2) BFS level-by-level: har level ek minute represent karta hai
//   3) Har rotten cell se 4-direction me fresh neighbor infect karo
//   4) fresh-- karo jab bhi 1→2 conversion ho
//   5) fresh==0 → minutes return, warna -1 (kuch fresh unreachable)
int orangesRotting(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 2) q.push({i, j});  // multi-source: sab rotten ek saath
            else if (grid[i][j] == 1) fresh++;

    int minutes = 0;
    int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    while (!q.empty() && fresh > 0) {
        int sz = q.size();  // current level size — ek minute ka batch
        minutes++;
        while (sz--) {
            auto [i, j] = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == 1) {
                    grid[ni][nj] = 2;  // infect fresh neighbor
                    fresh--;
                    q.push({ni, nj});  // naya rotten — next level me spread karega
                }
            }
        }
    }
    return fresh == 0 ? minutes : -1;  // sab rotten ho gaye ya impossible
}

int main() {
    vector<vector<int>> grid = {{2,1,1},{1,1,0},{0,1,1}};
    cout << orangesRotting(grid) << endl; // 4
    return 0;
}
