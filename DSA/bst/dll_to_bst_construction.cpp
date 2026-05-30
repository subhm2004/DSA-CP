/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : dll_to_bst_construction.cpp
 * PROBLEM  : Dll To Bst Construction
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
 * DLLconversionBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* head, int n
 * Returns : Node*
 */
Node* DLLconversionBST(Node* head, int n){
    if(n<=0 || head== NULL){
        return NULL;
    }
    Node* lefttree= DLLconversionBST(head, (n/2)-1);
    Node* root= head;
    root-> left= lefttree;
    if(head!= NULL){
        head= head-> right;
    }
    
    root-> right= DLLconversionBST(head, n/2);
    return root;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Dll To Bst Construction
 */
int main(){

}
