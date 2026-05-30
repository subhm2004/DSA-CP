//#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    // Adjacency list representation
    unordered_map<int, vector<int>> adjList;

public:
    // Function to add an edge between two nodes
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since the graph is undirected
    }

    // Function to display the graph
    void displayGraph() {
        for (auto node : adjList) {
            cout << "Node " << node.first << " is connected to: ";
            for (int neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Function to calculate the sum of degrees of all nodes
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

    // Add edges to the graph
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    // Display the graph
    g.displayGraph();

    // Display the sum of degrees
    cout << "Sum of degrees = " << g.sumOfDegrees() << endl;

    return 0;
}
