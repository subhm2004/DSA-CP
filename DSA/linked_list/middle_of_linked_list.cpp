/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : middle_of_linked_list.cpp
 * PROBLEM  : Middle Of Linked List
 * LEETCODE : 876 — Middle of the Linked List
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

};


/*
 * checkloop()
 * Purpose : Floyd's slow/fast pointers detect cycle.
 * Params  : Node* head
 * Returns : bool
 */
bool checkloop(Node* head){
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
 * Params  : Node* head
 * Returns : Node*
 */
Node* startingpoint(Node* head){
    Node* fast= head;
    Node* slow= head;
    while(fast!= NULL){
        fast= fast-> next;
        if(fast!= NULL){
            fast = fast-> next;
            slow = slow-> next;
        }
        if(fast == slow){
            fast = head;
            while(fast!= slow){
                fast= fast-> next;
                slow= slow-> next;
            }
            Node* start= slow;
           
        }
    }
}



/*
 * main()
 * Purpose : Entry point — demo/test for Middle Of Linked List
 */
int main(){
    
}
