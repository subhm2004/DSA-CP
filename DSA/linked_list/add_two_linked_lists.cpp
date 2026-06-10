/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : add_two_linked_lists.cpp
 * PROBLEM  : Add Two Linked Lists
 * LEETCODE : 2 — Add Two Numbers
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// ADD TWO NUMBERS (LINKED LISTS) — digit-by-digit sum with carry
// ────────────────────────────────────────────────────────────────────────────
// dono lists parallel traverse; sum = l1+l2+carry
// result node banake next pointer link; carry aage le jao
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

// ── insertathead: list build helper (stub) ──────────────────────────────────
//   1) naya Node(data) banao
//   2) head/tail update — list construct
void insertathead(Node *&head, Node *&tail, int data) {
}

int main() {
    Node *head = NULL;
    Node *tail = NULL;
}
