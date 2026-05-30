/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : lca_in_bst.cpp
 * PROBLEM  : Lca In Bst
 * LEETCODE : 235 — Lowest Common Ancestor of a BST
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
 * LCABST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, Node* p, Node* q
 * Returns : Node*
 */
Node* LCABST(Node* root, Node* p, Node* q){
    if(root== NULL){
        return NULL;
    }
    if(root== p){
        return p;
    }
    if(root== q){
        return q;
    }
    if(root!= p && root!= q){
        if((p-> data< root-> data && q-> data> root-> data)|| (p-> data> root-> data && q-> data< root-> data)){
            return root;
        }
        else if(p-> data< root-> data && q-> data< root-> data){
            return LCABST(root-> left, p,q);
        }
        else {
            return LCABST(root-> right, p, q);
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Lca In Bst
 */
int main(){
    Node* root= NULL;
    takeInput(root);
    cout<< "level order traversal is: "<< endl;
    levelordertraversal(root);
    cout<< endl;
}
