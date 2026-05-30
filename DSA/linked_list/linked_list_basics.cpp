/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : linked_list_basics.cpp
 * PROBLEM  : Linked List Basics
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
    Node* next; // pointer of node* type
    Node(){ 
        cout<< "this is default ctor"<< endl;
        this-> next= NULL;
    }
    Node(int data){
        this-> data= data;
        this-> next= NULL;
    }
};


/*
 * printll()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : void
 */
void printll(Node* head){
    Node* temp= head;
    while(temp!=NULL){
        cout<< temp-> data<< "->";
        temp= temp-> next;
    }
    cout<< endl;
}


/*
 * printingLL()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : void
 */
void printingLL(Node* head){
    if(head==NULL){
        return;
    }
    Node* temp= head;
    cout<< temp->data<< "-> ";
    printingLL(head-> next);
}


/*
 * nodesinll()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node*head, int count
 * Returns : int
 */
int nodesinll(Node*head, int count){
    if(head==NULL){
        return count;
    }
    return nodesinll(head-> next, count+1);
}


/*
 * nodecount()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head, int count
 * Returns : int
 */
int nodecount(Node* head, int count){
    Node* temp= head;
    while(temp!=NULL){
        temp= temp-> next;
        count++;
    }
    return count;
}
void insertatbegin(Node* &head, int data){ // head is pass by refernce here
    Node* newnode= new Node(data);// nyi node bna li
    Node* temp = head;
    if(temp==NULL){
        temp = newnode;
    }
    else{
        newnode->next= temp;
    }
    head = newnode;   
}



/*
 * main()
 * Purpose : Entry point — demo/test for Linked List Basics
 */
int main(){
    int data;
    Node* first= new Node(10);
    Node* second= new Node(20);
    Node* third= new Node(30);
    Node* fourth= new Node(40);
    Node* fifth= new Node(50);
    first-> next= second;
    second-> next= third;
    third-> next= fourth;
    fourth-> next= fifth;
    Node* head= first;
    cout<< "enter data of newnode"<< endl;
    cin >> data;
    insertatbegin(head,data);
    printingLL(head);
    cout<< endl;
    return 0;
}
