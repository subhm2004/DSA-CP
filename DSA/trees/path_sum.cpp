/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : path_sum.cpp
 * PROBLEM  : Path Sum
 * LEETCODE : 112 — Path Sum
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

// ════════════════════════════════════════════════════════════════════════════
// PATH SUM — Root-to-leaf path me target sum hai?
// ────────────────────────────────────────────────────────────────────────────
// Problem: Kya koi root-to-leaf path hai jiska nodes ka sum == target?
//
// Approach: DFS recursion
//   - Har step pe target -= node->val
//   - Leaf pe pahunch ke check: target == 0?
//   - Left ya right me se koi bhi true ho to true
//
// Complexity: Time O(n)  |  Space O(h)
//
// Note: Implementation abhi pending — sirf approach documented hai.
// ════════════════════════════════════════════════════════════════════════════
