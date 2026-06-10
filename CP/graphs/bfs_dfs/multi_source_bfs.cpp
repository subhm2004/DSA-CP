// ════════════════════════════════════════════════════════════════════════════
// MULTI-SOURCE BFS
// ────────────────────────────────────────────────────────────────────────────
// Ek se zyada source nodes se ek saath BFS chalao — sab simultaneously spread
// hote hain. Har cell tak shortest distance = sabse nazdeek source se kitna door.
// LC 994 (Rotten Oranges), LC 542 (01 Matrix), LC 286 (Walls and Gates)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

// ── multiSourceBFS: saare sources se parallel BFS, grid mein distance bharte hain ──
// Step 1: Saare source cells ko ek saath queue mein push karo (grid[x][y] pehle se 0 hai).
// Step 2: Jab tak queue empty na ho — front cell nikalo aur 4 directions explore karo.
// Step 3: Agar neighbor valid hai aur grid[newX][newY] == -1 (unvisited) to distance = parent + 1 set karo.
// Step 4: Naya cell queue mein daalo — FIFO se pehle sources ke paas wale cells pehle process hote hain.
// Step 5: End mein har cell mein nearest source se shortest distance store hota hai (multi-source magic).
void multiSourceBFS(vector<vector<int>> &grid, vector<pair<int, int>> &sources)
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int, int>> q;

    // Push all sources into the queue and mark them as visited
    for (auto [x, y] : sources)
    {
        q.push({x, y});
    }

    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // Up, Down, Left, Right

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        cout << "Processing: (" << x << ", " << y << "), Distance: " << grid[x][y] << "\n";

        for (auto dir : directions)
        {
            int newX = x + dir.first, newY = y + dir.second;

            // Check valid move — sirf unvisited cells (-1) mein distance propagate karo
            if (newX >= 0 && newX < n && newY >= 0 && newY < m && grid[newX][newY] == -1)
            {
                grid[newX][newY] = grid[x][y] + 1; // parent se ek step aage
                q.push({newX, newY});
                cout << "Updating: (" << newX << ", " << newY << ") to Distance: " << grid[newX][newY] << "\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "Enter grid dimensions (n m): ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m, -1)); // Initialize grid with -1

    int k;
    cout << "Enter number of sources: ";
    cin >> k;

    vector<pair<int, int>> sources;
    cout << "Enter source coordinates (x y):\n";
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x < 0 || x >= n || y < 0 || y >= m)
        {
            cout << "Invalid source position: (" << x << ", " << y << ")\n";
            continue;
        }
        sources.push_back({x, y});
        grid[x][y] = 0; // Mark sources with 0 distance
    }

    multiSourceBFS(grid, sources);

    cout << "Final Grid:\n";
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            cout << cell << " ";
        }
        cout << "\n";
    }

    return 0;
}
