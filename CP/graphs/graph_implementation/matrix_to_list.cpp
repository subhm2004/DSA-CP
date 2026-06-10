// ════════════════════════════════════════════════════════════════════════════
// ADJACENCY MATRIX → ADJACENCY LIST CONVERSION
// ────────────────────────────────────────────────────────────────────────────
// Matrix me adjMatrix[i][j] = edge weight (INT_MAX = no edge)
// List me har node i ke liye list of {neighbor, weight} pairs
//
// unordered_map use kiya hai taaki sparse graphs me memory bache
// ════════════════════════════════════════════════════════════════════════════

// #include <iostream>
// #include <vector>
// #include <climits> // for INF
// using namespace std;
//
// vector<vector<pair<int, int>>> matrixToAdjacencyList(int V, const vector<vector<int>> &adjMatrix)
// {
//     vector<vector<pair<int, int>>> adjList(V);
//     for (int i = 0; i < V; i++)
//     {
//         for (int j = 0; j < V; j++)
//         {
//             if (adjMatrix[i][j] != INT_MAX)
//             {
//                 adjList[i].push_back({j, adjMatrix[i][j]});
//             }
//         }
//     }
//     return adjList;
// }
//
// void printAdjList(const vector<vector<pair<int, int>>> &adjList)
// {
//     for (int i = 0; i < adjList.size(); i++)
//     {
//         cout << i << ": ";
//         for (const auto &neighbor : adjList[i])
//         {
//             cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
//         }
//         cout << endl;
//     }
// }
//
// int main()
// {
//     int V = 5;
//     vector<vector<int>> adjMatrix = {
//         {INT_MAX, 10, INT_MAX, INT_MAX, 20},
//         {INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
//         {INT_MAX, INT_MAX, INT_MAX, 2, INT_MAX},
//         {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1},
//         {INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};
//     vector<vector<pair<int, int>>> adjList = matrixToAdjacencyList(V, adjMatrix);
//     cout << "Adjacency List:" << endl;
//     printAdjList(adjList);
//     return 0;
// }
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <climits>
using namespace std;

// Step 1: Empty unordered_map adjList banao — sparse storage ke liye.
// Step 2: Har row i aur column j par check karo — adjMatrix[i][j] != INT_MAX matlab edge hai.
// Step 3: Edge mile to adjList[i].push_back({j, weight}) karo.
// Step 4: Sirf existing edges store hongi — memory bachti hai sparse graphs mein.
// Step 5: Converted adjacency list return karo.
unordered_map<int, list<pair<int, int>>> matrixToAdjList(int V, const vector<vector<int>> &adjMatrix)
{
    unordered_map<int, list<pair<int, int>>> adjList;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adjMatrix[i][j] != INT_MAX)
            {
                adjList[i].push_back({j, adjMatrix[i][j]});
            }
        }
    }
    return adjList;
}

// Step 1: adjList ki har node entry iterate karo.
// Step 2: Node number print karo, colon lagao.
// Step 3: Har neighbor ke liye (neighbor, weight) pair print karo.
// Step 4: Har node ke baad newline — conversion verify karne ke liye.
void printAdjList(const unordered_map<int, list<pair<int, int>>> &adjList)
{
    for (const auto &node : adjList)
    {
        cout << node.first << ": ";
        for (const auto &neighbor : node.second)
        {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}

int main()
{
    int V = 5;

    vector<vector<int>> adjMatrix = {
        {INT_MAX, 10, INT_MAX, INT_MAX, 20},
        {INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 2, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1},
        {INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};

    unordered_map<int, list<pair<int, int>>> adjList = matrixToAdjList(V, adjMatrix);

    cout << "Adjacency List:\n";
    printAdjList(adjList);

    return 0;
}
