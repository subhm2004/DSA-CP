// ════════════════════════════════════════════════════════════════════════════
// KUHN'S ALGORITHM — Bipartite Maximum Matching
// ────────────────────────────────────────────────────────────────────────────
// Bipartite graph: left set (jobs) → right set (workers).
// Har left node ke liye DFS se augmenting path dhundho.
// Agar match mil jaye to matching++ — greedy se maximum matching milti hai.
// Time: O(V * E) | Space: O(V + E)
// ════════════════════════════════════════════════════════════════════════════

#include <bits/stdc++.h>
using namespace std;

struct Kuhn {
    int nLeft, nRight;
    vector<vector<int>> adj;  // adj[u] = right-side neighbors of left node u
    vector<int> matchR;      // matchR[v] = kaunsa left node v se matched hai (-1 = free)
    vector<int> vis;         // is DFS round mein v visit hua ya nahi
    int timer = 0;           // har naye left node ke liye timer++ — vis reset trick

    // Step 1: nLeft left-side nodes (jobs), nRight right-side nodes (workers) store karo.
    // Step 2: adj resize nL — har left node ki neighbor list empty.
    // Step 3: matchR size nR, sab -1 — koi right node abhi matched nahi.
    // Step 4: vis array right nodes ke liye — DFS round mein duplicate visit avoid.
    Kuhn(int nL, int nR) : nLeft(nL), nRight(nR), adj(nL), matchR(nR, -1), vis(nR) {}

    // Step 1: Left node u ki adjacency list mein right node v push karo.
    // Step 2: Bipartite edge u->v — u left set, v right set.
    // Step 3: Multiple edges ek left node se multiple right nodes connect kar sakte hain.
    void addEdge(int u, int v) { adj[u].push_back(v); }

    // Step 1: u ke saare right neighbors v iterate karo.
    // Step 2: vis[v] == timer ho to skip — is DFS round mein already try ho chuka.
    // Step 3: vis[v] = timer mark karo — visited set trick (memset avoid).
    // Step 4: v free (matchR[v]==-1) YA v ka current match dfs(matchR[v]) se re-match ho sakta hai.
    // Step 5: Match mila to matchR[v] = u set karo, true return — augmenting path mil gaya.
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (vis[v] == timer) continue; // is round mein already try kiya
            vis[v] = timer;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u; // v ko u se match karo (purana match shift ho sakta hai)
                return true;
            }
        }
        return false;
    }

    // Step 1: matching = 0 initialize karo.
    // Step 2: Har left node u = 0..nLeft-1 ke liye timer++ (vis reset without memset).
    // Step 3: dfs(u) true de to matching++ — ek naya match add hua.
    // Step 4: Greedy order mein har left node try — maximum matching build hoti hai.
    // Step 5: Final matching count return karo.
    int maxMatching() {
        int matching = 0;
        for (int u = 0; u < nLeft; u++) {
            timer++; // naya timer = vis array reset without memset
            if (dfs(u)) matching++;
        }
        return matching;
    }

    // Step 1: Empty pairs vector banao.
    // Step 2: Har right node v = 0..nRight-1 check karo — matchR[v] != -1 matlab matched hai.
    // Step 3: Matched ho to {matchR[v], v} pair push karo — left-right matching pair.
    // Step 4: Saari matched pairs return karo — final assignment dikhao.
    vector<pair<int, int>> getPairs() {
        vector<pair<int, int>> pairs;
        for (int v = 0; v < nRight; v++)
            if (matchR[v] != -1)
                pairs.push_back({matchR[v], v});
        return pairs;
    }
};

int main() {
    // Jobs (0..2) -> Workers (0..3)
    Kuhn km(3, 4);
    km.addEdge(0, 0);
    km.addEdge(0, 1);
    km.addEdge(1, 1);
    km.addEdge(1, 2);
    km.addEdge(2, 2);
    km.addEdge(2, 3);

    cout << "Max matching = " << km.maxMatching() << endl;
    for (auto [u, v] : km.getPairs())
        cout << "Job " << u << " -> Worker " << v << endl;
    return 0;
}
