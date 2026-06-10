/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_height.cpp
 * PROBLEM  : Binary Tree Height
 * LEETCODE : 104 — Maximum Depth of Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY TREE HEIGHT — Maximum depth nikalo
// ────────────────────────────────────────────────────────────────────────────
// Problem: Root se sabse neeche leaf tak kitne edges/nodes?
//
// Approach: Recursive DFS
//   - NULL → 0 return
//   - max(leftDepth, rightDepth) + 1
//
// Complexity: Time O(n)  |  Space O(h) recursion
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        this-> data= val;
        this-> left= NULL;
        this-> right= NULL;
    }
};

// ── CreateTree: user input se tree banao ──
//   1) Data lo, -1 = NULL
//   2) Node create, left/right recursive
//   3) Root return
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

// ── Maxdepth: subtree ki maximum depth ──
//   1) NULL → 0 (base case)
//   2) Left aur right depth recursively
//   3) Dono ka max lo + 1 (current level)
//   4) Ye poori tree ki height hai
int Maxdepth(Node* root){
    if(root== NULL){
        return 0;
    }
    int left= Maxdepth(root->left);
    int right= Maxdepth(root-> right);
    int maxi= max(left,right);
    return maxi+1;
}

// ── main: tree build karo ──
int main(){
    Node* root= CreateTree();
}
