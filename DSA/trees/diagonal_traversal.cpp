/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : diagonal_traversal.cpp
 * PROBLEM  : Diagonal Traversal
 * LEETCODE : 545 — Boundary of Binary Tree (diagonal — GFG variant)
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <map>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DIAGONAL TRAVERSAL — ↘ diagonal lines me nodes print
// ────────────────────────────────────────────────────────────────────────────
// Problem: Tree ko diagonal (top-left to bottom-right) lines me traverse karo.
//
// Approach: Modified BFS
//   - Right child same diagonal pe rehta hai
//   - Left child nayi diagonal start karta hai
//   - Queue me sirf left children, temp right se slide
//
// Complexity: Time O(n)  |  Space O(n)
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

// ── CreateTree: recursive build ──
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

// ── levelorder: diagonal traversal (modified BFS) ──
//   1) Queue me left children store, temp right chain follow
//   2) Har node print, left push, right pe slide
//   3) Right khatam → queue se agla diagonal start
void levelorder(Node* root){
    queue<Node*>q;
    q.push(root);
    Node* temp= q.front();
    while(!q.empty()) {
        if(temp== root) q.pop();
        if(temp== NULL){
            temp= q.front();
            q.pop();
        }       
        cout<< temp-> data<< " ";
        if(temp-> left!= NULL){
            q.push(temp-> left);  // left = nayi diagonal
        }
        if(temp-> right!= NULL){
            temp= temp-> right;   // right = same diagonal continue
        }
        else {
            temp= NULL;          // diagonal khatam, queue se agla
        }
    }
}

// ── main: diagonal print demo ──
int main(){
    Node* root= CreateTree();
    cout<< "printing diagonal traversal"<< endl;
    levelorder(root);
}
