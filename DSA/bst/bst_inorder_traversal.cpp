/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_inorder_traversal.cpp
 * PROBLEM  : Bst Inorder Traversal
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST FROM SORTED INORDER — Balanced BST via mid element
// ────────────────────────────────────────────────────────────────────────────
// Problem: Sorted inorder array se balanced BST banao.
//
// Approach: Mid element = root, left/right halves recursively
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

// ── levelordertraversal: BFS print ──
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

// ── CreateBST: sorted inorder [s..e] se BST ──
//   1) s > e → NULL
//   2) mid = (s+e)/2 → root
//   3) Left = [s..mid-1], Right = [mid+1..e]
Node* CreateBST(int inorder[], int s, int size, int e){
    if(s>e){
        return NULL;
    }
    int mid= s+(e-s)/2;
    
    Node* root= new Node(inorder[mid]);
    root-> left = CreateBST(inorder, s, size, mid-1);
    root-> right= CreateBST(inorder, mid+1, size, e);
    return root;
}

// ── main: sorted array → BST → level order ──
int main(){
    int inorder[]= {10,20,30,40,50,60,70};
    int size= 7;
    int s=0; 
    int e= size-1;
    Node* root= CreateBST(inorder, s, size, e);
    levelordertraversal(root);
}
