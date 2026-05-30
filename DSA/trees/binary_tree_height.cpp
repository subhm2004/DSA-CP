/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_height.cpp
 * PROBLEM  : Binary Tree Height
 * LEETCODE : 104 — Maximum Depth of Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
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
 * Maxdepth()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : int
 */
int Maxdepth(Node* root){
    if(root== NULL){
        return 0;
    }
    int left= Maxdepth(root->left);
    int right= Maxdepth(root-> right);
    int maxi= max(left,right);
    return maxi+1;

}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Tree Height
 */
int main(){
    Node* root= CreateTree();


}
