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
 * inorder()
 * Purpose : Tree DFS in specific visit order.
 * Params  : Node* root, vector<int>&ans
 * Returns : void
 */
void inorder(Node* root, vector<int>&ans){
    if(root== NULL){
        return;
    }
    inorder(root-> left, ans);
    ans.push_back(root-> data);
    inorder(root-> right, ans);
}



/*
 * twosum()
 * Purpose : Exploit sorted BST property for O(h) operations.
 * Params  : Node* root, int sum, vector<int>&ans
 * Returns : bool
 */
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


/*
 * main()
 * Purpose : Entry point — demo/test for Two Sum Bst
 */
int main(){
    Node* root= NULL;
    int sum=78;
    vector<int>ans;
    inorder(root, ans);
    bool final= twosum(root, sum, ans);
    cout<< final<< endl;

}
