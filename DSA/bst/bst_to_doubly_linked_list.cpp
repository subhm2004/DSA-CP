/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : bst_to_doubly_linked_list.cpp
 * PROBLEM  : Bst To Doubly Linked List
 * LEETCODE : 426 — Convert BST to Sorted Doubly Linked List
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : DP: longest increasing subsequence ending at i.
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
 * CreateTree()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Returns : Node*
 */
Node* CreateTree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data == -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}


/*
 * levelorderTraversal()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root
 * Returns : void
 */
void levelorderTraversal(Node* root){
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
 * converttoDLL()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, Node* &head
 * Returns : void
 */
void converttoDLL(Node* root, Node* &head){
    if(root== NULL){
        return;
    }
    converttoDLL(root-> right, head);
    root-> right= head;
    if(head!= NULL){
        head-> left= root;
    }
    head= root;
    converttoDLL(root-> left, head);
}


/*
 * printLL()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* head
 * Returns : void
 */
void printLL(Node* head){
    cout<< "Printing double linkedlist"<< endl;
    Node* temp= head;
    while(temp!= NULL){
        cout<< temp-> data<< "->";
        temp= temp-> right;
    }
    cout<< endl;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Bst To Doubly Linked List
 */
int main(){
    Node* root= CreateTree();
    levelorderTraversal(root);
    Node* head= NULL;
    converttoDLL(root, head);

}
