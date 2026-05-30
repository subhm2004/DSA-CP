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

class Node {
public:
    int val;
    vector<Node *> neighbors;
    Node(int _val) : val(_val) {}
};

Node *cloneGraph(Node *node) {
    if (!node) return nullptr;
    unordered_map<Node *, Node *> mp;

    function<Node *(Node *)> dfs = [&](Node *cur) -> Node * {
        if (mp.count(cur)) return mp[cur];
        Node *copy = new Node(cur->val);
        mp[cur] = copy;
        for (Node *nb : cur->neighbors)
            copy->neighbors.push_back(dfs(nb));
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
