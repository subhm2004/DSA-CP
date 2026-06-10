/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : bst_to_max_heap.cpp
 * PROBLEM  : Bst To Max Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BST TO MAX HEAP — Pehle BST banao, phir heap me convert
// ────────────────────────────────────────────────────────────────────────────
// BST insert: left chhota, right bada (yahan reversed hai — demo code)
// Level order print se tree structure verify karte hain
// Max heap banane ke liye post-order / heapify step baad me add hoga
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

// ── InsertIntoBST: BST me naya node insert ─────────────────────────────────
//   1) root NULL ho to naya node banao aur return
//   2) data chhota ho to right subtree me jao (is file me reversed)
//   3) data bada ho to left subtree me jao
//   4) updated root return karo
Node* InsertIntoBST(Node* root, int data){
    if(root== NULL){
        root= new Node(data);
        return root;
    }
    if(root-> data> data){
        root-> right= InsertIntoBST(root-> right, data);
    }
    if(root-> data< data){
        root-> left= InsertIntoBST(root-> left, data);
    }
    return root;

}

// ── CreateBST: user se input leke BST build ────────────────────────────────
//   1) data input lo jab tak -1 na aaye
//   2) har value ko InsertIntoBST se root me add karo
//   3) loop me next data maango
void CreateBST(Node* root){
    int data;
    cout<< "enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root = InsertIntoBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}

// ── levelordertraversal: level-by-level print ──────────────────────────────
//   1) queue me root aur NULL separator push
//   2) non-NULL node -> data print, children push
//   3) NULL -> newline, agar queue khali nahi to NULL push (level break)
//   4) har level alag line pe dikhta hai
void levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< endl;
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

// ── main: demo entry point ─────────────────────────────────────────────────
//   1) empty BST root banate hain
int main(){
    Node* root= NULL;
}
