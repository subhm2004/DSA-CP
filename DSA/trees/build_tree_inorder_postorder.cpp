/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : build_tree_inorder_postorder.cpp
 * PROBLEM  : Build Tree Inorder Postorder
 * LEETCODE : 106 — Construct Binary Tree from Inorder and Postorder
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Tree DFS in specific visit order.
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
 * levelordertraversal()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode = q.front();
        q.pop();
        if(newnode== NULL){
            cout<< endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else {
            if(newnode-> left != NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
    }
}


/*
 * searchpostorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : int inorder[], int size, int target
 * Returns : int
 */
int searchpostorder(int inorder[], int size, int target){
    // Iterate over all elements
    for(int i=0; i< size; i++){
        if(inorder[i]== target){
            return i;
        }
    }
    return -1;
}


/*
 * inpostcreatetree()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : int postorder[], int inorder[], int size, int &post_index, int inorder_start, int inorder_end
 * Returns : Node*
 */
Node* inpostcreatetree(int postorder[], int inorder[], int size, int &post_index, int inorder_start, int inorder_end){
    if(post_index <0 || inorder_start> inorder_end){
        return NULL;
    }
    int element= postorder[post_index];
    post_index--;
    Node* root = new Node(element);
    int position= searchpostorder(inorder,size,element);
    root-> right= inpostcreatetree(postorder, inorder, size, post_index, position +1, inorder_end);
    root-> left= inpostcreatetree(postorder,inorder,size,post_index,inorder_start, position-1);
    return root;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Build Tree Inorder Postorder
 */
int main(){
    int postorder[]= {8,6,12,4,10,2};
    int inorder[]= {8,12,6,2,10,4};
    int size= 6;
    int post_index= size-1;
    int inorder_start= 0;
    int inorder_end= size-1;
    Node* root= inpostcreatetree(postorder,inorder,size,post_index,inorder_start,inorder_end);
    levelordertraversal(root);
}
