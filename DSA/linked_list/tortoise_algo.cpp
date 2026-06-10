/*
 * ============================================================================
 * TOPIC    : Linked List — Floyd's Tortoise & Hare (Cycle Detection)
 * FILE     : tortoise_algo.cpp
 * PROBLEM  : Detect cycle + find cycle entry node + middle node
 * LEETCODE : 141 — Linked List Cycle
 *            142 — Linked List Cycle II
 *            876 — Middle of the Linked List (slow/fast variant)
 * REF      : https://cp-algorithms.com/others/tortoise_and_hare.html
 * APPROACH : Two pointers — slow moves 1 step, fast moves 2 steps
 * COMPLEX  : Time O(n)  |  Space O(1)
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// TORTOISE & HARE (FLOYD'S) — cycle detect, entry find, middle node
// ────────────────────────────────────────────────────────────────────────────
// Phase 1: slow 1 step, fast 2 step — meet → cycle hai
// Phase 2: slow=head, dono 1 step — meeting = cycle start (LC 142)
// Bonus: fast 2 step ruk jaye → slow = middle (LC 876)
// Math: head→entry distance = meeting→entry distance (mod cycle length)
// ════════════════════════════════════════════════════════════════════════════

struct ListNode {
    int data;
    ListNode *next;
    ListNode(int val = 0) : data(val), next(nullptr) {}
};

// ── hasCycle: kya cycle hai? (LC 141) ──────────────────────────────────────
//   1) slow=fast=head
//   2) fast aur fast->next check karke 2 step
//   3) slow==fast → true; fast null → false
bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;                 // tortoise — 1 step
        fast = fast->next->next;           // hare — 2 step
        if (slow == fast)
            return true;                   // cycle mein mil gaye
    }
    return false;
}

// ── detectCycleStart: cycle entry node (LC 142) ───────────────────────────
//   1) phase 1 — meeting point dhundho
//   2) no meeting → nullptr
//   3) slow=head; dono 1 step — entry pe milenge
ListNode *detectCycleStart(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            break;                         // meeting point G — cycle ke andar
    }

    if (fast == nullptr || fast->next == nullptr)
        return nullptr;

    slow = head;                           // phase 2 — head se shuru
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;                 // dono 1 step — entry C pe meet
    }
    return slow;
}

// ── findMeetingPoint: debug — cycle mein kahan mile ────────────────────────
ListNode *findMeetingPoint(ListNode *head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return slow;
    }
    return nullptr;
}

// ── middleNode: slow/fast se middle (LC 876) ───────────────────────────────
ListNode *middleNode(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;           // fast end → slow middle
    }
    return slow;
}

// ── buildListWithTail: demo list + tail pointer ─────────────────────────────
pair<ListNode *, ListNode *> buildListWithTail(const int *vals, int n) {
    if (n == 0) return {nullptr, nullptr};
    ListNode *head = new ListNode(vals[0]);
    ListNode *tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = new ListNode(vals[i]);
        tail = tail->next;                 // next pointer se chain
    }
    return {head, tail};
}

// ── printList: list print (cycle safe limit) ────────────────────────────────
void printList(ListNode *head, int maxSteps = 20) {
    ListNode *cur = head;
    int steps = 0;
    while (cur && steps < maxSteps) {
        cout << cur->data;
        if (cur->next && steps + 1 < maxSteps)
            cout << " -> ";
        cur = cur->next;
        steps++;
    }
    if (cur)
        cout << " -> ... (cycle)";
    cout << '\n';
}

// ── freeList: cycle tod ke memory free ─────────────────────────────────────
void freeList(ListNode *head, ListNode *cycleEntry) {
    if (cycleEntry) {
        ListNode *cur = cycleEntry;
        while (cur->next != cycleEntry)
            cur = cur->next;
        cur->next = nullptr;               // cycle break — next NULL
    }
    while (head) {
        ListNode *nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    cout << "=== Tortoise & Hare (Floyd's Cycle Algorithm) ===\n\n";

    {
        const int vals[] = {2, 4, 6, 8, 10, 12};
        auto [head, tail] = buildListWithTail(vals, 6);
        (void)tail;

        cout << "List (no cycle): ";
        printList(head);
        cout << "hasCycle?          " << (hasCycle(head) ? "yes" : "no") << "\n";
        cout << "cycle start        " << (detectCycleStart(head) ? "found" : "null") << "\n";
        cout << "middle node value  " << middleNode(head)->data << "  (expected 8)\n\n";

        freeList(head, nullptr);
    }

    {
        const int vals[] = {2, 4, 6, 8, 10, 12};
        auto [head, tail] = buildListWithTail(vals, 6);
        ListNode *node6 = head;
        while (node6 && node6->data != 6) node6 = node6->next;
        tail->next = node6;                // cycle — tail se node6 link

        cout << "List (cycle from 6): ";
        printList(head);
        cout << "hasCycle?           " << (hasCycle(head) ? "yes" : "no") << "\n";

        ListNode *entry = detectCycleStart(head);
        cout << "cycle start value   " << (entry ? to_string(entry->data) : "null")
             << "  (expected 6)\n";

        ListNode *meet = findMeetingPoint(head);
        cout << "meeting point value " << (meet ? to_string(meet->data) : "null")
             << "  (somewhere inside cycle)\n";

        freeList(head, node6);
    }

    return 0;
}
