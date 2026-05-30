/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_basics.cpp
 * PROBLEM  : Binary Tree Basics
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
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
    cout<< "Enter the data of node"<< endl;
    cin>> data;
    if(data== -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;

}


/*
 * preorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root
 * Returns : void
 */
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    cout<< root-> data<< "->";
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
    cout<< root-> data<< "->";
    inorder(root->right);
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
    cout<< root-> data<< "->";
}
queue<Node*>q;


/*
 * levelorder()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void levelorder(Node* root){
    q.push(root);
    while(!q.empty()){
        cout << root-> data << "->";
             q.push(root->left);
            q.push(root->right);
        q.pop();
        root = q.front();
    }
}


/*
 * levelordertraversal()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void levelordertraversal(Node* root){
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data<< "->";
            if(newnode-> left!= NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
        else{
            cout<< endl;
            if(!q.empty()){
                q.push(NULL);

            }
        }
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Binary Tree Basics
 */
int main(){
    Node* root = CreateTree();
    levelordertraversal(root);

}
