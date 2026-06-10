/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_inorder_construction.cpp
 * PROBLEM  : Bst Inorder Construction
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST INORDER CONSTRUCTION — Sorted array se balanced tree
// ────────────────────────────────────────────────────────────────────────────
// Problem: Sorted inorder se BST construct (variant of bst_inorder_traversal).
//
// Approach: Divide & conquer — mid pick, left/right recurse
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

// ── CreateBSTInorder: [s..e] range se BST ──
//   1) s >= e → NULL (base case variant)
//   2) mid element root banao
//   3) Left/right halves recursively
Node* CreateBSTInorder(int inorder[], int s, int e, int& size){
    if(s>=e){
        return NULL;
    }
    int mid= s+(e-s)/2;
    Node* root= new Node(inorder[mid]);
    root-> left=  CreateBSTInorder(inorder, s, mid-1, size);
    root-> right= CreateBSTInorder(inorder, mid+1, e, size);
    return root;
}

// ── levelordertraversal: BFS level print ──
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

// ── main: demo with sorted inorder array ──
int main(){
    int inorder[]= {5,10,15,20,25,30,35,40};
    int size= 8;
    int s=0;
    int e= size-1;
    Node* root= CreateBSTInorder(inorder, s,e, size);
    levelordertraversal(root);
}
