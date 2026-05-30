/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : linkedlistdelete.cpp
 * PROBLEM  : Linkedlistdelete
 * LEETCODE : 237 — Delete Node in a Linked List
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

class Node {
        public:
        int data;
        Node* next;

        Node() {
                this->data = 0;
                this->next = NULL;
        }
        Node(int data) {
                this->data = data;
                this->next = NULL;
        }

        ~Node() {
          cout << "Destructor called for: " << this->data << endl;
        }

};



/*
 * insertAtHead()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail, int data
 * Returns : void
 */
void insertAtHead(Node* &head, Node* &tail, int data) {
        if(head == NULL) {
                Node* newNode = new Node(data);
                head = newNode;
                tail = newNode;
        }
        else {
                Node* newNode = new Node(data);
                newNode -> next = head;
                head = newNode;
        }


}


/*
 * insertAtTail()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail, int data
 * Returns : void
 */
void insertAtTail(Node* &head,Node* &tail, int data) {
        if(head == NULL) {
                Node* newNode = new Node(data);
                head = newNode;
                tail = newNode;
                
        }
        else {
            Node* newNode = new Node(data);
            tail->next = newNode;
            tail = newNode;
        }

}


/*
 * print()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* head
 * Returns : void
 */
void print(Node* head) {

        Node* temp = head;
        while(temp != NULL) {
                cout << temp->data << "->";
                temp = temp->next;
        }
}



/*
 * findLength()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head
 * Returns : int
 */
int findLength(Node* &head ) {
        int len = 0;
        Node* temp = head;
        while(temp != NULL) {
                temp = temp->next;
                len++;
        }
        return len;
}



/*
 * insertAtPosition()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : int data, int position, Node* &head, Node* &tail
 * Returns : void
 */
void insertAtPosition(int data, int position, Node* &head, Node* &tail) {
        int len = findLength(head);
        
        if(position == 1) {
                insertAtHead(head, tail , data);
                return;
        }
        else if(position > len) {
                insertAtTail(head, tail, data);
                return;
        }
        else {
            Node* newNode = new Node(data);
            
            Node* prev = NULL;
            Node* curr = head;
            while(position != 1) {
                position--;
                prev = curr;
                curr = curr->next;
            }
            
            newNode -> next = curr;

            prev -> next = newNode;
            
        }
        
}



/*
 * deleteNode()
 * Purpose : Node* pointers; handle empty and single-node cases.
 * Params  : Node* &head, Node* &tail, int position
 * Returns : void
 */
void deleteNode(Node* &head, Node* &tail, int position) {
  if(head == NULL) {
    cout << "Cannot delete, coz LL is empty" << endl;
    return;
  }

  if(head == tail) {
    Node* temp = head;
    delete temp;
    head = NULL;
    tail = NULL;
    return;
  }

  int len = findLength(head);

  if(position == 1) {
    Node* temp = head;
    head = head->next;
    temp->next = NULL;
    delete temp;
  }
  else if(position == len) {

    Node* prev = head;
    while(prev -> next != tail ){
      prev = prev -> next;
    }

    prev -> next = NULL;

    delete tail;

    tail = prev;

  }
  else {

    Node* prev = NULL;
    Node* curr = head;
    while(position != 1) {
      position--;
      prev = curr;
      curr = curr->next;
    }

    prev->next = curr->next;

    curr->next = NULL;
    delete curr;

  }

}



/*
 * main()
 * Purpose : Entry point — demo/test for Linkedlistdelete
 */
int main() {

        Node* head = NULL;
        Node* tail = NULL;
        insertAtHead(head, tail,50);
        insertAtHead(head, tail,40);
        insertAtHead(head, tail,30);
        insertAtHead(head,tail, 20);
        insertAtHead(head, tail,10);

        print(head);
        cout << endl;
        

        deleteNode(head, tail, 3);
        print(head);
        cout << endl;




        return 0;
}
