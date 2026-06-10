/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : boundary_traversal.cpp
 * PROBLEM  : Boundary Traversal
 * LEETCODE : 545 — Boundary of Binary Tree
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
// BOUNDARY TRAVERSAL — Tree ki outer perimeter print
// ────────────────────────────────────────────────────────────────────────────
// Problem: Anti-clockwise boundary: left edge + leaves + right edge (reverse)
//
// Approach: 3 parts
//   1) Left boundary (top-down, leaves skip)
//   2) All leaf nodes (left to right)
//   3) Right boundary (bottom-up, leaves skip)
//
// Complexity: Time O(n)  |  Space O(h)
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

// ── leftboundary: left edge top-down (leaves skip) ──
//   1) NULL return
//   2) Leaf pe ruk jao (leaves alag print honge)
//   3) Print root, left prefer karo warna right
void leftboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left == NULL && root-> right== NULL){ // leaf — skip
        return;
    }
    cout<< root-> data<< " ";
    if(root-> left!= NULL){
        leftboundary(root-> left);
    }
    else {
        leftboundary(root-> right);
    }
}

// ── rightboundary: right edge bottom-up (leaves skip) ──
//   1) Pehle recurse, phir print (reverse order)
//   2) Right prefer, warna left
void rightboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left== NULL && root-> right== NULL){
        return;
    }
    if(root-> right!= NULL){
        rightboundary(root-> right);
    }
    else {
        rightboundary(root-> left);
    }
    cout<< root-> data<< " ";  // post-order style print
}

// ── leafboundary: saari leaves left-to-right ──
//   1) Leaf detect → print
//   2) Left pehle, phir right
void leafboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left== NULL && root-> right== NULL){
        cout<< root-> data<< " ";
    }
    leafboundary(root-> left);
    leafboundary(root-> right);
}

// ── boundarytraversal: teen parts combine ──
//   1) Left boundary
//   2) Leaves
//   3) Right boundary (reverse)
void boundarytraversal(Node* root){
    if(root== NULL){
        return;
    }
    leftboundary(root);
    leafboundary(root);
    if(root-> right!= NULL){
        rightboundary(root-> right);
    }
    if(root-> left!= NULL){
        rightboundary(root-> left);
    }
}

// ── main: boundary print ──
int main(){
    Node* root= CreateTree();
    boundarytraversal(root);
}
