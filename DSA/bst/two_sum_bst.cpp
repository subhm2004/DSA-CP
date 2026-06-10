/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : two_sum_bst.cpp
 * PROBLEM  : Two Sum Bst
 * LEETCODE : 653 — Two Sum IV - Input is a BST
 * ABOUT    : Binary Search Tree — create, traverse, search, delete, convert
 * APPROACH : Hash map or two pointers to find pair with target sum.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TWO SUM IN BST — Koi do values ka sum = target?
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST me do nodes ki values ka sum target ke barabar hai?
//
// Approach: Inorder → sorted array → two pointers
//   - i=0, j=n-1; sum compare karke move
//
// Complexity: Time O(n)  |  Space O(n) array
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

// ── CreateBST: insert ──
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

// ── takeInput: loop insert ──
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

// ── levelordertraversal: BFS ──
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

// ── inorder: sorted array me values collect ──
//   1) Left → push root → right
//   2) BST inorder = sorted order
void inorder(Node* root, vector<int>&ans){
    if(root== NULL){
        return;
    }
    inorder(root-> left, ans);
    ans.push_back(root-> data);
    inorder(root-> right, ans);
}

// ── twosum: two pointers on sorted array ──
//   1) i=0, j=last
//   2) sum == target → true
//   3) sum < target → i++ (bada chahiye)
//   4) sum > target → j-- (chhota chahiye)
bool twosum(Node* root, int sum, vector<int>&ans){
    if(root== NULL){
        return false;
    }
    int i=0;
    int j= ans.size()-1;
    while(i<j){
        if(ans[i]+ ans[j]== sum){
            return true;
        }
        else if(ans[i]+ ans[j]< sum){
            i++;
        }
        else {
            j--;
        }
    }
    return false;
}

// ── main: two sum check demo ──
int main(){
    Node* root= NULL;
    int sum=78;
    vector<int>ans;
    inorder(root, ans);
    bool final= twosum(root, sum, ans);
    cout<< final<< endl;
}
