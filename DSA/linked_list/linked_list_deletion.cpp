/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : linked_list_deletion.cpp
 * PROBLEM  : Linked List Deletion
 * LEETCODE : 203 — Remove Linked List Elements
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// LINKED LIST DELETION — head, tail, middle index pe delete
// ────────────────────────────────────────────────────────────────────────────
// temp/ptr pointers se position track; next pointer bypass se node alag
// delete ke baad memory free — next=NULL pehle set karo
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
        cout << "destructor called for " << this->data << endl;
    }
};

// ── traversalLL: list print ────────────────────────────────────────────────
void traversalLL(Node *&head) {
    Node *tem = head;
    while (tem != NULL) {
        cout << tem->data << "-> ";
        tem = tem->next;
    }
}

// ── insertathead: head pe insert ───────────────────────────────────────────
void insertathead(Node *&head, Node *&tail, int data) {
    Node *newnode = new Node(data);
    if (head == NULL) {
        head = newnode;
        tail = newnode;
    } else {
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
        tail->next = newnode;
        tail = newnode;
    }
}

// ── deletehead: head node hatao ────────────────────────────────────────────
void deletehead(Node *&head) {
    if (head == NULL) {
        cout << "Can't delete" << endl;
    } else {
        Node *temp = head;
        head = temp->next;                 // head pointer update — agla node
        temp->next = NULL;
        delete temp;
    }
}

// ── deletetail: tail node hatao ────────────────────────────────────────────
void deletetail(Node *&head, Node *&tail) {
    if (head == NULL) {
        cout << "Can't delete" << endl;
    } else {
        Node *temp = head;
        while (temp->next != tail) {
            temp = temp->next;             // tail se pehle wala node
        }
        Node *ptr = tail;
        cout << "element deleted is " << ptr->data << endl;
        tail = temp;
        tail->next = NULL;                 // naya tail — next NULL
        delete ptr;
    }
}

// ── numofnodes: count ──────────────────────────────────────────────────────
int numofnodes(Node *&head, Node *&tail) {
    int count = 1;
    Node *temp = head;
    while (temp->next != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ── deletemiddle: index pe node delete ───────────────────────────────────────
void deletemiddle(Node *&head, Node *&tail, int &index) {
    if (index > numofnodes(head, tail) || index < 1) {
        cout << "Invalid Index for deletion " << endl;
        return;
    } else if (head == tail) {
        Node *temp = head;
        delete temp;
        head = NULL;
        tail = NULL;
    } else if (index == 1) {
        Node *temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
    } else if (index == numofnodes(head, tail)) {
        Node *temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        Node *ptr = tail;
        tail = temp;
        temp->next = NULL;
        delete ptr;
    } else {
        int i = 1;
        Node *temp = head;
        Node *ptr = head->next;
        while (index - 1 != i) {
            i++;
            temp = temp->next;             // prev pointer
            ptr = ptr->next;               // delete hone wala node
        }
        temp->next = ptr->next;            // bypass — ptr ko skip karo
        ptr->next = NULL;
        delete ptr;
    }
}

int main() {
    int index;
    cout << "enter the index to be deleted" << endl;
    cin >> index;
    Node *head = NULL;
    Node *tail = NULL;
    insertathead(head, tail, 10);
    insertathead(head, tail, 30);
    insertathead(head, tail, 50);
    insertathead(head, tail, 70);
    traversalLL(head);
    cout << endl;
    deletemiddle(head, tail, index);
    traversalLL(head);
}
