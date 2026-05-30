/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_creation.cpp
 * PROBLEM  : Bst Creation
 * LEETCODE : 701 — Insert into a Binary Search Tree
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
    if(root == NULL){
        root= new Node(data);
        return root;
    }
    if(data< root-> data){
        root-> left= CreateBST(root-> left, data);
    }
    if(data> root-> data){
        root-> right= CreateBST(root-> right, data);
    }
    return root;
}


/*
 * preorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root
 * Returns : void
 */
void preorder(Node* root){
    if(root== NULL){
        return;
    }
    cout<< root-> data<< " ";
    preorder(root-> left);
    preorder(root-> right);
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
 * postorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root
 * Returns : void
 */
void postorder(Node* root){
    if(root== NULL){
        return;
    }
    postorder(root-> left);
    postorder(root-> right);
    cout<< root-> data<< " ";
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
 * takeInput()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* &root
 * Returns : void
 */
void takeInput(Node* &root){
    int data;
    cout<< "Enter the data"<< endl;
    cin>> data;
    while(data!= -1){
        root= CreateBST(root, data);
        cout<< "Enter the data"<< endl;
        cin>> data;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Bst Creation
 */
int main(){
    Node* root= NULL;
    takeInput(root);
    inorder(root);
   

}
