/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : add_two_linked_lists.cpp
 * PROBLEM  : Add Two Linked Lists
 * LEETCODE : 2 — Add Two Numbers
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;
class Node{
    public:
    int data;
    Node* next;
    Node(){
        this-> data= 0;
        this-> next= NULL;
    }
    Node(int data){
        this-> data= data;
        this-> next= NULL;
    }
};


/*
 * insertathead()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail, int data
 * Returns : void
 */
void insertathead(Node* &head, Node* &tail, int data){
    
}


/*
 * main()
 * Purpose : Entry point — demo/test for Add Two Linked Lists
 */
int main(){
    Node* head= NULL;
    Node* tail= NULL;
}
