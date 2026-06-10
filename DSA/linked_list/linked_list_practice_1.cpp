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

// ════════════════════════════════════════════════════════════════════════════
// LINKED LIST PRACTICE — insert, reverse, add-one operations
// ────────────────────────────────────────────────────────────────────────────
// head pointer se chain manage; next pointers link nodes
// reverse: iterative prev/current/temp pointer swap
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int data;
    Node *next;
    Node() {
        this->next = NULL;
    }
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }
};

// ── traversalLL: iterative print ───────────────────────────────────────────
void traversalLL(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << "-> ";
        temp = temp->next;
    }
}

// ── traversal: recursive print ─────────────────────────────────────────────
void traversal(Node *head) {
    if (head == NULL) {
        return;
    }
    cout << head->data << "-> ";
    traversal(head->next);
}

// ── numofnodes: node count ─────────────────────────────────────────────────
int numofnodes(Node *head) {
    Node *temp = head;
    int count = 1;
    while (temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

// ── insertatstart: head ke aage insert ─────────────────────────────────────
void insertatstart(Node *&head, int data) {
    Node *newnode = new Node(data);
    if (head == NULL) {
        head = newnode;
    } else {
        newnode->next = head;              // purana head link
        head = newnode;
    }
}

// ── insertatend: tail ke peeche insert ─────────────────────────────────────
void insertatend(Node *&head, int data) {
    Node *ptr = head;
    Node *newnode = new Node(data);
    if (head == NULL) {
        head = newnode;
    } else {
        while (ptr->next != NULL) {
            ptr = ptr->next;               // last node tak jao
        }
        ptr->next = newnode;               // tail link — next pointer set
        newnode->next = NULL;
    }
}

// ── insertatposition: kisi index pe insert ─────────────────────────────────
void insertatposition(Node *&head, int index, int data) {
    if (index == 1) {
        insertatstart(head, data);
        return;
    } else if (index < 1) {
        cout << "invalid position" << endl;
        return;
    } else if (head == NULL) {
        Node *newnode = new Node(data);
        head = newnode;
    } else if (index == numofnodes(head) + 1) {
        insertatend(head, data);
    } else {
        Node *newnode = new Node(data);
        Node *ptr = head;
        int i = 1;
        while (i != index - 1) {
            ptr = ptr->next;
            i++;
        }
        newnode->next = ptr->next;         // naya node beech mein link
        ptr->next = newnode;
    }
}

// ── reversal: iterative reverse ──────────────────────────────────────────────
//   1) prev=NULL, current=head
//   2) temp=current->next; current->next=prev
//   3) prev=current, current=temp; head=prev
void reversal(Node *&head) {
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL) {
        Node *temp = current->next;        // next save — link break se pehle
        current->next = prev;              // pointer reverse
        prev = current;
        current = temp;
    }
    head = prev;                           // naya head
}

// ── addone: reverse-add-reverse +1 ─────────────────────────────────────────
void addone(Node *&head) {
    reversal(head);
    int carry = 0;
    Node *temp = head;
    while (temp != NULL) {
        temp->data = temp->data + 1;
        carry = 0;
        if (temp->data > 9) {
            temp->data = 0;
            carry = 1;
        }
        if (carry == 0) {
            break;
        } else {
            if (temp->next == NULL) {
                break;
            } else {
                temp = temp->next;
            }
        }
    }
    if (carry != 0) {
        Node *newnode = new Node(1);
        temp->next = newnode;
        newnode->next = NULL;
    }
}

// ── addonell: carry-based +1 variant ─────────────────────────────────────────
void addonell(Node *&head) {
    reversal(head);
    Node *temp = head;
    int carry = 1;
    while (temp != NULL) {
        temp->data += carry;
        int digit = (temp->data) % 10;
        carry = (temp->data) / 10;
        temp->data = digit;
        if (carry == 0) {
            break;
        }
        if (temp->next == NULL && carry != 0) {
            break;
        }
        temp = temp->next;
    }
    if (carry != 0) {
        Node *newnode = new Node(1);
        temp->next = newnode;
        newnode->next = NULL;
    }
}

int main() {
    Node *first = new Node(9);
    Node *second = new Node(9);

    Node *head = first;

    first->next = second;

    traversal(head);
    addonell(head);
    reversal(head);
    cout << endl;
    traversal(head);

    cout << endl;
}
