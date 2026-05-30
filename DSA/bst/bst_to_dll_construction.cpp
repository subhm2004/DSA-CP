/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_to_dll_construction.cpp
 * PROBLEM  : Bst To Dll Construction
 * LEETCODE : 426 — Convert BST to Sorted Doubly Linked List
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
 * InserttoBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int data
 * Returns : Node*
 */
Node* InserttoBST(Node* root, int data){
    if(root== NULL){
        root= new Node(data);
        return root;
    }
    if(root-> data< data){
        root-> right= InserttoBST(root-> right, data);
    }
    if(root-> data> data){
        root-> left= InserttoBST(root-> left, data);
    }
    return root;
}


/*
 * takingInput()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* &root
 * Returns : void
 */
void takingInput(Node* &root){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root= InserttoBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}


/*
 * ConverttoDLL()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, Node* &head
 * Returns : void
 */
void ConverttoDLL(Node* root,Node* &head){
    if(root== NULL){
        return;
    }
    ConverttoDLL(root-> right, head);
    root-> right= head;
    if(head!= NULL){
        head-> left= root;
    }
    head= root;
    ConverttoDLL(root-> left, head);
}


/*
 * LevelOrderTraversal()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : void
 */
void LevelOrderTraversal(Node* root){
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
 * inorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root
 * Returns : void
 */
void inorder(Node* root){
    if(root== NULL){
        return;
    }
    inorder(root-> left);
    cout<< root-> data<< " ";
    inorder(root-> right);
}


/*
 * main()
 * Purpose : Entry point — demo/test for Bst To Dll Construction
 */
int main(){
    Node* root= NULL;
    takingInput(root);
    LevelOrderTraversal(root);
    cout<< endl;
}
