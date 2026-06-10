// Given 2 nodes p and q, find their Lowest Common Ancestor (LCA) in binary tree

#include<iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LCA ON BINARY TREE — Classic Recursive Approach
// ────────────────────────────────────────────────────────────────────────────
// Agar root == p ya q -> wahi return (ancestor mil gaya).
// Left aur right subtree me dono dhundo:
//   dono non-null -> root hi LCA hai (p ek side, q doosri)
//   ek hi non-null -> wahi side ka result return karo
// ════════════════════════════════════════════════════════════════════════════

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    // ── Node: naya tree node banao value ke saath ─────────────────────────────
    //   1) data = val set karo
    //   2) left aur right = NULL — baad me children attach honge
    Node(int val){
        this-> data= val;
        this-> left= NULL;
        this-> right= NULL;
    }
};

// ── CreateTree: recursive tree input (-1 = NULL) ────────────────────────────
//   1) user se value lo — -1 ho to NULL return (leaf nahi, missing child)
//   2) naya Node(val) banao
//   3) left = CreateTree(), right = CreateTree() — recursively poora tree banao
//   4) root return karo
Node* CreateTree(){
    int val;
    cout<< "enter data"<< endl;
    cin>> val;
    if(val==-1){
        return NULL;
    }
    Node* root = new Node(val);
    root-> left= CreateTree();
    root-> right= CreateTree();
}

// ── leastcommonancestor: p aur q ka LCA nikalo ───────────────────────────────
//   1) root NULL -> NULL; root==p ya q -> root return (khud ancestor hai)
//   2) left aur right subtree me recursively LCA dhoondo
//   3) dono non-NULL -> p ek side q doosri — root hi LCA
//   4) ek hi non-NULL -> wahi side ka result return; dono NULL -> NULL
Node* leastcommonancestor(Node* root, Node* p, Node* q){
    if(root== NULL){
        return NULL;
    }
    if(root== p){
        return p;
    }
    if(root== q){
        return q;
    }
        Node* left= leastcommonancestor(root->left,p,q);
        Node* right= leastcommonancestor(root-> right,p,q);
        if(left!= NULL && right!= NULL){   // p left me, q right me — root LCA
            return root;
        }
        else if(left!= NULL && right== NULL){
            return left;
        }
        else if(left== NULL && right != NULL){
            return right;
        }
        else {
            return NULL;
        }

}
int main(){
    Node* root= CreateTree();
   
}
