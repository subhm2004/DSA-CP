// ════════════════════════════════════════════════════════════════════════════
// BFS PATTERNS — Level Order, Multi-Source, Graph, 0-1, Bidirectional, State
// ────────────────────────────────────────────────────────────────────────────
// Competitive programming ke common BFS templates ek jagah
// Har pattern ke saath LeetCode problems aur Hinglish explanation
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

// PATTERN 1: Simple Level Order BFS
/*
Ek source se start, level by level explore karo.
Har level = source se ek step door.
1. LC 2059 - Minimum Operations to Convert Number
   "Given nums array, start value, and goal. In one operation you can
   add, subtract, or XOR any element of nums with current value.
   Return minimum operations to reach goal, or -1 if impossible."

2. LC 127 - Word Ladder
   "Given beginWord, endWord, wordList. Change one letter at a time,
   each intermediate word must be in wordList.
   Return minimum transformations to reach endWord."

3. LC 1091 - Shortest Path in Binary Matrix
   "Given n×n binary grid, return length of shortest clear path
   from top-left to bottom-right (8 directions allowed).
   Return -1 if no such path."

4. LC 752 - Open the Lock
   "Lock has 4 wheels (0-9). Given deadends and target.
   Each move turns one wheel one slot.
   Return minimum turns to reach target, or -1 if impossible."

5. LC 773 - Sliding Puzzle
   "Given 2×3 board puzzle. Move 0 to adjacent position each step.
   Return minimum moves to reach [[1,2,3],[4,5,0]], or -1."
*/
// ╔══════════════════════════════════════════════╗
// ║     PATTERN 1: SIMPLE LEVEL ORDER BFS        ║
// ║  LC 2059, LC 127, LC 1091, LC 752, LC 773    ║
// ╚══════════════════════════════════════════════╝

// ── levelOrderBFS_Grid: grid pe source se target tak shortest steps (BFS levels) ──
// Step 1: Start cell ko queue mein daalo aur visited mark karo, time = 0 se shuru.
// Step 2: Har level ke liye q.size() snapshot lo — ye sab same distance ke cells hain.
// Step 3: Level ke har cell se 4 directions explore karo — valid, unblocked, unvisited neighbors queue mein.
// Step 4: Target cell is level mein mile to time return karo (shortest steps mil gaye).
// Step 5: Queue khali ho jaye bina target ke to -1 return — koi path nahi hai.
int levelOrderBFS_Grid(vector<vector<int>> &grid,
                       pair<int, int> start,
                       pair<int, int> target)
{

    int rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;

    int time = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y] = q.front();
            q.pop();

            if (make_pair(x, y) == target)
                return time;

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < cols &&
                    grid[nx][ny] != -1 &&
                    !visited[nx][ny])
                {

                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        time++;
    }
    return -1;
}

// ── minimumOperations: start se goal tak min ops (+/- nums[i] ya XOR) ────────
// Step 1: Start value ko queue mein daalo, visited[start] = true (range 0-1000).
// Step 2: Har BFS level par q.size() cells process karo — har level = ek operation.
// Step 3: Har value se nums[i] ke saath +, -, XOR teen transitions try karo.
// Step 4: Goal mile to steps return karo; valid unvisited values queue mein push karo.
// Step 5: Queue khatam ho jaye to -1 — goal unreachable hai.
int minimumOperations(vector<int> &nums, int start, int goal)
{

    vector<bool> visited(1001, false);
    queue<int> q;
    q.push(start);
    if (start >= 0 && start <= 1000)
        visited[start] = true;

    int steps = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            int val = q.front();
            q.pop();

            if (val == goal)
                return steps;

            for (int num : nums)
            {
                vector<int> nexts = {val + num, val - num, val ^ num};

                for (int nxt : nexts)
                {
                    if (nxt == goal)
                        return steps + 1;

                    if (nxt >= 0 && nxt <= 1000 && !visited[nxt])
                    {
                        visited[nxt] = true;
                        q.push(nxt);
                    }
                }
            }
        }
        steps++;
    }
    return -1;
}

// ─── LC 752: Open The Lock ───
// Step 1: Deadends set banao; "0000" dead hai to -1; target "0000" hai to 0 return.
// Step 2: Queue mein "0000" push karo, visited set mein add karo.
// Step 3: Har BFS level = ek turn; har state se 4 wheels × 2 directions (+1/-1) naye states banao.
// Step 4: Deadend ya visited states skip karo; target mile to steps return karo.
// Step 5: Queue khatam ho jaye to -1 — lock kholna impossible hai.
int openLock(vector<string> &deadends, string target)
{

    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000"))
        return -1;
    if (target == "0000")
        return 0;

    unordered_set<string> visited;
    queue<string> q;
    q.push("0000");
    visited.insert("0000");

    int steps = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            string curr = q.front();
            q.pop();

            if (curr == target)
                return steps;

            // Har wheel ko +1 ya -1 ghuma sakte ho
            for (int i = 0; i < 4; i++)
            {
                for (int delta : {1, -1})
                {
                    string next = curr;
                    next[i] = (char)(((curr[i] - '0') + delta + 10) % 10 + '0');

                    if (!dead.count(next) && !visited.count(next))
                    {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        steps++;
    }
    return -1;
}

// ─── LC 127: Word Ladder ───
// Step 1: endWord wordSet mein hona chahiye warna 0 return; beginWord queue mein push.
// Step 2: Har BFS level = ek letter change; steps = 1 se start (beginWord count hota hai).
// Step 3: Har word ke har position par 'a' se 'z' tak substitute karke naye words try karo.
// Step 4: Valid wordSet word ko queue mein push aur wordSet se erase (dobara visit avoid).
// Step 5: endWord mile to steps return; queue khatam ho to 0 — koi ladder nahi.
int ladderLength(string beginWord, string endWord,
                 vector<string> &wordList)
{

    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord))
        return 0;

    queue<string> q;
    q.push(beginWord);

    int steps = 1;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            string word = q.front();
            q.pop();

            if (word == endWord)
                return steps;

            for (int i = 0; i < (int)word.size(); i++)
            {
                char original = word[i];

                for (char c = 'a'; c <= 'z'; c++)
                {
                    word[i] = c;
                    if (wordSet.count(word))
                    {
                        q.push(word);
                        wordSet.erase(word);
                    }
                }
                word[i] = original;
            }
        }
        steps++;
    }
    return 0;
}

// ---

// # PATTERN 2: Multi-Source BFS

// ## Theory
// ```
// Multiple sources ek saath queue mein daalo.
// Sab simultaneously spread karte hain.
// "Simultaneously" word = Multi-Source sign!
// ```

// ## Problems:
// ```
// 1. LC 994 - Rotten Oranges
//    "Grid has 0(empty), 1(fresh), 2(rotten) oranges.
//    Every minute, rotten orange rots adjacent fresh oranges.
//    Return minimum minutes until no fresh orange remains, or -1."

// 2. LC 542 - 01 Matrix
//    "Given binary matrix, return matrix where each cell = distance
//    to nearest 0. All 0s spread simultaneously."

// 3. LC 286 - Walls and Gates (Premium)
//    "Grid has -1(wall), 0(gate), INF(empty room).
//    Fill each empty room with distance to nearest gate."

// 4. LC 1765 - Map of Highest Peak
//    "isWater grid given. Height of water cell = 0.
//    Adjacent cells differ by at most 1.
//    Maximize the highest peak — return height matrix."

// 5. LC 1162 - As Far from Land as Possible
//    "Grid of 0(water) and 1(land).
//    Find water cell with maximum distance to nearest land cell.
//    Return that maximum distance."

// ╔══════════════════════════════════════════════╗
// ║       PATTERN 2: MULTI-SOURCE BFS            ║
// ║  LC 994, LC 542, LC 286, LC 1765, LC 1162    ║
// ╚══════════════════════════════════════════════╝

// ─── LC 994: Rotten Oranges ───
// Step 1: Grid scan karke saare rotten (2) queue mein push karo, fresh (1) count karo.
// Step 2: Koi fresh nahi to 0 return — already done.
// Step 3: Har minute (outer loop) mein q.size() rotten oranges process karo.
// Step 4: Adjacent fresh ko 2 mein badlo, queue mein daalo, freshCount-- karo.
// Step 5: End mein freshCount==0 ? time-1 : -1 return karo.
int orangesRotting(vector<vector<int>> &grid)
{

    int rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    queue<pair<int, int>> q;
    int freshCount = 0;

    // Saare rotten oranges ek saath push karo
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == 2)
                q.push({i, j});
            if (grid[i][j] == 1)
                freshCount++;
        }
    }

    if (freshCount == 0)
        return 0;

    int time = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < cols &&
                    grid[nx][ny] == 1)
                {

                    grid[nx][ny] = 2;
                    freshCount--;
                    q.push({nx, ny});
                }
            }
        }
        time++;
    }
    return freshCount == 0 ? time - 1 : -1;
}

// ─── LC 542: 01 Matrix ───
// Step 1: Saare 0 cells ko queue mein push karo aur dist[i][j] = 0 set karo (multi-source).
// Step 2: Baaki cells ka dist = -1 rakho (abhi visit nahi hua).
// Step 3: BFS level-by-level chalao — har cell se 4 neighbors explore karo.
// Step 4: Unvisited neighbor ka dist = parent dist + 1 set karo aur queue mein push.
// Step 5: Poori grid fill hone ke baad dist matrix return — har cell nearest 0 se kitna door.
vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{

    int rows = mat.size(), cols = mat[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;

    // Saare 0s sources hain
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j] == 0)
            {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < cols &&
                    dist[nx][ny] == -1)
                {

                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return dist;
}

// ─── LC 1765: Map of Highest Peak ───
// Step 1: Saare water cells (isWater[i][j]==1) ko queue mein push karo, height = 0.
// Step 2: Land cells ka height = -1 rakho (abhi assign nahi hua).
// Step 3: Multi-source BFS se har land cell tak water se distance spread karo.
// Step 4: Har neighbor ka height = current height + 1 (adjacent cells max 1 differ).
// Step 5: Final height matrix return — ye maximum possible peak heights hain.
vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
{

    int rows = isWater.size(), cols = isWater[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<vector<int>> height(rows, vector<int>(cols, -1));
    queue<pair<int, int>> q;

    // Saare water cells sources hain (height=0)
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (isWater[i][j] == 1)
            {
                height[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < cols &&
                    height[nx][ny] == -1)
                {

                    height[nx][ny] = height[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    return height;
}

// # PATTERN 3: BFS on Graph

// ## Theory
// ```
// Grid nahi, nodes + edges wala graph.
// Adjacency list use hoti hai.
// Shortest path in unweighted graph.
// ```

// ## Problems:
// ```
// 1. LC 207 - Course Schedule
//    "numCourses courses, prerequisites pairs given.
//    Return true if you can finish all courses
//    (detect cycle in directed graph)."

// 2. LC 210 - Course Schedule II
//    "Same as above but return the order to take courses.
//    Return empty array if impossible (cycle exists)."

// 3. LC 433 - Minimum Genetic Mutation
//    "Gene string mutates one character at a time.
//    Each mutation must be in bank.
//    Return minimum mutations from start to end, or -1."

// 4. LC 1311 - Get Watched Videos by Friends
//    "Social network. Find all videos watched by friends
//    exactly 'level' connections away. Return sorted by frequency."

// 5. LC 863 - All Nodes Distance K in Binary Tree
//    "Binary tree, target node, integer k.
//    Return all nodes at distance k from target."
// ╔══════════════════════════════════════════════╗
// ║       PATTERN 3: BFS ON GRAPH                ║
// ║   LC 207, LC 210, LC 433, LC 863             ║
// ╚══════════════════════════════════════════════╝

// ─── GRAPH BFS TEMPLATE ───
// Step 1: dist array -1 se initialize karo; dist[src] = 0 aur src queue mein push.
// Step 2: Har level par q.size() nodes process karo — unweighted graph mein level = distance.
// Step 3: Har node ke neighbors check karo — agar dist[neighbor] == -1 (unvisited).
// Step 4: dist[neighbor] = dist[node] + 1 set karo aur queue mein push karo.
// Step 5: BFS khatam hone par dist array return — src se har node ka shortest hop count.
vector<int> bfsGraph(vector<vector<int>> &adj, int src, int n)
{

    vector<int> dist(n, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node])
            {
                if (dist[neighbor] == -1)
                {
                    dist[neighbor] = dist[node] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
    return dist;
}

// ─── LC 207: Course Schedule ───
// Step 1: Prerequisites se adjacency list aur indegree array banao (pre[1] -> pre[0] edge).
// Step 2: Indegree 0 wale courses (koi prerequisite nahi) queue mein push karo.
// Step 3: Kahn's algo: front course pop karo, completed++, uske neighbors ka indegree-- karo.
// Step 4: Indegree 0 hone par neighbor ko queue mein push karo.
// Step 5: completed == numCourses → no cycle, sab finish ho sakte hain; warna cycle hai.
bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
{

    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto &pre : prerequisites)
    {
        adj[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    // Indegree 0 = no prerequisites = start karo inse
    for (int i = 0; i < numCourses; i++)
        if (indegree[i] == 0)
            q.push(i);

    int completed = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            int course = q.front();
            q.pop();
            completed++;

            for (int next : adj[course])
            {
                indegree[next]--;
                if (indegree[next] == 0)
                    q.push(next);
            }
        }
    }
    return completed == numCourses; // sab complete = no cycle
}

// ─── LC 210: Course Schedule II ───
// Step 1: Graph aur indegree array build karo — har prerequisite edge se indegree[dest]++.
// Step 2: Indegree 0 courses queue mein daalo — ye pehle le sakte ho.
// Step 3: Kahn's BFS: pop karo, order mein push karo, neighbors ka indegree kam karo.
// Step 4: Indegree 0 hone par turant queue mein push — valid topological order ban raha hai.
// Step 5: order.size() == numCourses ? order return : empty {} — cycle hone par empty.
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{

    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto &pre : prerequisites)
    {
        adj[pre[1]].push_back(pre[0]);
        indegree[pre[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++)
        if (indegree[i] == 0)
            q.push(i);

    vector<int> order;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            int course = q.front();
            q.pop();
            order.push_back(course);

            for (int next : adj[course])
            {
                if (--indegree[next] == 0)
                    q.push(next);
            }
        }
    }
    return (int)order.size() == numCourses ? order : vector<int>{};
}

// ─── LC 433: Minimum Genetic Mutation ───
// Step 1: endGene bank mein hona chahiye warna -1; startGene queue mein, bank se erase.
// Step 2: Har BFS level = ek mutation; har gene se har position par A/C/G/T try karo.
// Step 3: Mutated gene bank mein ho to queue mein push aur bank se erase (revisit avoid).
// Step 4: endGene mile to mutations count return karo.
// Step 5: Queue khatam ho to -1 — mutation path nahi mila.
int minMutation(string startGene, string endGene,
                vector<string> &bank)
{

    unordered_set<string> bankSet(bank.begin(), bank.end());
    if (!bankSet.count(endGene))
        return -1;

    queue<string> q;
    q.push(startGene);
    bankSet.erase(startGene);

    int mutations = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            string gene = q.front();
            q.pop();

            if (gene == endGene)
                return mutations;

            for (char c : {'A', 'C', 'G', 'T'})
            {
                for (int i = 0; i < (int)gene.size(); i++)
                {
                    char orig = gene[i];
                    gene[i] = c;

                    if (bankSet.count(gene))
                    {
                        q.push(gene);
                        bankSet.erase(gene);
                    }
                    gene[i] = orig;
                }
            }
        }
        mutations++;
    }
    return -1;
}
// --- (pattern 3 khatam)

    // # PATTERN 4: 0-1 BFS (Deque)

    // ## Theory
    // ```
    // Edge weights sirf 0 ya 1 — Deque use karo.
    // Weight 0 → front mein daalo (same cost)
    // Weight 1 → back mein daalo (cost + 1)

    // ## Problems:
    // ```
    // 1. LC 2290 - Minimum Number of Obstacles to Remove
    //    "m×n grid. 0=empty, 1=obstacle. Remove minimum obstacles
    //    to create path from (0,0) to (m-1,n-1)."

    // 2. LC 1368 - Minimum Cost to Make Grid
    //    "Grid has arrows. Moving in arrow direction = free (cost 0).
    //    Changing arrow direction = cost 1.
    //    Find min cost path top-left to bottom-right."

    // 3. LC 2092 - Find All People With Secret (modified)
    //    "Some edges free, some cost 1. Minimum cost to spread info."

    // 4. LC 1976 - Number of Ways to Arrive at Destination
    //    "Weighted graph. Count paths with minimum time. (0-1 variant)"

    // ╔══════════════════════════════════════════════╗
    // ║         PATTERN 4: 0-1 BFS (DEQUE)          ║
    // ║      LC 2290, LC 1368                        ║
    // ╚══════════════════════════════════════════════╝

    // ─── LC 2290: Minimum Obstacles to Remove ───
    // Step 1: (0,0) se 0-1 BFS shuru — dist[0][0]=0, deque front mein push.
    // Step 2: Deque se cell nikalo; har neighbor ke liye edge weight = grid[nx][ny] (0 ya 1).
    // Step 3: Better dist mile to update karo — weight 0 → push_front, weight 1 → push_back.
    // Step 4: 0-1 BFS guarantee: pehle sab 0-cost edges process, phir 1-cost.
    // Step 5: dist[rows-1][cols-1] return — minimum obstacles hataane padenge.
    int minimumObstacles(vector<vector<int>> &grid)
{

    int rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    deque<pair<int, int>> dq;

    dist[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty())
    {
        auto [x, y] = dq.front();
        dq.pop_front();

        for (auto [dx, dy] : directions)
        {
            int nx = x + dx, ny = y + dy;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
            {
                int w = grid[nx][ny]; // 0=free, 1=obstacle

                if (dist[x][y] + w < dist[nx][ny])
                {
                    dist[nx][ny] = dist[x][y] + w;

                    if (w == 0)
                        dq.push_front({nx, ny});
                    else
                        dq.push_back({nx, ny});
                }
            }
        }
    }
    return dist[rows - 1][cols - 1];
}

// ─── LC 1368: Minimum Cost to Make Grid ───
// Step 1: (0,0) se 0-1 BFS — dist[0][0]=0, deque front mein.
// Step 2: 4 directions try karo; arrow match (grid[x][y]==d+1) → cost 0, warna cost 1.
// Step 3: dist improve ho to update; cost 0 neighbor → push_front, cost 1 → push_back.
// Step 4: Deque se Dijkstra jaisa behavior — chhoti cost wale cells pehle process.
// Step 5: dist[rows-1][cols-1] return — minimum direction changes needed.
int minCost(vector<vector<int>> &grid)
{

    int rows = grid.size(), cols = grid[0].size();
    // 1=right, 2=left, 3=down, 4=up
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    deque<pair<int, int>> dq;

    dist[0][0] = 0;
    dq.push_front({0, 0});

    while (!dq.empty())
    {
        auto [x, y] = dq.front();
        dq.pop_front();

        for (int d = 0; d < 4; d++)
        {
            int nx = x + directions[d].first;
            int ny = y + directions[d].second;

            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                continue;

            // Arrow direction match = cost 0, else cost 1
            int w = (grid[x][y] == d + 1) ? 0 : 1;

            if (dist[x][y] + w < dist[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + w;

                if (w == 0)
                    dq.push_front({nx, ny});
                else
                    dq.push_back({nx, ny});
            }
        }
    }
    return dist[rows - 1][cols - 1];
}

// ---

// # PATTERN 5: Bidirectional BFS

// ## Theory
// ```
// Start aur End dono se simultaneously BFS karo.
// Jab dono sets milein — answer found!
// Large graphs mein normal BFS se 4x faster.
// ```

// ## Problems:
// ```
// 1. LC 127 - Word Ladder (Optimized)
//    "Same as before but optimize using bidirectional BFS
//    when graph is very large."

// 2. LC 126 - Word Ladder II
//    "Return ALL shortest transformation sequences
//    from beginWord to endWord."

// 3. LC 433 - Minimum Genetic Mutation (Optimized)
//    "Start + end gene both known — bidirectional faster."

// ╔══════════════════════════════════════════════╗
// ║      PATTERN 5: BIDIRECTIONAL BFS            ║
// ║         LC 127 (optimized), LC 433           ║
// ╚══════════════════════════════════════════════╝

// ─── LC 127: Word Ladder (Bidirectional) ───
// Step 1: frontSet = {beginWord}, backSet = {endWord} — dono taraf se BFS simultaneously.
// Step 2: Hamesha chhote set ko expand karo (swap) — search space kam rehta hai.
// Step 3: Har word ke har position par a-z substitute karke nextLevel banao.
// Step 4: Agar naya word doosre set mein hai → intersection mil gaya → steps+1 return.
// Step 5: frontSet = nextLevel, steps++ — jab tak dono sets meet na karein ya empty ho jayein.
int ladderLengthBiDir(string beginWord, string endWord,
                      vector<string> &wordList)
{

    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord))
        return 0;

    unordered_set<string> frontSet = {beginWord};
    unordered_set<string> backSet = {endWord};
    unordered_set<string> visited;

    int steps = 1;

    while (!frontSet.empty() && !backSet.empty())
    {

        // Hamesha chota set expand karo
        if (frontSet.size() > backSet.size())
            swap(frontSet, backSet);

        unordered_set<string> nextLevel;

        for (string word : frontSet)
        {
            for (int i = 0; i < (int)word.size(); i++)
            {
                char orig = word[i];

                for (char c = 'a'; c <= 'z'; c++)
                {
                    word[i] = c;

                    // Dono sets mein mila = answer!
                    if (backSet.count(word))
                        return steps + 1;

                    if (wordSet.count(word) && !visited.count(word))
                    {
                        nextLevel.insert(word);
                        visited.insert(word);
                    }
                }
                word[i] = orig;
            }
        }
        frontSet = nextLevel;
        steps++;
    }
    return 0;
}

// ---

// # PATTERN 6: BFS with State

// ## Theory
// ```
// Position ke saath EXTRA STATE bhi track karo.
// visited[x][y][state] — 3D ya usse bhi zyada visited array.
// Jab sirf position track karna kaafi na ho.
// ```

// ## Problems:
// ```
// 1. LC 1293 - Shortest Path in Grid with Obstacles Elimination
//    "m×n grid, 0=empty, 1=obstacle. You can eliminate k obstacles.
//    Return minimum steps from top-left to bottom-right, or -1."

// 2. LC 864 - Shortest Path to Get All Keys
//    "Grid with keys (a-f) and locks (A-F).
//    Collect all keys with minimum steps.
//    State = position + keys collected (bitmask)."

// 3. LC 1263 - Minimum Moves to Move Box to Target
//    "Grid with box, player, target. Push box to target.
//    State = {box_pos, player_pos}. Minimum pushes."

// 4. LC 2192 - All Ancestors of Node in DAG
//    "State = current node + path tracking."

// ╔══════════════════════════════════════════════╗
// ║        PATTERN 6: BFS WITH STATE             ║
// ║      LC 1293, LC 864                         ║
// ╚══════════════════════════════════════════════╝

// ─── LC 1293: Shortest Path with Obstacle Elimination ───
// Step 1: State = (row, col, k_remaining) — 3D visited array use karo.
// Step 2: (0,0,k) se BFS shuru; har level = ek step.
// Step 3: Har move par newRem = rem - grid[nx][ny] — obstacle pe 1 kam, empty pe 0 kam.
// Step 4: newRem >= 0 aur visited[nx][ny][newRem] false ho to push karo.
// Step 5: (rows-1, cols-1) pahunche to steps return; queue khatam ho to -1.
int shortestPath(vector<vector<int>> &grid, int k)
{

    int rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // State: {row, col, k_remaining}
    vector<vector<vector<bool>>> visited(
        rows, vector<vector<bool>>(cols, vector<bool>(k + 1, false)));

    // Queue: {row, col, obstacles_remaining}
    queue<tuple<int, int, int>> q;
    q.push({0, 0, k});
    visited[0][0][k] = true;

    int steps = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y, rem] = q.front();
            q.pop();

            if (x == rows - 1 && y == cols - 1)
                return steps;

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                    continue;

                int newRem = rem - grid[nx][ny];

                if (newRem >= 0 && !visited[nx][ny][newRem])
                {
                    visited[nx][ny][newRem] = true;
                    q.push({nx, ny, newRem});
                }
            }
        }
        steps++;
    }
    return -1;
}

// ─── LC 864: Shortest Path to Get All Keys ───
// Step 1: '@' position aur total lowercase keys count karo; allKeys = (1<<totalKeys)-1 bitmask.
// Step 2: State = (row, col, keys_bitmask) — visited 3D array [x][y][keys].
// Step 3: BFS level-by-level; lowercase key mile to bitmask mein set bit ON karo.
// Step 4: Uppercase lock pe check — corresponding key bit ON hona chahiye warna skip.
// Step 5: keys == allKeys mile to steps return — saari keys collect ho gayi!
int shortestPathAllKeys(vector<string> &grid)
{

    int rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int startX, startY, totalKeys = 0;

    // Start position aur total keys dhundho
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] == '@')
            {
                startX = i;
                startY = j;
            }
            if (islower(grid[i][j]))
                totalKeys++;
        }
    }

    int allKeys = (1 << totalKeys) - 1; // bitmask: sab keys collected

    // State: {row, col, keys_bitmask}
    // visited[x][y][keys]
    vector<vector<vector<bool>>> visited(
        rows, vector<vector<bool>>(cols,
                                   vector<bool>(allKeys + 1, false)));

    queue<tuple<int, int, int>> q;
    q.push({startX, startY, 0});
    visited[startX][startY][0] = true;

    int steps = 0;

    while (!q.empty())
    {
        int s = q.size();

        while (s--)
        {
            auto [x, y, keys] = q.front();
            q.pop();

            if (keys == allKeys)
                return steps; // sab keys mil gayi!

            for (auto [dx, dy] : directions)
            {
                int nx = x + dx, ny = y + dy;

                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                    continue;

                char cell = grid[nx][ny];
                if (cell == '#')
                    continue; // wall

                // Lock hai aur key nahi hai
                if (isupper(cell) && !(keys & (1 << (cell - 'A'))))
                    continue;

                int newKeys = keys;
                if (islower(cell))
                    newKeys |= (1 << (cell - 'a')); // key collect karo

                if (!visited[nx][ny][newKeys])
                {
                    visited[nx][ny][newKeys] = true;
                    q.push({nx, ny, newKeys});
                }
            }
        }
        steps++;
    }
    return -1;
}

// ---

// # Master Decision Card
// ```
// ╔══════════════════════════════════════════════════════════╗
// ║              BFS PATTERN SELECTOR                        ║
// ╠══════════════════════════════════════════════════════════╣
// ║ "minimum steps/path" + 1 source  → Pattern 1 Level Order║
// ║ "simultaneously" / multiple src  → Pattern 2 Multi-Src  ║
// ║ nodes + edges graph given        → Pattern 3 Graph BFS   ║
// ║ weights only 0 or 1              → Pattern 4 0-1 BFS     ║
// ║ start+end both known, large graph→ Pattern 5 Bidir BFS   ║
// ║ position + extra info to track   → Pattern 6 State BFS   ║
// ╚══════════════════════════════════════════════════════════╝
// int main() {
//     return 0;
// }