/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : top_view_binary_tree.cpp
 * PROBLEM  : Top View Binary Tree
 * LEETCODE : 314 — Binary Tree Vertical Order Traversal
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <map>
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
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Returns : Node*
 */
Node* CreateTree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data==-1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= CreateTree();
    root-> right= CreateTree();
    return root;
}


/*
 * topview()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void topview(Node* root){
    map<int,int>distNode;
    queue<pair<Node*,int>>q;
    q.push(make_pair(root,0));
    while(!q.empty()){
        pair<Node*,int> temp = q.front();
        q.pop();
        Node* frontNode = temp.first;
        int level= temp.second;
        if(distNode.find(level)== distNode.end()){
            distNode[level]= frontNode-> data;
        }
        if(frontNode-> left!= NULL){
            q.push(make_pair(frontNode-> left, level-1));
        }
        if(frontNode-> right!= NULL){
            q.push(make_pair(frontNode-> right, level+1));
        }
    }
    cout<< "Top view"<< endl;
    for(auto i: distNode){
        cout<< i.second<< " ";
    }
}


/*
 * bottomview()
 * Purpose : Recursive DFS; base case when node == nullptr.
 * Params  : Node* root
 * Returns : void
 */
void bottomview(Node* root){
    map<int, int>distNode;
    queue<pair<Node*, int>>q;
    q.push(make_pair(root,0));
    while(!q.empty()){
        pair<Node*, int>temp= q.front();
        q.pop();
        Node* frontNode= temp.first;
        int level= temp.second;
        distNode[level]= frontNode-> data;
        if(frontNode-> left!= NULL){
            q.push(make_pair(frontNode-> left, level-1));
        }
        if(frontNode-> right!= NULL){
            q.push(make_pair(frontNode-> right, level+1));
        }
    }
    cout<< "Bottom View"<< endl;
    for(auto i: distNode){
        cout<< i.second << " ";
    }        
}


/*
 * main()
 * Purpose : Entry point — demo/test for Top View Binary Tree
 */
int main(){
    Node* root= CreateTree();
    bottomview(root);
}
