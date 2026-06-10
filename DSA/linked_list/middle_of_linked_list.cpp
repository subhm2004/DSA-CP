/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : middle_of_linked_list.cpp
 * PROBLEM  : Middle Of Linked List
 * LEETCODE : 876 — Middle of the Linked List
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : DP: longest increasing subsequence ending at i.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MIDDLE OF LINKED LIST + CYCLE — slow/fast pointer technique
// ────────────────────────────────────────────────────────────────────────────
// slow 1 step, fast 2 step — fast end pe slow = middle
// cycle: meet hone ke baad slow=head, dono 1 step → start point
// ════════════════════════════════════════════════════════════════════════════

class Node {
public:
    int data;
    Node *next;
};

// ── checkloop: Floyd's cycle detection ─────────────────────────────────────
bool checkloop(Node *head) {
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;             // fast 2 step
            slow = slow->next;             // slow 1 step
        }
        if (fast == slow) {
            return true;
        }
    }
    return false;
}

// ── startingpoint: cycle entry node ─────────────────────────────────────────
Node *startingpoint(Node *head) {
    Node *fast = head;
    Node *slow = head;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        if (fast == slow) {
            fast = head;
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;         // phase 2 — entry point find
            }
            Node *start = slow;
        }
    }
}

int main() {
}
