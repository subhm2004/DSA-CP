/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : largest_bst_subtree.cpp
 * PROBLEM  : Largest Bst Subtree
 * LEETCODE : 333 — Largest BST Subtree
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LARGEST BST SUBTREE — Sabse bada valid BST subtree
// ────────────────────────────────────────────────────────────────────────────
// Problem: Binary tree me sabse bada subtree jo valid BST ho?
//
// Approach: Post-order DFS — har node pe (size, min, max, isValid) return
//   - Valid BST: left.max < root < right.min
//   - ans = max valid size across tree
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

class NodeData{
    public:
    int size;
    int minval;
    int maxval;
    bool validBST;
    NodeData(){}
    NodeData(int size, int min, int max, bool valid){
        this-> size= size;
        minval= min;
        maxval= max;
        validBST= valid;
    }
};

// ── findlargest: post-order BST info collect ──
//   1) NULL → size 0, valid true, min=INT_MAX, max=INT_MIN
//   2) Left/right info merge
//   3) Current valid? left.max < root < right.min
//   4) Valid ho to ans update
NodeData findlargest(Node* root, int& ans){
    if(root== NULL){
        NodeData temp (0,INT_MAX, INT_MIN, true);
        return temp;
    }
    NodeData left= findlargest(root-> left, ans);
    NodeData right= findlargest(root-> right, ans);
    NodeData currNode;
    currNode.size= left.size + right.size +1;
    currNode.maxval= max(right.maxval, root-> data);
    currNode.minval= min(root-> data, left.minval);
    if(left.validBST && right.validBST && (root-> data> left.maxval && root-> data< right.minval)){
        currNode.validBST= true;
    }
    if(currNode.validBST){
        ans= max(ans, currNode.size);  // largest valid BST size
    }
    return currNode;
}

// ── CreateBST: insert ──
Node* CreateBST(Node* root, int data){
    if(root== NULL){
        root= new Node(data);
    }
    if(data> root-> data){
        root-> right= CreateBST(root-> right, data);
    }
    else if(data < root-> data){
        root-> left= CreateBST(root-> left, data);
    }
    return root;
}

// ── TakeInput: loop insert ──
void TakeInput(Node* root){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root= CreateBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}

// ── main: largest BST subtree size ──
int main(){
    Node* root= NULL;
    int ans=0;
    findlargest(root, ans);
}
