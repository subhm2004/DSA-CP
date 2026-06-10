/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_search.cpp
 * PROBLEM  : Bst Search
 * LEETCODE : 700 — Search in a Binary Search Tree
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST SEARCH — Target dhundho, min/max nikalo
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST me value search karo; minimum aur maximum bhi nikalo.
//
// Approach: BST property exploit — target < root → left, warna right
// Complexity: Time O(h)  |  Space O(h) recursion
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

// ── CreateBST: insert karke BST maintain ──
//   1) NULL → naya node
//   2) data > root → right me insert
//   3) Warna left me insert
Node* CreateBST(Node* root, int data){
    if(root== NULL){
        root= new Node(data);
        return root;
    }
    if(data> root-> data){
        root-> right= CreateBST(root-> right, data);
    }
    else {
        root-> left= CreateBST(root-> left, data);
    }
    return root;
}

// ── takinginput: -1 tak values insert ──
void takinginput(Node* &root){
    int data;
    cout<< "Enter data"<< endl;
    cin>>data;
    while(data!= -1){
        root= CreateBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}

// ── searchInBST: target hai ya nahi ──
//   1) NULL → false
//   2) Match → true
//   3) target < root → left search
//   4) Warna right search
bool searchInBST(Node* root, int target){
    if(root== NULL){
        return false;
    }
    if(root-> data== target){
        return true;
    }
    else if(root-> data > target){
        return searchInBST(root-> left, target);
    }
    else {
        return searchInBST(root-> right, target);
    }
}

// ── FindMinimum: leftmost node ki value ──
//   1) NULL → -1
//   2) Jab tak left hai, left jao
//   3) Leaf left = minimum
int FindMinimum(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> left!= NULL){
        root= root-> left;
    }
    return root-> data;
}

// ── FindMaxNode: rightmost node ki value ──
int FindMaxNode(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> right!= NULL){
        root= root-> right;
    }
    return root-> data;
}

// ── main: BST build, min/max print ──
int main(){
    Node* root= NULL;
    takinginput(root);
    int ans= FindMinimum(root);
    int ans2= FindMaxNode(root);
    cout<< "Minimum Value: "<< ans<< endl;
    cout<< "Maximum Value: "<< ans2<< endl;
}
