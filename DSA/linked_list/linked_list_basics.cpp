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

// ════════════════════════════════════════════════════════════════════════════
// LINKED LIST BASICS — Node* pointers, traversal, insert at begin
// ────────────────────────────────────────────────────────────────────────────
// har node: data + next pointer; head = pehla node
// insert at begin: newnode->next = head, head = newnode
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int data;
    Node *next;                            // next pointer — agla node link
    Node() {
        cout << "this is default ctor" << endl;
        this->next = NULL;
    }
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// ── printll: iterative traversal ───────────────────────────────────────────
//   1) temp = head se start
//   2) temp!=NULL tak data print, temp = temp->next
void printll(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << "->";
        temp = temp->next;                 // pointer aage — next node
    }
    cout << endl;
}

// ── printingLL: recursive traversal ────────────────────────────────────────
//   1) base: head==NULL return
//   2) print data, recurse head->next
void printingLL(Node *head) {
    if (head == NULL) {
        return;
    }
    Node *temp = head;
    cout << temp->data << "-> ";
    printingLL(head->next);
}

// ── nodesinll: recursive node count ────────────────────────────────────────
int nodesinll(Node *head, int count) {
    if (head == NULL) {
        return count;
    }
    return nodesinll(head->next, count + 1);
}

// ── nodecount: iterative node count ────────────────────────────────────────
int nodecount(Node *head, int count) {
    Node *temp = head;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

// ── insertatbegin: head ke pehle naya node ─────────────────────────────────
//   1) new Node(data) banao
//   2) newnode->next = head (purana head link)
//   3) head = newnode (head update — reference se)
void insertatbegin(Node *&head, int data) {
    Node *newnode = new Node(data);
    Node *temp = head;
    if (temp == NULL) {
        temp = newnode;
    } else {
        newnode->next = temp;              // purana head naye ke next mein
    }
    head = newnode;                        // head pointer update
}

int main() {
    int data;
    Node *first = new Node(10);
    Node *second = new Node(20);
    Node *third = new Node(30);
    Node *fourth = new Node(40);
    Node *fifth = new Node(50);
    first->next = second;                  // link nodes — chain banao
    second->next = third;
    third->next = fourth;
    fourth->next = fifth;
    Node *head = first;
    cout << "enter data of newnode" << endl;
    cin >> data;
    insertatbegin(head, data);
    printingLL(head);
    cout << endl;
    return 0;
}
