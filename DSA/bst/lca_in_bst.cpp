/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : lca_in_bst.cpp
 * PROBLEM  : Lca In Bst
 * LEETCODE : 235 — Lowest Common Ancestor of a BST
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LCA IN BST — Do nodes ka lowest common ancestor
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST me p aur q ka LCA dhundho.
//
// Approach: BST property use karo
//   - Dono root ke opposite sides → root hi LCA
//   - Dono left me → left recurse
//   - Dono right me → right recurse
//
// Complexity: Time O(h)  |  Space O(h)
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

// ── CreateBST: standard insert ──
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

// ── inorder: sorted traversal ──
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout<< root-> data<< " ";
    inorder(root-> right);
}

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

// ── takeInput: values insert loop ──
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

// ── LCABST: BST me LCA dhundho ──
//   1) NULL → NULL
//   2) root == p ya q → wahi return
//   3) p left, q right (ya ulta) → root LCA hai
//   4) Dono left → left recurse
//   5) Dono right → right recurse
Node* LCABST(Node* root, Node* p, Node* q){
    if(root== NULL){
        return NULL;
    }
    if(root== p){
        return p;
    }
    if(root== q){
        return q;
    }
    if(root!= p && root!= q){
        if((p-> data< root-> data && q-> data> root-> data)|| (p-> data> root-> data && q-> data< root-> data)){
            return root;  // split point = LCA
        }
        else if(p-> data< root-> data && q-> data< root-> data){
            return LCABST(root-> left, p,q);
        }
        else {
            return LCABST(root-> right, p, q);
        }
    }
}

// ── main: BST build + level order demo ──
int main(){
    Node* root= NULL;
    takeInput(root);
    cout<< "level order traversal is: "<< endl;
    levelordertraversal(root);
    cout<< endl;
}
