// #include <iostream>
// #include <vector>
// #include <climits> // for INF
// using namespace std;

// vector<vector<pair<int, int>>> matrixToAdjacencyList(int V, const vector<vector<int>> &adjMatrix)
// {
//     // Initialize an adjacency list
//     vector<vector<pair<int, int>>> adjList(V);

//     // Traverse the adjacency matrix and convert it to adjacency list
//     for (int i = 0; i < V; i++)
//     {
//         for (int j = 0; j < V; j++)
//         {
//             // If there is an edge (i.e., weight is not INF), add it to the adjacency list
//             if (adjMatrix[i][j] != INT_MAX)
//             {
//                 adjList[i].push_back({j, adjMatrix[i][j]});
//             }
//         }
//     }

//     return adjList;
// }

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

// int main()
// {
//     int V = 5; // Number of vertices

//     // Adjacency matrix representation of a graph
//     vector<vector<int>> adjMatrix = {
//         {INT_MAX, 10, INT_MAX, INT_MAX, 20},
//         {INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
//         {INT_MAX, INT_MAX, INT_MAX, 2, INT_MAX},
//         {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1},
//         {INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};

//     // Convert adjacency matrix to adjacency list
//     vector<vector<pair<int, int>>> adjList = matrixToAdjacencyList(V, adjMatrix);

//     // Print the adjacency list
//     cout << "Adjacency List:" << endl;
//     printAdjList(adjList);

//     return 0;
// }
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <climits> // For INT_MAX
using namespace std;

// Function: Adjacency matrix ko unordered_map-based adjacency list me convert karega
unordered_map<int, list<pair<int, int>>> matrixToAdjList(int V, const vector<vector<int>> &adjMatrix)
{
    unordered_map<int, list<pair<int, int>>> adjList;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adjMatrix[i][j] != INT_MAX)
            {                                               // Agar edge exist karti hai
                adjList[i].push_back({j, adjMatrix[i][j]}); // {neighbor, weight} add karo
            }
        }
    }
    return adjList;
}

// Function: Adjacency list print karega
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
    int V = 5; // Number of vertices

    // Adjacency matrix representation of a graph
    vector<vector<int>> adjMatrix = {
        {INT_MAX, 10, INT_MAX, INT_MAX, 20},
        {INT_MAX, INT_MAX, 5, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 2, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1},
        {INT_MAX, 7, INT_MAX, INT_MAX, INT_MAX}};

    // Convert adjacency matrix to unordered_map-based adjacency list
    unordered_map<int, list<pair<int, int>>> adjList = matrixToAdjList(V, adjMatrix);

    // Print adjacency list
    cout << "Adjacency List:\n";
    printAdjList(adjList);

    return 0;
}
