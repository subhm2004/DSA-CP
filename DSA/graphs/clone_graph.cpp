/*
 * ============================================================================
 * TOPIC    : Graphs — Clone Graph
 * FILE     : clone_graph.cpp
 * PROBLEM  : Deep copy undirected graph with random pointers
 * LEETCODE : 133 — Clone Graph
 * APPROACH : DFS/BFS + hash map old node → new node
 * COMPLEX  : Time: O(V+E)  |  Space: O(V)
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEETCODE 133 — Clone Graph
// ────────────────────────────────────────────────────────────────────────────
// Problem: Undirected graph ka deep copy banao — har node aur uske neighbors
//          naye memory me, original pointers reuse nahi karne.
//
// Approach: DFS + unordered_map (old Node* → new Node*)
//   - Har node pe pehle check karo map me already copy hai ya nahi
//   - Nahi hai to naya Node banao, map me store karo
//   - Saare neighbors ke liye recursively dfs call — copy ke neighbors me daalo
//   - Map cycle handle karta hai — same node dobara create nahi hoga
//
// Complexity: Time O(V+E)  |  Space O(V) for map + recursion stack
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int val;
    vector<Node *> neighbors;
    Node(int _val) : val(_val) {}
};

// ── cloneGraph: poora graph deep copy karke return ──
//   1) Null node ho to seedha nullptr return
//   2) unordered_map banao — purane pointer se naye pointer ka mapping
//   3) Lambda dfs: map me hai to cached copy return, warna naya node banao
//   4) Har neighbor ke liye dfs call — copy->neighbors me cloned node push
//   5) Root se dfs start karke cloned graph ka head return karo
Node *cloneGraph(Node *node) {
    if (!node) return nullptr;  // empty graph edge case
    unordered_map<Node *, Node *> mp;

    function<Node *(Node *)> dfs = [&](Node *cur) -> Node * {
        if (mp.count(cur)) return mp[cur];  // pehle se clone ho chuka — cycle safe
        Node *copy = new Node(cur->val);
        mp[cur] = copy;  // create karke turant map me daalo — cycle break
        for (Node *nb : cur->neighbors)
            copy->neighbors.push_back(dfs(nb));  // har edge ke liye recursive clone
        return copy;
    };
    return dfs(node);
}

int main() {
    Node *a = new Node(1), *b = new Node(2);
    a->neighbors = {b};
    b->neighbors = {a};
    Node *c = cloneGraph(a);
    cout << (c && c->val == 1 && c != a && c->neighbors[0]->val == 2 ? "OK" : "FAIL") << endl;
    return 0;
}
