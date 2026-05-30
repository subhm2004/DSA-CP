#include <bits/stdc++.h>
using namespace std;

// Graph representation: node -> list of (neighbor, cost)
unordered_map<int, list<pair<int, int>>> adjList;

// Heuristic: node -> estimated cost to goal
unordered_map<int, int> heuristic;

struct Node
{
    int id, g, f;
    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

int a_star(int start, int goal)
{
    unordered_map<int, int> g_cost;
    for (auto &[node, _] : adjList)
    {
        g_cost[node] = INT_MAX;
    }
    g_cost[start] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0, heuristic[start]});

    while (!pq.empty())
    {
        auto [curr, g, f] = pq.top();
        pq.pop();

        if (curr == goal)
            return g;

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

    return -1; // No path found
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

    // Heuristic values (manually estimated, e.g. for path to node 4)
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
