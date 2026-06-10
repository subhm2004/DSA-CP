#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ALL ANCESTORS OF EACH NODE IN A DAG
// ────────────────────────────────────────────────────────────────────────────
// Directed acyclic graph me har node ke liye saare ancestors (nodes jinse
// koi path us node tak jaata hai) nikalna.
//
// Approach: har node i ko "source ancestor" maan ke DFS — jahan bhi pohoncho,
//           result[nbr] me i add karo (duplicate avoid karne ke liye check).
// Time: O(V * (V+E)) worst case  |  Space: O(V²) result store
// ════════════════════════════════════════════════════════════════════════════

class Solution
{
public:
    // Step 1: currNode ke har neighbor nbr par jao — directed edge currNode -> nbr.
    // Step 2: Duplicate avoid: result[nbr] empty ho YA last entry ancestor na ho tab hi add karo.
    // Step 3: result[nbr].push_back(ancestor) — nbr ke ancestors mein ancestor add hua.
    // Step 4: Recursively DFS(ancestor, adjList, nbr, result) — aage ke descendants tak spread.
    // Step 5: Backtrack implicit hai — har branch independently ancestors collect karti hai.
    void DFS(int ancestor, unordered_map<int, list<int>> &adjList, int currNode, vector<vector<int>> &result)
    {
        for (int nbr : adjList[currNode])
        {
            // Duplicate avoid: agar pehle se last me same ancestor hai to skip
            if (result[nbr].empty() || result[nbr].back() != ancestor)
            {
                result[nbr].push_back(ancestor);
                DFS(ancestor, adjList, nbr, result); // aage ke descendants tak
            }
        }
    }

    // Step 1: Edges se adjacency list banao — directed u -> v edges.
    // Step 2: result vector size n initialize karo — har node ki ancestor list.
    // Step 3: Har node i = 0..n-1 ko source maan ke DFS(i, adjList, i, result) call karo.
    // Step 4: Node i se reachable har node ke ancestors mein i add ho jayega.
    // Step 5: Poori result matrix return — result[j] = saare ancestors of node j.
    vector<vector<int>> getAncestors(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> result(n);

        unordered_map<int, list<int>> adjList;
        for (const vector<int> &vec : edges)
        {
            int u = vec[0];
            int v = vec[1];
            adjList[u].push_back(v); // directed u -> v
        }

        // Har i ko starting point maan ke poori reachable subtree me ancestors mark
        for (int i = 0; i < n; i++)
        {
            DFS(i, adjList, i, result);
        }

        return result;
    }
};

int main()
{
    Solution sol;

    // ---- Demo: 0->1, 0->2, 1->2, 3->0 ----
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 0}};
    int n = 4;

    vector<vector<int>> result = sol.getAncestors(n, edges);

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
