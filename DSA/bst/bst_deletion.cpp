/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_deletion.cpp
 * PROBLEM  : Bst Deletion
 * LEETCODE : 450 — Delete Node in a BST
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
 * Returns : Node*
 */
Node* searchInBST(Node* root, int target){
    if(root == NULL){
        return NULL;
    }
    if(root-> data== target){
        return root;
    }
    else if(root-> data> target){
        return searchInBST(root-> left, target);
    }
    else {
        return searchInBST(root-> right, target);
    }

}


/*
 * levelordertraversal()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : void
 */
void levelordertraversal(Node* root){
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
            if(!q.empty()){
                q.push(NULL);
            }
        }
    }
}


/*
 * FindMaximum()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : int
 */
int FindMaximum(Node* root){
    if(root== NULL){
        return -1;
    }
    while(root-> right!= NULL){
        root= root-> right;
    }
    return root-> data;

}



/*
 * deletionInBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int target
 * Returns : Node*
 */
Node* deletionInBST(Node* root, int target){
    if(root== NULL){
        return NULL;
    }
    if(root-> data == target){
         if(root-> left== NULL && root-> right== NULL){
        delete root;
        return NULL;
    }
    else if(root-> left!= NULL && root -> right== NULL){
        Node* child= root-> left;
        delete root;
        return child;
    }
    else if(root-> left== NULL && root-> right!= NULL){
        Node* child= root-> right;
        delete root;
        return child;
    }
    else {
        int child = FindMaximum(root-> left);
        root-> data= child;
        root-> left = deletionInBST(root-> left, child);
        return root;
    }

    }
    else if(root-> data > target){
        root-> left= deletionInBST(root-> left,target);
    }
    else {
        root-> right= deletionInBST(root-> right, target);
    }
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Bst Deletion
 */
int main(){
    Node* root= NULL;
    takinginput(root);
    int target;
    cout<< " Enter the node to be deleted"<< endl;
    cin>> target;
    deletionInBST(root, target);
    levelordertraversal(root);

}
