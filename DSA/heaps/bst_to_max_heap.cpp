/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : bst_to_max_heap.cpp
 * PROBLEM  : Bst To Max Heap
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : Build heap; repeatedly extract min/max.
 * COMPLEX  : Time: O(n log k)  |  Space: O(n)
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
 * InsertIntoBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root, int data
 * Returns : Node*
 */
Node* InsertIntoBST(Node* root, int data){
    if(root== NULL){
        root= new Node(data);
        return root;
    }
    if(root-> data> data){
        root-> right= InsertIntoBST(root-> right, data);
    }
    if(root-> data< data){
        root-> left= InsertIntoBST(root-> left, data);
    }
    return root;

}


/*
 * CreateBST()
 * Purpose : Use BST property: left < root < right.
 * Params  : Node* root
 * Returns : void
 */
void CreateBST(Node* root){
    int data;
    cout<< "enter data"<< endl;
    cin>> data;
    while(data!= -1){
        root = InsertIntoBST(root, data);
        cout<< "Enter data"<< endl;
        cin>> data;
    }
}


/*
 * levelordertraversal()
 * Purpose : priority_queue for O(log n) min/max access.
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
            cout<< newnode-> data<< endl;
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
 * main()
 * Purpose : Entry point — demo/test for Bst To Max Heap
 */
int main(){
    Node* root= NULL;
}
