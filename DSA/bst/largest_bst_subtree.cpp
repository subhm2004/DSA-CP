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
    NodeData(){

    }
    NodeData(int size, int min, int max, bool valid){
        this-> size= size;
        minval= min;
        maxval= max;
        validBST= valid;
    }
};


/*
 * findlargest()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, int& ans
 * Returns : NodeData
 */
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
        ans= max(ans, currNode.size);
    }
    return currNode;

}


/*
 * CreateBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int data
 * Returns : Node*
 */
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


/*
 * TakeInput()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : void
 */
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



/*
 * main()
 * Purpose : Entry point — demo/test for Largest Bst Subtree
 */
int main(){
    Node* root= NULL;
    int ans=0;
    findlargest(root, ans);

}
