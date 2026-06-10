// ════════════════════════════════════════════════════════════════════════════
// ROTTEN ORANGES — Multi-Source BFS
// ────────────────────────────────────────────────────────────────────────────
// Grid: 0=empty, 1=fresh, 2=rotten. Har minute adjacent fresh sade hote hain.
// Saare rotten oranges ko ek saath queue mein daalo (multi-source BFS).
// LC 994 - Rotting Oranges
// ════════════════════════════════════════════════════════════════════════════

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // ── bfs: rotten se spread karo level-by-level, har level = 1 minute ─────
    // Step 1: Har outer while iteration ek minute represent karti hai — pehle ++count.
    // Step 2: q.size() snapshot lo — is minute mein jitne rotten hain utne hi process karo.
    // Step 3: Har rotten orange ke 4 neighbors check karo — fresh (1) ko 2 mein badlo aur queue mein daalo.
    // Step 4: Har fresh rotten hone par count_fresh-- karo.
    // Step 5: Loop khatam hone par count-1 return karo (pehla increment extra tha); fresh bache to -1.
    int bfs(vector<vector<int>>& grid, queue<pair<int, int>>& q,
            int& count_fresh) {
        int count = 0;
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int rows = grid.size();
        int cols = grid[0].size();

        while (!q.empty()) {
            ++count; // har outer loop = ek minute
            int size = q.size(); // is minute mein jitne rotten process karne hain

            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (auto [dx, dy] : dirs) {
                    int newX = x + dx, newY = y + dy;

                    // sirf fresh orange (1) ko rot karo
                    if (newX < 0 || newY < 0 || newX >= rows || newY >= cols ||
                        grid[newX][newY] == 0 || grid[newX][newY] == 2) {
                        continue;
                    }

                    grid[newX][newY] = 2; // fresh → rotten
                    q.push({newX, newY});
                    count_fresh--;
                }
            }
        }

        // count-1 kyunki pehla increment extra minute count karta hai
        return count_fresh == 0 ? count - 1 : -1;
    }

    // ── orangesRotting: saare rotten sources dhundho, fresh count karo, BFS chalao ──
    // Step 1: Poori grid scan karo — 2 wale cells queue mein push (multi-source), 1 wale count_fresh++.
    // Step 2: Agar koi fresh nahi bacha to 0 minutes return karo — already sab rotten/empty.
    // Step 3: Queue aur count_fresh ko internal bfs() ko pass karo.
    // Step 4: BFS level-by-level rot spread karega jab tak queue empty na ho.
    // Step 5: Final answer = minutes ya -1 agar kuch fresh bach gaye.
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q;
        int count_fresh = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j}); // multi-source: sab rotten ek saath queue mein
                } else if (grid[i][j] == 1) {
                    count_fresh++;
                }
            }
        }

        if (count_fresh == 0)
            return 0; // koi fresh nahi — 0 minute

        return bfs(grid, q, count_fresh);
    }
};

int main() {
    // Hardcoded values for the grid
    vector<vector<int>> grid = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };

    Solution sol;
    int result = sol.orangesRotting(grid);
    cout << "Minimum minutes to rot all oranges: " << result << endl;

    return 0;
}
