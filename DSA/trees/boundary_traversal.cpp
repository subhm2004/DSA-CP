/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : boundary_traversal.cpp
 * PROBLEM  : Boundary Traversal
 * LEETCODE : 545 — Boundary of Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <map>
using namespace std;
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


/*
 * CreateTree()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Returns : Node*
 */
Node* CreateTree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data==-1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}


/*
 * leftboundary()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void leftboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left == NULL && root-> right== NULL){ // leaf node pr aagye
        return;
    }
    cout<< root-> data<< " ";
    if(root-> left!= NULL){
        leftboundary(root-> left);
    }
    else {
        leftboundary(root-> right);
    }
}


/*
 * rightboundary()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void rightboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left== NULL && root-> right== NULL){
        return;
    }
    if(root-> right!= NULL){
        rightboundary(root-> right);

    }
    else {
        rightboundary(root-> left);
    }
    cout<< root-> data<< " ";
}


/*
 * leafboundary()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void leafboundary(Node* root){
    if(root== NULL){
        return;
    }
    if(root-> left== NULL && root-> right== NULL){
        cout<< root-> data<< " ";
    }
    leafboundary(root-> left);
    leafboundary(root-> right);
}


/*
 * boundarytraversal()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void boundarytraversal(Node* root){
    if(root== NULL){
        return;
    }
    leftboundary(root);
    leafboundary(root);
    if(root-> right!= NULL){
        rightboundary(root-> right);
    }
    if(root-> left!= NULL){
        rightboundary(root-> left);
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Boundary Traversal
 */
int main(){
    Node* root= CreateTree();
    boundarytraversal(root);
}
