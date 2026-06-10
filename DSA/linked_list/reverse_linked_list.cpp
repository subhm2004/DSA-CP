/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : reverse_linked_list.cpp
 * PROBLEM  : Reverse Linked List
 * LEETCODE : 206 — Reverse Linked List
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Swap from both ends or reverse links iteratively.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// REVERSE LINKED LIST — recursive pointer reversal
// ────────────────────────────────────────────────────────────────────────────
// current->next = prev; prev/current aage badhao
// base pe head = prev (naya head)
// ════════════════════════════════════════════════════════════════════════════

class ListNode {
public:
    int data;
    ListNode *next;
    ListNode() {
        this->data = 0;
        this->next = NULL;
    }
    ListNode(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// ── traversal: list print ──────────────────────────────────────────────────
void traversal(ListNode *&head) {
    ListNode *temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

// ── insertathead: head pe naya node ──────────────────────────────────────────
void insertathead(ListNode *&head, ListNode *&tail, int data) {
    if (head == NULL) {
        ListNode *newnode = new ListNode(data);
        head = newnode;
        tail = newnode;
    } else {
        ListNode *newnode = new ListNode(data);
        newnode->next = head;
        head = newnode;
    }
}

// ── reversal: recursive reverse ────────────────────────────────────────────
//   1) base: current==NULL → head=prev
//   2) temp = current->next save
//   3) current->next = prev (link reverse)
//   4) recurse with prev=current, current=temp
void reversal(ListNode *prev, ListNode *current, ListNode *&head, ListNode *&tail) {
    if (current == NULL) {
        head = prev;                       // naya head — last node
        return;
    }
    ListNode *temp = current->next;        // next pointer bachao
    current->next = prev;                  // link ulta karo
    reversal(current, temp, head, tail);
}

int main() {
    ListNode *head = NULL;
    ListNode *tail = NULL;
    insertathead(head, tail, 12);
    insertathead(head, tail, 10);
    insertathead(head, tail, 8);
    insertathead(head, tail, 6);
    insertathead(head, tail, 4);
    insertathead(head, tail, 2);
    traversal(head);
    ListNode *prev = NULL;
    ListNode *current = head;
    reversal(prev, current, head, tail);
    traversal(head);
}
