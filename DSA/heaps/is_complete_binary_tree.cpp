/*
 * ============================================================================
 * TOPIC    : Heaps
 * FILE     : is_complete_binary_tree.cpp
 * PROBLEM  : Is Complete Binary Tree
 * ABOUT    : Min/max heap, priority queue, heap sort, k-th element
 * APPROACH : priority_queue for O(log n) min/max access.
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
};


/*
 * levelordertraversal()
 * Purpose : priority_queue for O(log n) min/max access.
 * Params  : Node* root
 * Returns : bool
 */
bool levelordertraversal(Node* root){
    queue<Node*>q;
    q.push(root);
    bool flag = false;
    while(!q.empty()){
        Node* newnode= q.front();
        q.pop();
        if(newnode== NULL){
            flag= true;
        }
        else {
            if(flag== true){
                return false;
            }
            q.push(newnode-> left);
            q.push(newnode-> right);
        }
    }
    return true;
}


/*
 * CheckCBT()
 * Purpose : priority_queue for O(log n) min/max access.
 * Params  : Node* root
 * Returns : bool
 */
bool CheckCBT(Node* root){
    levelordertraversal(root);


}
