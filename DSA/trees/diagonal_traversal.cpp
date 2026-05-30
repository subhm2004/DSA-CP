/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : diagonal_traversal.cpp
 * PROBLEM  : Diagonal Traversal
 * LEETCODE : 545 — Boundary of Binary Tree (diagonal — GFG variant)
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
 * levelorder()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void levelorder(Node* root){
    queue<Node*>q;
    q.push(root);
    Node* temp= q.front();
    while(!q.empty()) {
        if(temp== root) q.pop();
        if(temp== NULL){
            temp= q.front();
            q.pop();
        }       
        cout<< temp-> data<< " ";
        if(temp-> left!= NULL){
            q.push(temp-> left);
        }
        if(temp-> right!= NULL){
            temp= temp-> right;
        }
        else {
            temp= NULL;
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Diagonal Traversal
 */
int main(){
    Node* root= CreateTree();
    cout<< "printing diagonal traversal"<< endl;
    levelorder(root);
}
