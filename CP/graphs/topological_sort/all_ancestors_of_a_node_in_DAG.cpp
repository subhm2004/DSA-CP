#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

class Solution
{
public:
    // DFS function to find ancestors of a node
    void DFS(int ancestor, unordered_map<int, list<int>> &adjList, int currNode, vector<vector<int>> &result)
    {
        // Traverse all neighbors of the current node
        for (int nbr : adjList[currNode])
        {
            // Check if ancestor is already added for this neighbor to avoid duplicates
            if (result[nbr].empty() || result[nbr].back() != ancestor)
            {
                result[nbr].push_back(ancestor);
                DFS(ancestor, adjList, nbr, result); // Recurse for the neighbor
            }
        }
    }

    // Function to find ancestors for each node
    vector<vector<int>> getAncestors(int n, vector<vector<int>> &edges)
    {
        // Initialize result as a 2D vector to store ancestors of each node
        vector<vector<int>> result(n);

        // Create adjListacency list for the graph
        unordered_map<int, list<int>> adjList;

        // Build the adjListacency list from the edges
        for (const vector<int> &vec : edges)
        {
            int u = vec[0];
            int v = vec[1];

            adjList[u].push_back(v); // u --> v
        }

        // For each node, find its ancestors
        for (int i = 0; i < n; i++)
        {
            DFS(i, adjList, i, result); // Call DFS for each node to find ancestors
        }

        return result; // Return the ancestors for each node
    }
};

int main()
{
    Solution sol;

    // Example input
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 0}};
    int n = 4; // Number of nodes

    // Get ancestors for each node
    vector<vector<int>> result = sol.getAncestors(n, edges);

    // Print the result
    for (int i = 0; i < n; i++)
    {
        cout << "Ancestors of node " << i << ": ";
        for (int ancestor : result[i])
        {
            cout << ancestor << " ";
        }
        cout << endl;
    }

    return 0;
}
