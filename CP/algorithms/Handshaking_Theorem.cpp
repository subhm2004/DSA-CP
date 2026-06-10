//#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HANDSHAKING LEMMA — Sum of all degrees = 2 * |E|
// ────────────────────────────────────────────────────────────────────────────
// Har edge do nodes ko connect karti hai -> har edge degree sum me 2 baar count
// Undirected graph me: Σ degree(v) = 2 * number of edges
// Is demo me adjacency list se degrees sum karke verify karte hain
// ════════════════════════════════════════════════════════════════════════════

class Graph {
private:
    unordered_map<int, vector<int>> adjList;

public:
    // ── addEdge: undirected edge u-v add karo ───────────────────────────────
    //   1) u ki list me v, v ki list me u push karo
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // ── displayGraph: adjacency list print karo ───────────────────────────────
    void displayGraph() {
        for (auto node : adjList) {
            cout << "Node " << node.first << " is connected to: ";
            for (int neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // ── sumOfDegrees: saare nodes ke degrees ka sum ───────────────────────────
    //   1) har node ki adjacency list size = us node ka degree
    //   2) sab degrees jodo -> 2 * edges (Handshaking Lemma)
    int sumOfDegrees() {
        int sum = 0;
        for (auto node : adjList) {
            sum += node.second.size();
        }
        return sum;
    }
};

int main() {
    Graph g;

    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    g.displayGraph();

    // sum of degrees = 2 + 3 + 1 + 1 = 7? Actually: deg(1)=2, deg(2)=3, deg(3)=1, deg(4)=2 -> sum=8 = 2*4 edges
    cout << "Sum of degrees = " << g.sumOfDegrees() << endl;

    return 0;
}
