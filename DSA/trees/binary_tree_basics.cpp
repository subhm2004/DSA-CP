/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_basics.cpp
 * PROBLEM  : Binary Tree Basics
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY TREE BASICS — Saari common traversals
// ────────────────────────────────────────────────────────────────────────────
// Problem: Binary tree ko build karo aur saari traversal types print karo.
//
// Traversals:
//   - Preorder  : Root → Left → Right
//   - Inorder   : Left → Root → Right
//   - Postorder : Left → Right → Root
//   - Level order: BFS queue se level-by-level
//
// Complexity: Har traversal O(n) time, O(h) ya O(n) space
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

// ── CreateTree: DFS se tree build ──
//   1) Data input lo, -1 = NULL
//   2) Node banao, left/right recursively call
//   3) Root return karo
Node* CreateTree(){
    int data;
    cout<< "Enter the data of node"<< endl;
    cin>> data;
    if(data== -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}

// ── preorder: Root pehle visit ──
//   1) NULL → return
//   2) Current node print karo
//   3) Left subtree, phir right subtree
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    cout<< root-> data<< "->";
    preorder(root-> left);
    preorder(root-> right);
}

// ── inorder: Root beech me ──
//   1) NULL → return
//   2) Pehle left, phir root print, phir right
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout<< root-> data<< "->";
    inorder(root->right);
}

// ── postorder: Root last me ──
//   1) NULL → return
//   2) Pehle left, phir right, last me root print
void postorder(Node* root){
    if(root== NULL){
        return;
    }
    postorder(root-> left);
    postorder(root-> right);
    cout<< root-> data<< "->";
}

queue<Node*>q;

// ── levelorder: simple BFS ──
//   1) Root queue me daalo
//   2) Jab tak queue khali nahi — front print, children push
//   3) Pop karo aur aage badho
void levelorder(Node* root){
    q.push(root);
    while(!q.empty()){
        cout << root-> data << "->";
             q.push(root->left);
            q.push(root->right);
        q.pop();
        root = q.front();
    }
}

// ── levelordertraversal: level-wise print (NULL separator) ──
//   1) Queue me root + NULL daalo (level end marker)
//   2) Node aaye → print + children push
//   3) NULL aaye → newline + agla level start
void levelordertraversal(Node* root){
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< "->";
            if(newnode-> left!= NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
        else{
            cout<< endl;  // ek level khatam
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}

// ── main: tree banao aur level-order print ──
int main(){
    Node* root = CreateTree();
    levelordertraversal(root);
}
