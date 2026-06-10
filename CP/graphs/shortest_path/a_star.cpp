#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// A* (A-STAR) SEARCH — Heuristic-Guided Shortest Path
// ────────────────────────────────────────────────────────────────────────────
// Dijkstra jaisa hai, par ek "guess" (heuristic h) se smart explore karta hai.
// Goal ke paas wale nodes pehle try hote hain — blind search se tez.
//
// Har node ke liye:
//   g = start se is node tak actual cost (jaise Dijkstra me dist)
//   h = is node se goal tak estimated cost (heuristic — admissible hona chahiye)
//   f = g + h  (priority queue me sabse chhota f pehle niklega)
//
// Jab goal pop ho jaye -> shortest path mil gaya (agar heuristic admissible ho).
// Time: O((V+E) log V) worst case  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

// Graph representation: node -> list of (neighbor, cost)
unordered_map<int, list<pair<int, int>>> adjList;

// Heuristic: node -> goal tak estimated cost (manually ya formula se)
unordered_map<int, int> heuristic;

// Node struct — priority queue me f ke basis pe sort hoga (min-heap)
struct Node
{
    int id, g, f;

    // Min-heap ke liye: bada f = kam priority (greater comparator)
    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

// ── a_star: start se goal tak minimum cost path dhundo ───────────────────
// g_cost map me har node ka best-known actual cost rakho.
// PQ se sabse chhota f wala node nikalo; goal mila to return g.
// Neighbors relax karo: agar tentative_g < g_cost[nei] to update + PQ me daalo.
// Koi path nahi mila to -1 return.
int a_star(int start, int goal)
{
    // Step 1: g_cost[] = start se actual cost (shuru me sab INF, start=0)
    unordered_map<int, int> g_cost;
    for (auto &[node, _] : adjList)
    {
        g_cost[node] = INT_MAX;
    }
    g_cost[start] = 0;

    // Step 2: PQ me start daalo — f = g + h (heuristic se guided search)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic[start]});

    // Step 3: sabse chhota f wala node pop karo
    while (!pq.empty())
    {
        auto [curr, g, f] = pq.top();
        pq.pop();

        // Step 4: goal mil gaya — ye shortest path hai (admissible heuristic pe)
        if (curr == goal)
            return g;

        // Step 5: neighbors relax — tentative_g improve ho to g_cost update + PQ push
        for (auto &[nei, cost] : adjList[curr])
        {
            int tentative_g = g + cost;
            if (tentative_g < g_cost[nei])
            {
                g_cost[nei] = tentative_g;
                int h = heuristic[nei];
                pq.push({nei, tentative_g, tentative_g + h});
            }
        }
    }

    return -1; // koi path nahi mila
}

int main()
{
    // Example graph
    /*
        1 --(1)--> 2 --(5)--> 4
         \         \
         (4)        (2)
          \          \
           > 3 --(1)--> 4
    */

    adjList[1] = {{2, 1}, {3, 4}};
    adjList[2] = {{3, 2}, {4, 5}};
    adjList[3] = {{4, 1}};
    adjList[4] = {};

    // Heuristic values — goal (node 4) ke liye estimate; node 4 ka h = 0
    heuristic[1] = 7;
    heuristic[2] = 6;
    heuristic[3] = 2;
    heuristic[4] = 0;

    int start = 1, goal = 4;

    int cost = a_star(start, goal);

    if (cost != -1)
        cout << "Minimum cost from " << start << " to " << goal << " is: " << cost << "\n";
    else
        cout << "No path found\n";

    return 0;
}
