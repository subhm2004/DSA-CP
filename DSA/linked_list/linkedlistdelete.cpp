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

// ════════════════════════════════════════════════════════════════════════════
// LINKED LIST DELETION — head/tail/middle position pe node delete
// ────────────────────────────────────────────────────────────────────────────
// prev/curr pointers se position pe jao; prev->next = curr->next
// head delete: head = head->next; tail delete: prev->next = NULL
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

    ~Node() {
        cout << "Destructor called for: " << this->data << endl;
    }
};

// ── insertAtHead: head pe naya node ────────────────────────────────────────
void insertAtHead(Node *&head, Node *&tail, int data) {
    if (head == NULL) {
        Node *newNode = new Node(data);
        head = newNode;
        tail = newNode;
    } else {
        Node *newNode = new Node(data);
        newNode->next = head;              // naya node purane head se link
        head = newNode;
    }
}

// ── insertAtTail: tail ke peeche insert ────────────────────────────────────
void insertAtTail(Node *&head, Node *&tail, int data) {
    if (head == NULL) {
        Node *newNode = new Node(data);
        head = newNode;
        tail = newNode;
    } else {
        Node *newNode = new Node(data);
        tail->next = newNode;              // tail ka next — naya node link
        tail = newNode;
    }
}

// ── print: iterative traversal ─────────────────────────────────────────────
void print(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << "->";
        temp = temp->next;
    }
}

// ── findLength: node count ─────────────────────────────────────────────────
int findLength(Node *&head) {
    int len = 0;
    Node *temp = head;
    while (temp != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}

// ── insertAtPosition: kisi position pe insert ──────────────────────────────
void insertAtPosition(int data, int position, Node *&head, Node *&tail) {
    int len = findLength(head);

    if (position == 1) {
        insertAtHead(head, tail, data);
        return;
    } else if (position > len) {
        insertAtTail(head, tail, data);
        return;
    } else {
        Node *newNode = new Node(data);

        Node *prev = NULL;
        Node *curr = head;
        while (position != 1) {
            position--;
            prev = curr;                   // prev pointer track
            curr = curr->next;
        }

        newNode->next = curr;
        prev->next = newNode;              // beech mein link update
    }
}

// ── deleteNode: position pe node delete ────────────────────────────────────
//   1) empty/single node special cases
//   2) position==1 → head shift
//   3) position==len → tail delete via prev
//   4) middle → prev->next = curr->next, delete curr
void deleteNode(Node *&head, Node *&tail, int position) {
    if (head == NULL) {
        cout << "Cannot delete, coz LL is empty" << endl;
        return;
    }

    if (head == tail) {
        Node *temp = head;
        delete temp;
        head = NULL;
        tail = NULL;
        return;
    }

    int len = findLength(head);

    if (position == 1) {
        Node *temp = head;
        head = head->next;                 // head pointer aage — next node
        temp->next = NULL;
        delete temp;
    } else if (position == len) {
        Node *prev = head;
        while (prev->next != tail) {
            prev = prev->next;
        }

        prev->next = NULL;                 // tail unlink — prev ka next NULL

        delete tail;

        tail = prev;                       // naya tail = prev
    } else {
        Node *prev = NULL;
        Node *curr = head;
        while (position != 1) {
            position--;
            prev = curr;
            curr = curr->next;
        }

        prev->next = curr->next;           // skip curr — pointer bypass

        curr->next = NULL;
        delete curr;
    }
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
    insertAtHead(head, tail, 50);
    insertAtHead(head, tail, 40);
    insertAtHead(head, tail, 30);
    insertAtHead(head, tail, 20);
    insertAtHead(head, tail, 10);

    print(head);
    cout << endl;

    deleteNode(head, tail, 3);
    print(head);
    cout << endl;

    return 0;
}
