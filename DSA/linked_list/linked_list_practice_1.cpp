/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : linked_list_practice_1.cpp
 * PROBLEM  : Linked List Practice 1
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
        this -> next = NULL;
    }
    Node(int data){
        this-> data= data;
        this-> next= NULL;
    }
};


/*
 * traversalLL()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : void
 */
void traversalLL(Node* head){
    Node* temp = head;
    while(temp!= NULL){
        cout<< temp-> data<< "-> ";
        temp= temp-> next;
    }
}


/*
 * traversal()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : void
 */
void traversal(Node* head){
    if(head== NULL){
        return;
    }
    cout<< head-> data<< "-> ";
    traversal(head->next);

}


/*
 * numofnodes()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : int
 */
int numofnodes(Node* head){
    Node* temp = head;
    int count =1;
    while(temp-> next!= NULL){
        temp= temp-> next;
        count++;
    }
    return count;
}


/*
 * insertatstart()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, int data
 * Returns : void
 */
void insertatstart(Node* &head, int data){
    Node* newnode = new Node(data);
    if(head == NULL){
        head= newnode;
    }
    else {
        newnode-> next= head;
        head= newnode;
    }
}


/*
 * insertatend()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, int data
 * Returns : void
 */
void insertatend(Node* &head, int data){
    Node* ptr= head;
    Node* newnode= new Node(data);
    if(head== NULL){
        head= newnode;
    }
    else{
         while(ptr-> next!=NULL){
        ptr= ptr-> next;
    }
    ptr-> next = newnode;
    newnode-> next= NULL;
    }
}


/*
 * insertatposition()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, int index, int data
 * Returns : void
 */
void insertatposition(Node* &head, int index, int data){
    if(index== 1){
        insertatstart(head,data);
        return;
    }
    else if(index < 1) {
        cout<< "invalid position"<< endl;
        return;
    }
    else if(head== NULL){
        Node* newnode= new Node(data);
        head= newnode;
    }
    else if(index== numofnodes(head)+1){
        insertatend(head,data);
    }
    else {
        Node* newnode = new Node(data);
        Node* ptr= head;
        int i=1;
        while(i!= index-1){
            ptr= ptr-> next;
            i++;
        }
        newnode-> next = ptr-> next;
        ptr -> next = newnode;
    }
}


/*
 * reversal()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* & head
 * Returns : void
 */
void reversal(Node* & head){
    Node* current= head;
    Node* prev= NULL;
    while(current!= NULL){
        Node* temp= current-> next;
        current-> next= prev;
        prev= current;
        current= temp;
    }
    head= prev;
}


/*
 * addone()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head
 * Returns : void
 */
void addone(Node* &head){
    reversal(head);
    int carry=0;
    Node* temp= head;
    while(temp!= NULL){
        temp-> data= temp-> data+1;
        carry=0;
        if(temp-> data >9){
            temp-> data=0;
            carry=1;
        }
        if(carry==0){
            break;
        }
        else{
            if(temp-> next == NULL){
                break;
            }
            else {
                temp= temp-> next;
            }
        }
    }
    if(carry!= 0){
        Node* newnode= new Node(1);
        temp-> next= newnode;
        newnode-> next= NULL;
    }
}


/*
 * addonell()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head
 * Returns : void
 */
void addonell(Node* &head){
    reversal(head);
    Node* temp= head;
    int carry= 1;
    while(temp!= NULL){
        temp-> data += carry;
        int digit= (temp-> data) %10;
        carry= (temp-> data)/10;
        temp-> data= digit;
        if(carry ==0){
            break;
        }
        if(temp-> next== NULL && carry != 0){
            break;
        }
        temp= temp-> next;   
    }
    if(carry != 0){
        Node* newnode= new Node(1);
        temp-> next= newnode;
        newnode-> next= NULL;
    }
}


/*
 * main()
 * Purpose : Entry point — demo/test for Linked List Practice 1
 */
int main(){
    Node* first = new Node(9);
    Node* second = new Node(9);
  
   
    Node* head= first;
   
    first-> next= second;
   
    traversal(head);
    addonell(head);
    reversal(head);
    cout<< endl;
    traversal(head);

    cout<< endl;
}
