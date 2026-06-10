/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : build_tree_inorder_preorder.cpp
 * PROBLEM  : Build Tree Inorder Preorder
 * LEETCODE : 105 — Construct Binary Tree from Preorder and Inorder
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Tree DFS in specific visit order.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BUILD TREE — Preorder + Inorder se binary tree reconstruct
// ────────────────────────────────────────────────────────────────────────────
// Problem: Do traversals se original tree wapas banao.
//
// Approach: Recursive divide
//   - Preorder[0] = root (preIndex se)
//   - Inorder me root dhundho → left/right split
//   - Left subtree = inorder[start..pos-1], right = inorder[pos+1..end]
//
// Complexity: Time O(n²) linear search  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node(int val){
        this-> data= val;
        this-> left= NULL;
        this-> right= NULL;
    }
};

// ── levelorder: BFS se tree print ──
//   1) Queue + NULL separator
//   2) Node print + children push
void levelorder(Node* root) {
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
            q.push(NULL);
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}

// ── searchinorder: inorder me element ki position ──
//   1) Linear scan — target mila to index return
//   2) Nahi mila to -1
int searchinorder(int inorder[], int size, int target){
    for(int i=0; i< size; i++){
        if(inorder[i] == target){
            return i;
        }
    }
    return -1;
}

// ── createtreeprein: preorder+inorder se tree banao ──
//   1) Base: invalid range → NULL
//   2) Preorder[preIndex] = root element, preIndex++
//   3) Inorder me position dhundho
//   4) Left = inorder[start..pos-1], Right = inorder[pos+1..end]
//   5) Recursively left/right build karo
Node* createtreeprein(int preorder[], int &preorder_index, int size, int inorder[], int inorder_start, int inorder_end){
    if(preorder_index >= size|| inorder_start > inorder_end){
        return NULL;
    }
    int element= preorder[preorder_index];
    preorder_index++;  
    Node* root= new Node(element);
    int position= searchinorder(inorder, size, element);  // root ki jagah
    root-> left= createtreeprein(preorder, preorder_index, size, inorder, inorder_start, position-1);
    root-> right= createtreeprein(preorder,preorder_index, size, inorder, position +1, inorder_end);
    return root;
}

// ── main: sample arrays se tree build ──
int main(){
    int preorder[]= {2,8,10,6,4,12};
    int inorder[]= {10,8,6,2,4,12};
    int size= 6;
    int preorder_index= 0;
    int inorder_start=0;
    int inorder_end= 5;
    Node* root= createtreeprein(preorder, preorder_index, size, inorder, inorder_start, inorder_end);
    cout<< "Printing tree"<< endl;
    levelorder(root);
}
