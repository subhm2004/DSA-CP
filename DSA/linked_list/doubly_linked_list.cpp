/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : doubly_linked_list.cpp
 * PROBLEM  : Doubly Linked List
 * LEETCODE : 146 — LRU Cache (doubly linked list pattern)
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DOUBLY LINKED LIST — prev + next dono pointers
// ────────────────────────────────────────────────────────────────────────────
// insert: prev/next dono update karo — bidirectional links
// head/tail pointers se start/end track
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int data;
    Node *prev;                            // peeche wala node
    Node *next;                            // aage wala node
    Node() {
        cout << "default ctor called" << endl;
        this->data = 0;
        this->prev = NULL;
        this->next = NULL;
    }
    Node(int data) {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
        cout << "parameterised ctor for " << this->data << endl;
    }
};

// ── doublyll: forward traversal print ──────────────────────────────────────
void doublyll(Node *&head, Node *&tail) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << "-> ";
        temp = temp->next;                 // next pointer se aage
    }
    cout << endl;
}

// ── numofnodes: count nodes ────────────────────────────────────────────────
int numofnodes(Node *&head, Node *&tail) {
    Node *temp = head;
    int count = 1;
    while (temp->next != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ── insertdoublyll: index pe insert (prev/next update) ─────────────────────
//   1) index==1 → head pe, newnode->next=head, head->prev=newnode
//   2) index==end → tail ke peeche, tail->next=newnode
//   3) middle → temp/ptr se position, 4 pointers update
void insertdoublyll(Node *&head, Node *&tail, int &index, int &data) {
    if (index < 1 || index > numofnodes(head, tail) + 1) {
        cout << "Invalid index for insertion" << endl;
    } else if (index == 1) {
        Node *newnode = new Node(data);
        if (head == NULL) {
            head = newnode;
        } else {
            newnode->next = head;
            head->prev = newnode;          // bidirectional link — prev set
            head = newnode;
        }
    } else if (index == numofnodes(head, tail) + 1) {
        Node *newnode = new Node(data);
        if (tail == NULL) {
            tail = newnode;
        } else {
            tail->next = newnode;
            newnode->prev = tail;          // tail se naye node ka prev
            tail = newnode;
        }
    } else {
        Node *newnode = new Node(data);
        Node *temp = head;
        Node *ptr = head->next;
        int i = 1;
        while (i != index - 1) {
            temp = temp->next;
            ptr = ptr->next;
            i++;
        }
        temp->next = newnode;
        newnode->prev = temp;              // beech mein insert — dono links
        ptr->prev = newnode;
        newnode->next = ptr;
    }
}

int main() {
    int index;
    cout << " enter the index to perform insertion " << endl;
    cin >> index;
    int data;
    cout << "enter data" << endl;
    cin >> data;
    Node *first = new Node(10);
    Node *second = new Node(20);
    Node *third = new Node(30);
    Node *fourth = new Node(40);
    Node *fifth = new Node(50);
    Node *head = first;
    Node *tail = fifth;
    first->next = second;
    second->next = third;
    second->prev = first;                  // doubly links banao
    third->next = fourth;
    third->prev = second;
    fourth->prev = third;
    fourth->next = fifth;
    fifth->prev = fourth;
    doublyll(head, tail);
    insertdoublyll(head, tail, index, data);
    doublyll(head, tail);
}
