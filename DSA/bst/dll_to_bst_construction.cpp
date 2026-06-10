/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : dll_to_bst_construction.cpp
 * PROBLEM  : Dll To Bst Construction
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// SORTED DLL → BALANCED BST
// ────────────────────────────────────────────────────────────────────────────
// Problem: Sorted doubly linked list se balanced BST banao.
//
// Approach: Recursive mid pick (like sorted array BST)
//   - n/2 left subtree, current node root, n/2 right subtree
//
// Complexity: Time O(n log n)  |  Space O(n)
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

// ── CreateTree: DFS input tree ──
Node* CreateTree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data == -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}

// ── levelorderTraversal: BFS ──
void levelorderTraversal(Node* root){
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

// ── DLLconversionBST: sorted DLL → balanced BST ──
//   1) n <= 0 → NULL
//   2) Left half = (n/2)-1 nodes recursively
//   3) Current head = root, head advance
//   4) Right half = n/2 nodes recursively
Node* DLLconversionBST(Node* head, int n){
    if(n<=0 || head== NULL){
        return NULL;
    }
    Node* lefttree= DLLconversionBST(head, (n/2)-1);
    Node* root= head;
    root-> left= lefttree;
    if(head!= NULL){
        head= head-> right;  // DLL me aage badho
    }
    
    root-> right= DLLconversionBST(head, n/2);
    return root;
}

// ── main: placeholder entry ──
int main(){
}
