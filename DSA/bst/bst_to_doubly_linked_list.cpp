/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_to_doubly_linked_list.cpp
 * PROBLEM  : Bst To Doubly Linked List
 * LEETCODE : 426 — Convert BST to Sorted Doubly Linked List
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST → SORTED DOUBLY LINKED LIST
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST ko in-place sorted circular DLL me convert karo.
//
// Approach: Reverse inorder (right → root → left)
//   - Har node ko head ke left me link karo
//   - Result: ascending sorted DLL
//
// Complexity: Time O(n)  |  Space O(h) recursion
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

// ── CreateTree: generic tree build (DFS input) ──
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

// ── levelorderTraversal: BFS print ──
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

// ── converttoDLL: reverse inorder se sorted DLL ──
//   1) NULL return
//   2) Pehle right subtree (bade values)
//   3) root->right = head, head->left = root
//   4) head = root
//   5) Phir left subtree
void converttoDLL(Node* root, Node* &head){
    if(root== NULL){
        return;
    }
    converttoDLL(root-> right, head);  // right pehle = reverse inorder
    root-> right= head;
    if(head!= NULL){
        head-> left= root;
    }
    head= root;
    converttoDLL(root-> left, head);
}

// ── printLL: DLL forward print ──
void printLL(Node* head){
    cout<< "Printing double linkedlist"<< endl;
    Node* temp= head;
    while(temp!= NULL){
        cout<< temp-> data<< "->";
        temp= temp-> right;
    }
    cout<< endl;
}

// ── main: tree → DLL convert ──
int main(){
    Node* root= CreateTree();
    levelorderTraversal(root);
    Node* head= NULL;
    converttoDLL(root, head);
}
