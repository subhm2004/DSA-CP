/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_practice.cpp
 * PROBLEM  : Binary Tree Practice
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BINARY TREE PRACTICE — Saari traversals ek saath demo
// ────────────────────────────────────────────────────────────────────────────
// Problem: Tree build karo aur preorder/inorder/postorder/level-order chalao.
//
// Approach: Classic recursive DFS + BFS queue
// Complexity: Har traversal O(n)
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        this-> data= val;
        this-> left= NULL;
        this->right= NULL;
    }
};

// ── CreateTree: recursive tree construction ──
//   1) Data input, -1 = NULL
//   2) Node banao, left/right build karo
//   3) Root return (note: original me return missing tha)
Node* CreateTree(){
    int data;
    cout<< "enter node data"<< endl;
    cin>> data;
    if(data== -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
}

// ── preorder: Root → Left → Right ──
//   1) Base: NULL return
//   2) Print root, recurse left, recurse right
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    cout<< root-> data<< "->";
    preorder(root->left);
    preorder(root->right);
}

// ── inorder: Left → Root → Right ──
//   1) Base: NULL return
//   2) Left pehle, root print, phir right
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root->left);
    cout<< root->data<<"->";
    inorder(root->right);
}

// ── postorder: Left → Right → Root ──
//   1) Base: NULL return
//   2) Left, right pehle, root last me print
void postorder(Node* root){
    if(root== NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<< root-> data<< "->";
}

// ── levelorder: simple BFS without level separator ──
//   1) Empty check, queue me root
//   2) Front print, children push, pop
void levelorder(Node* root){
    if(root== NULL){
        return;
    }
    queue<Node*>q;
    q.push(root);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        cout<< newnode-> data<< "->";
        if(newnode-> left!= NULL){
            q.push(newnode-> left);
        }
        if(newnode-> right!= NULL){
            q.push(newnode-> right);
        }
    }
}

// ── levelordertraversal: NULL se level divide ──
//   1) Queue: root + NULL marker
//   2) Node → print + children push
//   3) NULL → newline, agla level start
void levelordertraversal(Node* root){
    if(root== NULL){
        return;
    }
    queue<Node*>q1;
    q1.push(root);
    q1.push(NULL);
    while(!q1.empty()){
        Node* newnode= q1.front();
        q1.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< "->";
            if(newnode-> left!= NULL){
                q1.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q1.push(newnode-> right);
            }
        }
        else {
            cout<< endl;
            if(!q1.empty()){
                q1.push(NULL);
            }
        }
    }
}

// ── main: saari traversals demo ──
int main(){
    Node* root= CreateTree();
    cout<< "INORDER"<< endl;
    inorder(root);
    cout<< endl;
    cout<< "PREORDER"<< endl;
    preorder(root);
    cout<< endl;
    cout<< "POSTORDER"<< endl;
    postorder(root);
    cout<< endl;
    cout<< "LEVELORDER"<< endl;
    levelorder(root);
    cout<< endl;
    cout<< "LEVELORDER TRAVERSAL"<< endl;
    levelordertraversal(root);
    cout<< endl;
}
