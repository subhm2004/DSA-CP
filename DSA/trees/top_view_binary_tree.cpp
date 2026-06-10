/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : top_view_binary_tree.cpp
 * PROBLEM  : Top View Binary Tree
 * LEETCODE : 314 — Binary Tree Vertical Order Traversal
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <map>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TOP / BOTTOM VIEW — Vertical distance (HD) se nodes group
// ────────────────────────────────────────────────────────────────────────────
// Problem: Tree ko upar/neeche se dekho — har vertical line ka node?
//
// Approach: BFS + map<HD, value>
//   - Left → HD-1, Right → HD+1
//   - Top view: pehli baar HD dikhe to store
//   - Bottom view: har baar overwrite (last = bottom)
//
// Complexity: Time O(n log n) map  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int data){
        this-> data= data;
        this-> left= NULL;
        this-> right= NULL;
    }
};

// ── CreateTree: recursive input ──
Node* CreateTree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data==-1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}

// ── topview: BFS — har HD ka pehla node ──
//   1) Queue: (node, horizontalDistance)
//   2) HD pehli baar aaye → map me store
//   3) Left HD-1, right HD+1 push
void topview(Node* root){
    map<int,int>distNode;
    queue<pair<Node*,int>>q;
    q.push(make_pair(root,0));
    while(!q.empty()){
        pair<Node*,int> temp = q.front();
        q.pop();
        Node* frontNode = temp.first;
        int level= temp.second;
        if(distNode.find(level)== distNode.end()){
            distNode[level]= frontNode-> data;  // pehli entry = top
        }
        if(frontNode-> left!= NULL){
            q.push(make_pair(frontNode-> left, level-1));
        }
        if(frontNode-> right!= NULL){
            q.push(make_pair(frontNode-> right, level+1));
        }
    }
    cout<< "Top view"<< endl;
    for(auto i: distNode){
        cout<< i.second<< " ";
    }
}

// ── bottomview: BFS — har HD ka last node ──
//   1) Same BFS, lekin har baar overwrite
//   2) Last visit = sabse neeche wala node
void bottomview(Node* root){
    map<int, int>distNode;
    queue<pair<Node*, int>>q;
    q.push(make_pair(root,0));
    while(!q.empty()){
        pair<Node*, int>temp= q.front();
        q.pop();
        Node* frontNode= temp.first;
        int level= temp.second;
        distNode[level]= frontNode-> data;  // overwrite = bottom
        if(frontNode-> left!= NULL){
            q.push(make_pair(frontNode-> left, level-1));
        }
        if(frontNode-> right!= NULL){
            q.push(make_pair(frontNode-> right, level+1));
        }
    }
    cout<< "Bottom View"<< endl;
    for(auto i: distNode){
        cout<< i.second << " ";
    }        
}

// ── main: bottom view demo ──
int main(){
    Node* root= CreateTree();
    bottomview(root);
}
