/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : left_view_binary_tree.cpp
 * PROBLEM  : Left View Binary Tree
 * LEETCODE : 199 — Binary Tree Right Side View (mirror pattern)
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LEFT VIEW — Tree ko left se dekho, har level ka pehla node
// ────────────────────────────────────────────────────────────────────────────
// Problem: Left side se dikhe to har depth ka sabse aage wala node?
//
// Approach: BFS (har level ka first) ya DFS (left pehle, level track)
// Complexity: Time O(n)  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

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

// ── Createtree: recursive build ──
Node* Createtree(){
    int data;
    cout<< "Enter data"<< endl;
    cin>> data;
    if(data == -1){
        return NULL;
    }
    Node* root= new Node(data);
    root-> left= Createtree();
    root-> right= Createtree();
    return root;
}

// ── levelordertraversal: BFS left view ──
//   1) Har level ka pehla node print (NULL marker se)
void levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    cout<< q.front()-> data<< endl;
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            if(newnode-> left!= NULL){
                q.push(newnode-> left);
            }
            if(newnode-> right!= NULL){
                q.push(newnode-> right);
            }
        }
        else { 
            if(!q.empty()){
                cout<< q.front()-> data<< endl;
                q.push(NULL);
            }
        }
    }
}

// ── printleftview: DFS left pehle ──
//   1) level == leftview.size() → pehli baar is depth pe
//   2) Left subtree pehle, phir right
void printleftview(Node* root, vector<int>&leftview, int level){
    if(root == NULL){
        return;
    }
    if(level== leftview.size()){
        leftview.push_back(root-> data);  
    }
    printleftview(root-> left, leftview, level+1);
    printleftview(root-> right, leftview, level+1);
}

// ── printrightview: DFS right pehle (comparison) ──
void printrightview(Node* root, vector<int>&right, int level){
    if(root== NULL){
        return;
    }
    if(right.size()== level){
        right.push_back(root-> data);
    }
    printrightview(root-> right, right, level+1);
    printrightview(root-> left, right, level+1);
}

// ── main: right view print (file me right view demo hai) ──
int main(){
    Node* root= Createtree();
    int level=0;
    vector<int>right;
    printrightview(root, right,level);
    for(int i=0; i<right.size(); i++){
        cout<< right[i]<< " ";
    }
}
