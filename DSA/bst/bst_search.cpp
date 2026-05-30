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
 * CreateBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int data
 * Returns : Node*
 */
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


/*
 * takinginput()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* &root
 * Returns : void
 */
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


/*
 * searchInBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int target
 * Returns : bool
 */
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


/*
 * FindMinimum()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : int
 */
int FindMinimum(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> left!= NULL){
        root= root-> left;
    }
    return root-> data;
}


/*
 * FindMaxNode()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : int
 */
int FindMaxNode(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> right!= NULL){
        root= root-> right;
    }
    return root-> data;
}



/*
 * main()
 * Purpose : Entry point — demo/test for Bst Search
 */
int main(){
    Node* root= NULL;
    takinginput(root);
    int ans= FindMinimum(root);
    int ans2= FindMaxNode(root);
    cout<< "Minimum Value: "<< ans<< endl;
    cout<< "Maximum Value: "<< ans2<< endl;

}
