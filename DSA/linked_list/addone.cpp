/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : addone.cpp
 * PROBLEM  : Addone
 * LEETCODE : 369 — Plus One Linked List
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Node* pointers; handle empty and single-node cases.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ADD ONE TO NUMBER (LINKED LIST) — reverse, add carry, reverse back
// ────────────────────────────────────────────────────────────────────────────
// MSB head pe hai — reverse karke LSB se +1/carry
// carry handle karke wapas reverse — original order restore
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

// ── traversal: list print ──────────────────────────────────────────────────
void traversal(Node *&head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << endl;
}

// ── insertathead: head pe insert ─────────────────────────────────────────────
void insertathead(Node *&head, Node *&tail, int data) {
    if (head == NULL) {
        Node *newnode = new Node(data);
        head = newnode;
        tail = newnode;
    } else {
        Node *newnode = new Node(data);
        newnode->next = head;
        head = newnode;
    }
}

// ── reversal: recursive list reverse ─────────────────────────────────────────
void reversal(Node *&head, Node *&prev, Node *&current) {
    if (current == NULL) {
        head = prev;
        return;
    }
    Node *temp = current->next;
    current->next = prev;                  // link reverse
    reversal(head, current, temp);
}

// ── addonetoLL: 9-chain special case +1 ────────────────────────────────────
void addonetoLL(Node *&head, Node *&prev, Node *&current) {
    reversal(head, prev, current);
    Node *ptr = head;
    while (ptr != NULL) {
        if (ptr->data == 9) {
            if (ptr->next == NULL) {
                Node *newnode = new Node(1);
                ptr->next = newnode;
                ptr->data = 0;
                ptr = ptr->next;
                break;
            }
            ptr->data = 0;
            ptr = ptr->next;
        } else {
            ptr->data = ptr->data + 1;
            break;
        }
    }
    prev = NULL;
    current = head;
    reversal(head, prev, current);         // wapas reverse — MSB head pe
}

// ── addone: general carry-based +1 ───────────────────────────────────────────
//   1) reverse list
//   2) LSB se carry=1 add, digit%10, carry/10
//   3) last pe carry bache → new node
//   4) reverse back
void addone(Node *&head, Node *&prev, Node *&current) {
    reversal(head, prev, current);
    Node *temp = head;
    int carry = 1;
    while (temp != NULL) {
        int totalsum = temp->data + carry;
        int digit = totalsum % 10;
        carry = totalsum / 10;
        temp->data = digit;
        if (carry == 1 && temp->next == NULL) {
            Node *newnode = new Node(carry);
            temp->next = newnode;          // carry node — end pe link
            break;
        }
        if (carry == 0) {
            break;
        }
        temp = temp->next;
    }
    prev = NULL;
    current = head;
    reversal(head, prev, current);
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    insertathead(head, tail, 9);
    insertathead(head, tail, 9);
    insertathead(head, tail, 9);
    insertathead(head, tail, 9);
    Node *current = head;
    Node *prev = NULL;
    addone(head, prev, current);
    traversal(head);
}
