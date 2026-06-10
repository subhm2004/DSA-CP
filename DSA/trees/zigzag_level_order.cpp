/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : zigzag_level_order.cpp
 * PROBLEM  : Zigzag Level Order
 * LEETCODE : 103 — Binary Tree Zigzag Level Order Traversal
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

// ════════════════════════════════════════════════════════════════════════════
// ZIGZAG LEVEL ORDER — Level-by-level alternate direction
// ────────────────────────────────────────────────────────────────────────────
// Problem: Level 0 left→right, level 1 right→left, level 2 left→right ...
//
// Approach: BFS + deque / reverse flag
//   1) Queue se level-wise nodes nikalo
//   2) Har level ke liye vector me collect karo
//   3) Odd level pe reverse karo ya deque se alternate push
//   4) Result me har level ka vector daalo
//
// Complexity: Time O(n)  |  Space O(n)
//
// Note: Implementation abhi pending — sirf approach documented hai.
// ════════════════════════════════════════════════════════════════════════════
