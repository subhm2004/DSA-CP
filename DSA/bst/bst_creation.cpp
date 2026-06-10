/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_creation.cpp
 * PROBLEM  : Bst Creation
 * LEETCODE : 701 — Insert into a Binary Search Tree
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST CREATION — Insert + saari traversals
// ────────────────────────────────────────────────────────────────────────────
// Problem: Values insert karke BST banao; preorder/inorder/postorder/level print.
//
// Approach: Recursive insert + standard traversals
// Complexity: Insert O(h)  |  Traversal O(n)
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

// ── CreateBST: recursive insert ──
//   1) NULL → naya node return
//   2) data < root → left subtree
//   3) data > root → right subtree
Node* CreateBST(Node* root, int data){
    if(root == NULL){
        root= new Node(data);
        return root;
    }
    if(data< root-> data){
        root-> left= CreateBST(root-> left, data);
    }
    if(data> root-> data){
        root-> right= CreateBST(root-> right, data);
    }
    return root;
}

// ── preorder: Root → Left → Right ──
void preorder(Node* root){
    if(root== NULL){
        return;
    }
    cout<< root-> data<< " ";
    preorder(root-> left);
    preorder(root-> right);
}

// ── inorder: Left → Root → Right (BST = sorted) ──
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout<< root-> data<< " ";
    inorder(root-> right);
}

// ── postorder: Left → Right → Root ──
void postorder(Node* root){
    if(root== NULL){
        return;
    }
    postorder(root-> left);
    postorder(root-> right);
    cout<< root-> data<< " ";
}

// ── levelordertraversal: BFS level-wise ──
void levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< " ";
            if(newnode-> left!= NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
        else {
            cout<< endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}

// ── takeInput: -1 tak insert loop ──
void takeInput(Node* &root){
    int data;
    cout<< "Enter the data"<< endl;
    cin>> data;
    while(data!= -1){
        root= CreateBST(root, data);
        cout<< "Enter the data"<< endl;
        cin>> data;
    }
}

// ── main: input → inorder (sorted) print ──
int main(){
    Node* root= NULL;
    takeInput(root);
    inorder(root);
}
