/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : tortoise_algo.cpp
 * PROBLEM  : Tortoise Algo
 * LEETCODE : 141 — Linked List Cycle / 142 — Linked List Cycle II
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Floyd's slow/fast pointers detect cycle.
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
    if(head== NULL){
        Node* newnode= new Node(data);
        head= newnode;
        tail= newnode;
    }
    else{
        Node* newnode = new Node(data);
        newnode-> next= head;
        head= newnode;
    }
}


/*
 * midnode()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail
 * Returns : Node*
 */
Node* midnode(Node* &head, Node* &tail){
    Node* slow = head;
    Node* fast = head;
    while(fast!= NULL){
        fast= fast-> next;
        if(fast!= NULL){
            fast= fast-> next;
            slow= slow-> next;
        }
    }
    return slow;
}


/*
 * traversal()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head
 * Returns : void
 */
void traversal(Node* &head){
    Node* temp= head;
    while(temp!= NULL){
        cout<< temp-> data<< " -> ";
        temp= temp-> next;
    }
    cout << endl;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Tortoise Algo
 */
int main(){
    Node* head= NULL;
    Node* tail= NULL;
    insertathead(head,tail,12);
    insertathead(head,tail,10);
    insertathead(head,tail,8);
    insertathead(head,tail,6);
    insertathead(head,tail,4);
    insertathead(head,tail,2);
    traversal(head);
    Node* ans= midnode(head,tail);
    cout<< ans-> data<< endl;


    

}
