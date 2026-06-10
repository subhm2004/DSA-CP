/*
 * ============================================================================
 * TOPIC    : Linked List
 * FILE     : k_group_reversal.cpp
 * PROBLEM  : K Group Reversal
 * LEETCODE : 25 — Reverse Nodes in k-Group
 * ABOUT    : Singly/doubly linked list operations and classic problems
 * APPROACH : Node* pointers; handle empty and single-node cases.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

// ════════════════════════════════════════════════════════════════════════════
// K-GROUP REVERSAL — har k nodes ka block reverse karo
// ────────────────────────────────────────────────────────────────────────────
// prev/current/next pointers se k nodes reverse
// har group ke baad prev link update — agle group se connect
// remaining < k nodes → as-is chhod do (LeetCode variant)
// ════════════════════════════════════════════════════════════════════════════
//
// ── reverseKGroup (planned): ───────────────────────────────────────────────
//   1) count k nodes available? nahi → return head
//   2) k nodes reverse — prev/current/next pointer swap
//   3) reversed block ka tail → agle group se link
//   4) recurse/repeat next group ke liye
