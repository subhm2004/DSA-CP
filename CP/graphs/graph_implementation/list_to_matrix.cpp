// #include <iostream>
// #include <vector>
// #include <climits> // for INF
// using namespace std;

// vector<vector<int>> adjacencyListToMatrix(int V, const vector<vector<pair<int, int>>> &adjList)
// {
//     // Initialize an adjacency matrix with all "no edge" values (e.g., INF)
//     vector<vector<int>> adjMatrix(V, vector<int>(V, INT_MAX));

//     // Traverse the adjacency list and fill the matrix
//     for (int i = 0; i < V; i++)
//     {
//         for (const auto &neighbor : adjList[i])
//         {
//             int j = neighbor.first;       // Neighbor vertex
//             int weight = neighbor.second; // Edge weight
//             adjMatrix[i][j] = weight;     // Set the weight of the edge
//         }
//     }

//     return adjMatrix;
// }

// void printMatrix(const vector<vector<int>> &matrix)
// {
//     for (const auto &row : matrix)
//     {
//         for (int val : row)
//         {
//             // Print INF for no edge or INT_MAX if using that representation
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

// int main()
// {
//     int V = 5; // Number of vertices

//     // Adjacency list representation of a directed weighted graph
//     // Each pair: {neighbor vertex, edge weight}
//     vector<vector<pair<int, int>>> adjList(V);
//     adjList[0].push_back({1, 10}); // Edge from 0 to 1 with weight 10
//     adjList[0].push_back({4, 20}); // Edge from 0 to 4 with weight 20
//     adjList[1].push_back({2, 5});  // Edge from 1 to 2 with weight 5
//     adjList[2].push_back({3, 2});  // Edge from 2 to 3 with weight 2
//     adjList[3].push_back({4, 1});  // Edge from 3 to 4 with weight 1
//     adjList[4].push_back({1, 7});  // Edge from 4 to 1 with weight 7

//     // Convert adjacency list to adjacency matrix
//     vector<vector<int>> adjMatrix = adjacencyListToMatrix(V, adjList);

//     // Print the adjacency matrix
//     cout << "Adjacency Matrix:" << endl;
//     printMatrix(adjMatrix);

//     return 0;
// }
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <climits> // For INT_MAX
using namespace std;

// Function: unordered_map-based adjacency list ko adjacency matrix me convert karega
vector<vector<int>> adjListToMatrix(int V, const unordered_map<int, list<pair<int, int>>> &adjList)
{
    // Initialize adjacency matrix with INF (no edge)
    vector<vector<int>> adjMatrix(V, vector<int>(V, INT_MAX));

    // Traverse adjacency list and update matrix
    for (const auto &node : adjList)
    {
        int u = node.first;
        for (const auto &neighbor : node.second)
        {
            int v = neighbor.first;
            int weight = neighbor.second;
            adjMatrix[u][v] = weight; // Edge weight update karo
        }
    }

    return adjMatrix;
}

// Function: Adjacency matrix print karega
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
    int V = 5; // Number of vertices

    // Unordered_map based adjacency list
    unordered_map<int, list<pair<int, int>>> adjList;
    adjList[0] = {{1, 10}, {4, 20}};
    adjList[1] = {{2, 5}};
    adjList[2] = {{3, 2}};
    adjList[3] = {{4, 1}};
    adjList[4] = {{1, 7}};

    // Convert adjacency list to adjacency matrix
    vector<vector<int>> adjMatrix = adjListToMatrix(V, adjList);

    // Print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    printMatrix(adjMatrix);

    return 0;
}
