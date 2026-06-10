/*
 * NOTE: Yeh file Hierholzer's Algorithm hai (Eulerian Path/Circuit in graph)
 * Euler Tour on TREE alag topic hai — dekh Euler_tour_on_trees.cpp
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <stack>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HIERHOLZER'S ALGORITHM — Eulerian Path / Circuit
// ────────────────────────────────────────────────────────────────────────────
// Eulerian Circuit: har edge exactly ek baar, start=end (sab vertices even degree)
// Eulerian Path: har edge exactly ek baar, start!=end (exactly 2 odd degree)
//
// Algorithm: stack use karke edges "khate" jao, jab koi edge nahi bachi
// wapas path me node daal do. Reverse print = euler path/circuit.
// ════════════════════════════════════════════════════════════════════════════

class Graph
{
    int V;
    unordered_map<int, list<int>> adjList;

public:
    // ── Graph: V vertices wala empty adjacency list banao ───────────────────
    //   1) V store karo — kitne nodes hain graph me
    //   2) adjList abhi khali hai, addEdge se edges add hongi
    Graph(int V)
    {
        this->V = V;
    }

    // ── addEdge: directed edge u -> v ───────────────────────────────────────
    //   1) adjList[u] me v push karo
    //   2) directed hai — reverse edge automatically nahi banti
    //   3) multiple edges bhi allowed (list me duplicate ho sakte hain)
    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    // ── findEulerianPathOrCircuit: Hierholzer se path/circuit nikalo ────────
    //   1) tempAdj me edges copy karo (original graph safe rahe)
    //   2) koi bhi non-empty node se stack pe shuru karo
    //   3) jab tak unvisited edge hai -> next push; warna node path me, pop
    //   4) path reverse print karo — har edge exactly ek baar use hoti hai
    void findEulerianPathOrCircuit()
    {
        unordered_map<int, list<int>> tempAdj = adjList;

        stack<int> stk;
        vector<int> path;
        int startNode = 0;

        // koi bhi node jisme edge ho, wahan se shuru karo
        unordered_map<int, list<int>>::iterator it;
        for (it = adjList.begin(); it != adjList.end(); ++it)
        {
            if (!it->second.empty())
            {
                startNode = it->first;
                break;
            }
        }

        stk.push(startNode);

        while (!stk.empty())
        {
            int node = stk.top();

            if (!tempAdj[node].empty())
            {
                int next = tempAdj[node].front();
                tempAdj[node].pop_front();  // edge "kha" li — dobara use nahi hogi
                stk.push(next);
            }
            else
            {
                path.push_back(node);       // ab is node se aage koi edge nahi
                stk.pop();
            }
        }

        cout << "Eulerian Path/Circuit: ";
        for (int i = path.size() - 1; i >= 0; i--)  // reverse = sahi euler order
            cout << path[i] << " ";
        cout << endl;
    }
};

int main()
{
    int V = 6;
    Graph g(V);

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}};

    for (size_t i = 0; i < edges.size(); i++)
    {
        g.addEdge(edges[i].first, edges[i].second);
    }

    g.findEulerianPathOrCircuit();

    return 0;
}
