/*
 * ============================================================================
 * TOPIC    : Graphs — Hierholzer's Algorithm (Directed Graph)
 * FILE     : Hierholzers_algorithm.cpp
 * PROBLEM  : Find Eulerian path/circuit in a directed graph (use every edge once)
 * APPROACH : Stack-based Hierholzer + in/out degree existence check
 * COMPLEX  : Time: O(V + E)  |  Space: O(V + E)
 * ============================================================================
 *
 * Eulerian Path  : har directed edge exactly ek baar traverse
 * Eulerian Circuit: path jahan start == end
 *
 * Directed conditions:
 *   Circuit → sab nodes: inDeg == outDeg, weakly connected
 *   Path    → exactly 1 start (out = in+1), 1 end (in = out+1), baaki equal
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// HIERHOLZER'S ALGORITHM — DIRECTED EULERIAN PATH / CIRCUIT
// ────────────────────────────────────────────────────────────────────────────
// Step 1: Degree check — path/circuit possible hai ya nahi
// Step 2: Weak connectivity — direction hata ke sab edge-nodes connected?
// Step 3: Hierholzer — stack se edges traverse, dead-end pe path me push
// Step 4: Path reverse — stack se ulta aata hai, reverse karke sahi order
// COMPLEX: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

struct DirectedGraph
{
    int n;
    vector<vector<int>> adj;
    vector<int> inDeg, outDeg;

    DirectedGraph(int n) : n(n), adj(n), inDeg(n, 0), outDeg(n, 0) {}

    // ── addEdge: directed edge u → v ──
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        outDeg[u]++;
        inDeg[v]++;
    }

    // ── weaklyConnected: direction ignore karke sab active nodes ek component? ──
    //   Eulerian path ke liye graph "weakly connected" hona zaroori hai
    bool weaklyConnected() const
    {
        vector<vector<int>> und(n);
        for (int u = 0; u < n; u++)
            for (int v : adj[u])
            {
                und[u].push_back(v);
                und[v].push_back(u);
            }

        int start = -1;
        for (int i = 0; i < n; i++)
            if (inDeg[i] > 0 || outDeg[i] > 0)
            {
                start = i;
                break;
            }
        if (start == -1)
            return true; // koi edge nahi

        vector<bool> vis(n, false);
        queue<int> q;
        q.push(start);
        vis[start] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : und[u])
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
        }

        for (int i = 0; i < n; i++)
            if ((inDeg[i] > 0 || outDeg[i] > 0) && !vis[i])
                return false;
        return true;
    }

    // ── eulerType: 0 = none, 1 = path, 2 = circuit ──
    int eulerType() const
    {
        if (!weaklyConnected())
            return 0;

        int starts = 0, ends = 0;
        for (int i = 0; i < n; i++)
        {
            int diff = outDeg[i] - inDeg[i];
            if (diff == 1)
                starts++;
            else if (diff == -1)
                ends++;
            else if (diff != 0)
                return 0;
        }

        if (starts == 0 && ends == 0)
            return 2; // circuit
        if (starts == 1 && ends == 1)
            return 1; // path
        return 0;
    }

    // ── findStart: path me out-in=1 wala node, circuit me koi active node ──
    int findStart() const
    {
        for (int i = 0; i < n; i++)
            if (outDeg[i] - inDeg[i] == 1)
                return i;
        for (int i = 0; i < n; i++)
            if (outDeg[i] > 0 || inDeg[i] > 0)
                return i;
        return 0;
    }

    // ── hierholzer: actual Eulerian trail construct karo ──
    //   1) adj ki copy lo — edges remove karte jao
    //   2) stack pe start push
    //   3) outgoing edge hai → next pe jao, edge hata do
    //   4) nahi hai → node path me daalo (backtrack)
    //   5) reverse → sahi traversal order
    vector<int> hierholzer() const
    {
        vector<vector<int>> temp = adj;
        vector<int> st, path;
        st.push_back(findStart());

        while (!st.empty())
        {
            int u = st.back();
            if (temp[u].empty())
            {
                path.push_back(u);
                st.pop_back();
            }
            else
            {
                int v = temp[u].back();
                temp[u].pop_back();
                st.push_back(v);
            }
        }

        reverse(path.begin(), path.end());
        return path;
    }

    // ── getEulerianTrail: check + path return (empty = impossible) ──
    vector<int> getEulerianTrail() const
    {
        if (eulerType() == 0)
            return {};
        return hierholzer();
    }
};

static void printTrail(const string &label, const vector<int> &path)
{
    cout << label;
    for (int i = 0; i < (int)path.size(); i++)
    {
        cout << path[i];
        if (i + 1 < (int)path.size())
            cout << " -> ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Test 1: Eulerian Circuit (directed) ===\n";
    // 0 → 1 → 2 → 0,  1 → 3 → 4 → 1
    DirectedGraph g1(5);
    for (auto [u, v] : vector<pair<int, int>>{{0, 1}, {1, 2}, {2, 0}, {1, 3}, {3, 4}, {4, 1}})
        g1.addEdge(u, v);

    cout << "Type: " << (g1.eulerType() == 2 ? "Circuit" : g1.eulerType() == 1 ? "Path"
                                                                          : "None")
         << "\n";
    printTrail("Trail: ", g1.getEulerianTrail());

    cout << "\n=== Test 2: Eulerian Path (not circuit) ===\n";
    // 0 → 1 → 2 → 3  (simple path, 3 is end)
    DirectedGraph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);

    cout << "Type: " << (g2.eulerType() == 1 ? "Path" : "Other") << "\n";
    printTrail("Trail: ", g2.getEulerianTrail());

    cout << "\n=== Test 3: No Eulerian trail ===\n";
    // triangle — no node with balanced degrees for circuit, wrong for path too in directed?
    // 0→1, 1→2, 2→0: actually circuit exists. Use 0→1, 0→2, 1→2 — not eulerian
    DirectedGraph g3(3);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 2);

    cout << "Type: " << (g3.eulerType() == 0 ? "None (expected)" : "Unexpected") << "\n";
    cout << "Trail empty? " << (g3.getEulerianTrail().empty() ? "Yes" : "No") << "\n";

    return 0;
}

/*
 * ════════════════════════════════════════════════════════════════════════════
 * HIERHOLZER — DIRECTED GRAPH GUIDE (Hinglish)
 * ════════════════════════════════════════════════════════════════════════════
 *
 * EULERIAN PATH/CIRCUIT KYA HAI?
 *   Directed graph ki har edge exactly EK baar use karo — trail ban jaye.
 *   Circuit = start aur end same node.
 *
 * PEHLE CHECK (degree rules):
 *   Circuit: har node pe inDeg == outDeg
 *   Path:    ek node outDeg = inDeg + 1 (START)
 *            ek node inDeg  = outDeg + 1 (END)
 *            baaki sab equal
 *   + graph WEAKLY CONNECTED hona chahiye (direction ignore karke connected)
 *
 * HIERHOLZER STEPS:
 *   1) Start = path case me (out-in==1), warna koi bhi node
 *   2) Stack = [start]
 *   3) Jab adj[u] non-empty → kisi neighbor pe jao, edge DELETE karo
 *   4) Jab adj[u] empty → u ko answer me daalo, stack pop
 *   5) Answer reverse karo
 *
 * DIRECTED vs UNDIRECTED:
 *   Directed: sirf u→v edge remove (adj[u] se)
 *   Undirected: dono taraf se remove — file: printing_euler_path_undirected.cpp
 *
 * KAB USE KARO?
 *   ✅ Route planning jahan har road ek baar
 *   ✅ String reconstruction (De Bruijn sequence)
 *   ✅ CP "use all edges once" problems
 *
 * COMMON MISTAKES:
 *   ❌ Sirf outgoing DFS se connectivity check — weak connectivity BFS use karo
 *   ❌ Path reverse bhool jana
 *   ❌ Multi-edge graph me adj copy zaroori — original mutate mat karo
 *
 * RELATED FILES:
 *   euler_path_directed_indegree.cpp  → sirf degree CHECK (path print nahi)
 *   printing_euler_path_undirected.cpp → undirected Hierholzer
 *   directed_eulerian_path.cpp         → purana combined version
 *
 * ════════════════════════════════════════════════════════════════════════════
 */
