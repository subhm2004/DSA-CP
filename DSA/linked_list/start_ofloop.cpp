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

// ════════════════════════════════════════════════════════════════════════════
// CYCLE DETECTION & REMOVAL — Floyd's tortoise-hare + hash map variant
// ────────────────────────────────────────────────────────────────────────────
// slow 1 step, fast 2 step — meet → cycle hai
// phase 2: slow=head, dono 1 step → cycle start
// remove: slow/fast next pointers align karke loop tod do
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

// ── loopstarting: hash map se cycle start dhundho ──────────────────────────
int loopstarting(Node *&head) {
    map<Node *, bool> table;
    Node *temp = head;
    while (temp != NULL) {
        if (table[temp] == false) {
            table[temp] = true;
        } else {
            return temp->data;             // pehle visit — cycle start
        }
        temp = temp->next;
    }
    return -1;
}

// ── insertathead: head pe insert ───────────────────────────────────────────
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

// ── insertattail: tail pe insert ───────────────────────────────────────────
void insertattail(Node *&head, Node *&tail, int data) {
    if (head == NULL) {
        Node *newnode = new Node(data);
        head = newnode;
        tail = newnode;
    } else {
        Node *newnode = new Node(data);
        tail->next = newnode;              // tail ka next — cycle banane ke liye
        tail = newnode;
    }
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

// ── checkloop: Floyd's — cycle hai ya nahi? ────────────────────────────────
bool checkloop(Node *&head) {
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;             // fast 2 step — hare
            slow = slow->next;             // slow 1 step — tortoise
        }
        if (fast == slow) {
            return true;                   // meet → cycle confirmed
        }
    }
    return false;
}

// ── startingpoint: cycle entry node dhundho ────────────────────────────────
//   1) slow/fast se meeting point
//   2) slow = head; dono 1-1 step
//   3) meet = cycle start node
Node *startingpoint(Node *&head) {
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        if (fast == slow) {
            break;
        }
    }
    if (fast == NULL) {
        return NULL;
    }
    slow = head;                           // phase 2 — head se start
    while (fast != slow) {
        slow = slow->next;
        fast = fast->next;                 // dono 1 step — entry pe milenge
    }
    return slow;
}

// ── removeloop: cycle tod do ───────────────────────────────────────────────
void removeloop(Node *&head) {
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        if (fast == slow) {
            break;
        }
    }
    if (fast == NULL) {
        cout << "NO LOOP PRESENT" << endl;
    }
    slow = head;
    while (slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = NULL;                     // loop break — next pointer NULL
    cout << "loop removed" << endl;
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    insertathead(head, tail, 12);
    insertathead(head, tail, 10);
    insertathead(head, tail, 8);
    insertathead(head, tail, 6);
    insertathead(head, tail, 4);
    insertathead(head, tail, 2);
    traversal(head);
    tail->next = head->next->next->next;   // cycle create — tail se mid link
    cout << startingpoint(head)->data << endl;
    removeloop(head);
    traversal(head);
}
