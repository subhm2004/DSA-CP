// ════════════════════════════════════════════════════════════════════════════
// ADJACENCY LIST → ADJACENCY MATRIX CONVERSION
// ────────────────────────────────────────────────────────────────────────────
// unordered_map-based adj list se V x V matrix banao.
// No edge = INT_MAX (INF), edge hai to weight store karo.
// ════════════════════════════════════════════════════════════════════════════

// #include <iostream>
// #include <vector>
// #include <climits> // for INF
// using namespace std;
//
// vector<vector<int>> adjacencyListToMatrix(int V, const vector<vector<pair<int, int>>> &adjList)
// {
//     vector<vector<int>> adjMatrix(V, vector<int>(V, INT_MAX));
//     for (int i = 0; i < V; i++)
//     {
//         for (const auto &neighbor : adjList[i])
//         {
//             int j = neighbor.first;
//             int weight = neighbor.second;
//             adjMatrix[i][j] = weight;
//         }
//     }
//     return adjMatrix;
// }
//
// void printMatrix(const vector<vector<int>> &matrix)
// {
//     for (const auto &row : matrix)
//     {
//         for (int val : row)
//         {
//             if (val == INT_MAX)
//             {
//                 cout << "INF ";
//             }
//             else
//             {
//                 cout << val << " ";
//             }
//         }
//         cout << endl;
//     }
// }
//
// int main()
// {
//     int V = 5;
//     vector<vector<pair<int, int>>> adjList(V);
//     adjList[0].push_back({1, 10});
//     adjList[0].push_back({4, 20});
//     adjList[1].push_back({2, 5});
//     adjList[2].push_back({3, 2});
//     adjList[3].push_back({4, 1});
//     adjList[4].push_back({1, 7});
//     vector<vector<int>> adjMatrix = adjacencyListToMatrix(V, adjList);
//     cout << "Adjacency Matrix:" << endl;
//     printMatrix(adjMatrix);
//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <climits>
using namespace std;

// Step 1: V×V matrix banao sab cells INT_MAX (INF = no edge) se fill karo.
// Step 2: adjList ki har entry (u -> neighbors) iterate karo.
// Step 3: Har neighbor (v, weight) ke liye adjMatrix[u][v] = weight set karo.
// Step 4: List representation sparse hai — matrix dense ban jati hai Floyd/Dijkstra ke liye.
// Step 5: Converted matrix return karo.
vector<vector<int>> adjListToMatrix(int V, const unordered_map<int, list<pair<int, int>>> &adjList)
{
    vector<vector<int>> adjMatrix(V, vector<int>(V, INT_MAX));

    for (const auto &node : adjList)
    {
        int u = node.first;
        for (const auto &neighbor : node.second)
        {
            int v = neighbor.first;
            int weight = neighbor.second;
            adjMatrix[u][v] = weight;
        }
    }

    return adjMatrix;
}

// Step 1: Matrix ki har row iterate karo.
// Step 2: Har cell check karo — INT_MAX ho to "INF" print karo (no edge).
// Step 3: Warna actual weight value print karo.
// Step 4: Har row ke baad newline — readable adjacency matrix output.
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << (val == INT_MAX ? "INF " : to_string(val) + " ");
        }
        cout << endl;
    }
}

int main()
{
    int V = 5;

    unordered_map<int, list<pair<int, int>>> adjList;
    adjList[0] = {{1, 10}, {4, 20}};
    adjList[1] = {{2, 5}};
    adjList[2] = {{3, 2}};
    adjList[3] = {{4, 1}};
    adjList[4] = {{1, 7}};

    vector<vector<int>> adjMatrix = adjListToMatrix(V, adjList);

    cout << "Adjacency Matrix:" << endl;
    printMatrix(adjMatrix);

    return 0;
}
