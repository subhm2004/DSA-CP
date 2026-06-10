/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : palindrome_linked_list.cpp
 * PROBLEM  : Palindrome Linked List
 * LEETCODE : 234 — Palindrome Linked List
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Two pointers from both ends or recursive check.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// PALINDROME LINKED LIST — middle se split, reverse, compare
// ────────────────────────────────────────────────────────────────────────────
// slow/fast se middle dhundho; second half reverse
// dono halves compare — sab match → palindrome
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int data;
    Node *next;
    Node() {
        this->data = 0;
        this->next = NULL;
    }
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// ── midnode: slow/fast se middle node ──────────────────────────────────────
//   1) slow=head, fast=head
//   2) fast 2 step, slow 1 step
//   3) fast end → slow = middle
Node *midnode(Node *&head, Node *&tail) {
    Node *slow = head;
    Node *fast = head;
    while (fast->next != NULL) {
        fast = fast->next;
        if (fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;             // slow pointer — middle track
        }
    }
    return slow;
}

// ── reversell: recursive second half reverse ───────────────────────────────
//   1) base: current==NULL → head2=prev
//   2) temp=current->next save
//   3) current->next=prev (link reverse)
void reversell(Node *prev, Node *current, Node *&head2) {
    if (current == NULL) {
        head2 = prev;
        return;
    }
    Node *temp = current->next;            // next pointer save karo
    current->next = prev;                  // link ulta — prev ki taraf
    reversell(current, temp, head2);
}

// ── comparell: dono halves compare ─────────────────────────────────────────
void comparell(Node *&head, Node *&head2) {
    Node *ptr1 = head;
    Node *ptr2 = head2;
    while (head != NULL && head2 != NULL) {
        if (ptr1->data == ptr2->data) {
            ptr1 = ptr1->next;             // dono pointers aage
            ptr2 = ptr2->next;
        } else {
            cout << false;
        }
    }
    cout << true;
}

// ── traversal: list print ──────────────────────────────────────────────────
void traversal(Node *&head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

// ── insertathead: head pe insert ───────────────────────────────────────────
void insertathead(Node *&head, Node *&tail, int data) {
    if (head == NULL) {
        Node *newnode = new Node(data);
        head = newnode;
        tail = newnode;
    } else {
        Node *newnode = new Node(data);
        newnode->next = head;              // naya node head se link
        head = newnode;
    }
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    insertathead(head, tail, 1);
    insertathead(head, tail, 2);
    insertathead(head, tail, 3);
    insertathead(head, tail, 3);
    insertathead(head, tail, 2);
    insertathead(head, tail, 1);
    traversal(head);
    Node *middle = midnode(head, tail);
    cout << middle->data << endl;
    Node *head2 = middle->next;
    middle->next = NULL;                   // list split — first half alag
    Node *prev = NULL;
    Node *current = head2;
    reversell(prev, current, head2);
    traversal(head2);
    comparell(head, head2);
}
