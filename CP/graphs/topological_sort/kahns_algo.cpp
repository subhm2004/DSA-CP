#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// KAHN'S ALGORITHM — Topological Sort (BFS / indegree based)
// ────────────────────────────────────────────────────────────────────────────
// DAG (Directed Acyclic Graph) me linear order jahan har edge u->v ke liye
// u, v se pehle aata hai.
//
// Idea:
//   indegree[v] = kitne edges v ki taraf aa rahe hain
//   indegree 0 wale nodes queue me daalo -> pop -> neighbors ka indegree--
//   jab kisi ka indegree 0 ho jaye queue me daalo
//
// Agar final ans.size() < n -> cycle hai (valid topo sort impossible)
// Time: O(V + E)  |  Space: O(V)
// ════════════════════════════════════════════════════════════════════════════

template <typename T>
class Graph
{
public:
    unordered_map<T, list<T>> adjList;

    // Step 1: adjList[u] mein v push karo — directed edge u -> v (topo sort ke liye).
    // Step 2: direction == 0 ho to undirected — v se u bhi add (topo sort sirf DAG pe valid).
    // Step 3: Har edge se indegree[v] badhega topoSortBfs mein.
    void addEdge(T u, T v, bool direction)
    {
        // direction = 1 -> directed (topo sort ke liye)
        // direction = 0 -> undirected
        adjList[u].push_back(v);
        if (direction == 0)
        {
            adjList[v].push_back(u);
        }
    }

    // Step 1: adjList ki har node entry iterate karo.
    // Step 2: Node aur uske neighbors comma-separated print karo.
    // Step 3: DAG structure verify karne ke liye debugging output.
    void printAdjacencyList()
    {
        for (auto node : adjList)
        {
            cout << node.first << " -> ";
            for (auto neighbor : node.second)
            {
                cout << neighbor << ", ";
            }
            cout << endl;
        }
    }

    // Step 1: Har edge u->v se indegree[v]++ karo — kitne edges node ki taraf aa rahe hain.
    // Step 2: Indegree 0 wale nodes queue mein push karo — inke koi prerequisites nahi.
    // Step 3: Front node pop karo, ans mein push karo — ye topo order mein aayega.
    // Step 4: Us node ke har neighbor ka indegree-- karo; 0 ho jaye to queue mein push.
    // Step 5: ans.size() < n matlab cycle hai — valid topological sort impossible.
    void topoSortBfs(int n, vector<int> &ans)
    {
        queue<int> q;
        unordered_map<int, int> indegree;

        // Har edge se destination ka indegree badhao
        for (auto i : adjList)
        {
            int src = i.first;
            for (auto nbr : i.second)
            {
                indegree[nbr]++;
            }
        }

        // Shuru me jinke paas koi incoming edge nahi — woh pehle process honge
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        // BFS: front node topo order me, uske neighbors ka indegree kam karo
        while (!q.empty())
        {
            int fNode = q.front();
            q.pop();
            ans.push_back(fNode);

            for (auto nbr : adjList[fNode])
            {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                {
                    q.push(nbr); // ab is node ke saare prerequisites done
                }
            }
        }
    }
};

int main()
{
    Graph<int> g;
    int n = 8;

    // ---- DAG demo: 0,1,2 -> ... -> 7 ----
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 5, 1);
    g.addEdge(3, 6, 1);
    g.addEdge(4, 6, 1);
    g.addEdge(5, 7, 1);
    g.addEdge(6, 7, 1);

    g.printAdjacencyList();
    cout << endl;

    vector<int> ans;
    g.topoSortBfs(n, ans);

    // ans.size() == n matlab saare nodes process hue — no cycle
    if (ans.size() == n)
    {
        cout << "It is a valid topological sort." << endl;
    }
    else
    {
        cout << "Cycle present or invalid topological sort." << endl;
    }

    cout << "Topological Sort using BFS: ";
    for (auto i : ans)
    {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}
