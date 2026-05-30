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
 *
 * STEP 1 — Does a cycle exist? (LC 141)
 * -------------------------------------
 *   slow = fast = head
 *   while fast and fast->next:
 *       slow = slow->next          (tortoise — 1 step)
 *       fast = fast->next->next    (hare   — 2 steps)
 *       if slow == fast → cycle exists
 *   If fast reaches null → no cycle
 *
 *   Why it works: inside a cycle of length L, the gap between slow and fast
 *   grows by 1 each round → they must meet within L steps of the cycle.
 *
 * STEP 2 — Where does the cycle start? (LC 142)
 * ---------------------------------------------
 *   After step 1, slow and fast meet at some node G inside the cycle.
 *   Reset slow to head; move BOTH one step at a time.
 *   Meeting point = cycle entry C.
 *
 *   Math (CP-Algo): let a = distance head→C, b = distance C→G.
 *   slowDist = a + b + xL, fastDist = 2·slowDist
 *   ⇒ a = (y − 2x)L − b  →  moving a steps from head and from G both land on C.
 *
 * BONUS — Middle node (LC 876)
 * -----------------------------
 *   Same slow/fast, but stop when fast can't move 2 steps; slow = middle.
 * ============================================================================
 */

#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode *next;
    ListNode(int val = 0) : data(val), next(nullptr) {}
};

// ── STEP 1: cycle present? ─────────────────────────────────────────────────
bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    // CP-Algo: check fast AND fast->next before jumping 2 steps
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return true;
    }
    return false;
}

// ── STEP 2: cycle entry node (nullptr if no cycle) ───────────────────────────
ListNode *detectCycleStart(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            break; // meeting point G inside cycle
    }

    // No cycle
    if (fast == nullptr || fast->next == nullptr)
        return nullptr;

    // Phase 2: slow back to head, both move 1 step → meet at entry C
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

// Combined: returns meeting node inside cycle (for debugging), or nullptr
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

// ── BONUS: middle of linked list (slow/fast) ─────────────────────────────────
ListNode *middleNode(ListNode *head) {
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// ── Helpers for demo ─────────────────────────────────────────────────────────
pair<ListNode *, ListNode *> buildListWithTail(const int *vals, int n) {
    if (n == 0) return {nullptr, nullptr};
    ListNode *head = new ListNode(vals[0]);
    ListNode *tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = new ListNode(vals[i]);
        tail = tail->next;
    }
    return {head, tail};
}

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

void freeList(ListNode *head, ListNode *cycleEntry) {
    // Break cycle before delete to avoid infinite loop
    if (cycleEntry) {
        ListNode *cur = cycleEntry;
        while (cur->next != cycleEntry)
            cur = cur->next;
        cur->next = nullptr;
    }
    while (head) {
        ListNode *nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    cout << "=== Tortoise & Hare (Floyd's Cycle Algorithm) ===\n\n";

    // ── Demo 1: no cycle ───────────────────────────────────────────────────
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

    // ── Demo 2: cycle — tail connects back to node with value 6 ──────────────
    // List: 2 -> 4 -> 6 -> 8 -> 10 -> 12
    //                        ↑____________|
    {
        const int vals[] = {2, 4, 6, 8, 10, 12};
        auto [head, tail] = buildListWithTail(vals, 6);
        ListNode *node6 = head;
        while (node6 && node6->data != 6) node6 = node6->next;
        tail->next = node6; // cycle starts at node with value 6

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
