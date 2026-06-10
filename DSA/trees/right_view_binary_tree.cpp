/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : right_view_binary_tree.cpp
 * PROBLEM  : Right View Binary Tree
 * LEETCODE : 199 — Binary Tree Right Side View
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// RIGHT VIEW — Tree ko right se dekho, har level ka pehla node
// ────────────────────────────────────────────────────────────────────────────
// Problem: Right side se tree dikhe to har level ka sabse aage wala node?
//
// Approach 1: BFS — har level ka last node print
// Approach 2: DFS — right pehle jao, level == ans.size() pe push
//
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

// ── CreateTree: DFS input se tree banao ──
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

// ── levelordertraversal: level-wise print ──
//   1) Queue + NULL separator
//   2) Har node print, children push
//   3) NULL pe newline
void levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode!= NULL){
            cout<< newnode-> data;
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

// ── levelleftview: BFS se left view (har level ka pehla) ──
//   1) Pehle level ka front print
//   2) NULL marker pe agle level ka front print
void levelleftview(Node* root){
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
                q.push(NULL);
                cout<< q.front()-> data<< endl;  // nayi level ka pehla node
            }
        }
    }
}

// ── leftviewrecursion: DFS left pehle, level track ──
//   1) NULL return
//   2) Agar level == vector size → pehli baar is level pe → push
//   3) Left pehle, phir right (left view ke liye)
void leftviewrecursion(Node* root, vector<int>&left, int level){
    if(root== NULL){
        return;
    }
    if(left.size()== level){
        left.push_back(root-> data);
    }
    leftviewrecursion(root-> left, left,level+1);
    leftviewrecursion(root-> right, left,level+1);
}

// ── rightviewrecursion: DFS right pehle ──
//   1) NULL return
//   2) level == right.size() → is level ka rightmost node
//   3) Right subtree pehle visit (right view ke liye)
void rightviewrecursion(Node* root, vector<int>&right, int level){
    if(root== NULL)
{
    return;
}
    if(right.size()== level){
        right.push_back(root-> data);
    }
    rightviewrecursion(root-> right, right, level+1);  // right pehle
    rightviewrecursion(root-> left, right, level+1);
}

// ── main: right view print karo ──
int main(){
    Node* root= CreateTree();
    vector<int>right;
    int level=0;
    rightviewrecursion(root, right, level);
    for(int i=0; i<right.size(); i++){
        cout<< right[i]<< " ";
    }
}
