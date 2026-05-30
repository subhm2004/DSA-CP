/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : start_ofloop.cpp
 * PROBLEM  : Start Ofloop
 * LEETCODE : 142 — Linked List Cycle II
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Floyd's slow/fast pointers detect cycle.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <map>
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
 * loopstarting()
 * Purpose : Floyd's slow/fast pointers detect cycle.
 * Params  : Node* &head
 * Returns : int
 */
int loopstarting (Node* &head){
    map< Node*, bool> table;
    Node* temp= head;
    while(temp!= NULL){
        if(table[temp]== false){
            table[temp]= true;
        }
        else {
            return temp-> data;
        }
        temp= temp-> next;
    }
    return -1;
}


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
 * insertattail()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail, int data
 * Returns : void
 */
void insertattail(Node* &head, Node* &tail, int data){
    if(head== NULL){
        Node* newnode= new Node(data);
        head= newnode;
        tail= newnode;
    }
    else {
        Node* newnode= new Node(data);
        tail-> next= newnode;
        tail = newnode;
    }

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
 * checkloop()
 * Purpose : Floyd's slow/fast pointers detect cycle.
 * Params  : Node* &head
 * Returns : bool
 */
bool checkloop(Node* &head){
    Node* slow= head;
    Node* fast= head;
    while(fast!= NULL){
        fast= fast-> next;
        if(fast!= NULL){
            fast= fast-> next;
            slow= slow-> next;
        }
        if(fast== slow){
            return true;
        }
    }
    return false;
}


/*
 * startingpoint()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head
 * Returns : Node*
 */
Node* startingpoint(Node* &head){
    Node* slow= head;
    Node* fast= head;
    while(fast!= NULL){
        fast= fast-> next;
        if(fast!= NULL){
            fast = fast-> next;
            slow = slow-> next;
        }
        if(fast == slow){
            break;
        }
    }
    if(fast == NULL){
        return  NULL;
    }
    slow = head;
    while(fast != slow){
        slow= slow-> next;
        fast= fast-> next;
    }
    return slow;
}


/*
 * removeloop()
 * Purpose : Floyd's slow/fast pointers detect cycle.
 * Params  : Node* &head
 * Returns : void
 */
void removeloop(Node* &head){
    Node* slow= head;
    Node* fast= head;
    while(fast!= NULL){
        fast= fast-> next;
        if(fast!= NULL){
            fast= fast-> next;
            slow= slow-> next;
        }
        if(fast== slow){
            break;
        }
    }
    if(fast== NULL){
        cout<< "NO LOOP PRESENT"<< endl;
    }
    slow= head;
    while(slow-> next!= fast-> next){
        slow= slow-> next;
        fast= fast-> next;
    }
    fast-> next = NULL;
    cout<< "loop removed"<< endl;
}


/*
 * main()
 * Purpose : Entry point — demo/test for Start Ofloop
 */
int main(){
    Node* head = NULL;
    Node* tail= NULL;
    insertathead(head,tail,12);
    insertathead(head,tail,10);
    insertathead(head,tail,8);
    insertathead(head,tail,6);
    insertathead(head,tail,4);
    insertathead(head,tail,2);
    traversal(head);
    tail-> next= head-> next-> next-> next;
    cout<< startingpoint(head)-> data<< endl;
    removeloop(head);
    traversal(head);

}
