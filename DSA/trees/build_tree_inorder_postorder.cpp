/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : build_tree_inorder_postorder.cpp
 * PROBLEM  : Build Tree Inorder Postorder
 * LEETCODE : 106 — Construct Binary Tree from Inorder and Postorder
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Tree DFS in specific visit order.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BUILD TREE — Inorder + Postorder se reconstruct
// ────────────────────────────────────────────────────────────────────────────
// Problem: Postorder (L,R,Root) + Inorder se tree banao.
//
// Approach: Recursive
//   - Postorder[last] = root (post_index backward)
//   - Inorder me root dhundho → left/right split
//   - Pehle RIGHT build (postorder me root ke baad right aata hai)
//
// Complexity: Time O(n²)  |  Space O(n)
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
        Node* newnode = q.front();
        q.pop();
        if(newnode== NULL){
            cout<< endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else {
            if(newnode-> left != NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
    }
}

// ── searchpostorder: inorder me target ki index ──
int searchpostorder(int inorder[], int size, int target){
    for(int i=0; i< size; i++){
        if(inorder[i]== target){
            return i;
        }
    }
    return -1;
}

// ── inpostcreatetree: inorder+postorder se tree ──
//   1) Base: invalid range → NULL
//   2) postorder[post_index] = root, post_index--
//   3) Inorder me position dhundho
//   4) Pehle RIGHT subtree (post_index backward)
//   5) Phir LEFT subtree
Node* inpostcreatetree(int postorder[], int inorder[], int size, int &post_index, int inorder_start, int inorder_end){
    if(post_index <0 || inorder_start> inorder_end){
        return NULL;
    }
    int element= postorder[post_index];
    post_index--;
    Node* root = new Node(element);
    int position= searchpostorder(inorder,size,element);
    root-> right= inpostcreatetree(postorder, inorder, size, post_index, position +1, inorder_end);
    root-> left= inpostcreatetree(postorder,inorder,size,post_index,inorder_start, position-1);
    return root;
}

// ── main: sample build demo ──
int main(){
    int postorder[]= {8,6,12,4,10,2};
    int inorder[]= {8,12,6,2,10,4};
    int size= 6;
    int post_index= size-1;
    int inorder_start= 0;
    int inorder_end= size-1;
    Node* root= inpostcreatetree(postorder,inorder,size,post_index,inorder_start,inorder_end);
    levelordertraversal(root);
}
