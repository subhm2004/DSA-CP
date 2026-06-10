/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : binary_tree_diameter.cpp
 * PROBLEM  : Binary Tree Diameter
 * LEETCODE : 543 — Diameter of Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

// ════════════════════════════════════════════════════════════════════════════
// BINARY TREE DIAMETER — Sabse lamba path (edges count)
// ────────────────────────────────────────────────────────────────────────────
// Problem: Tree ka diameter = kisi bhi do nodes ke beech longest path.
//
// Approach: Height DFS + global max
//   - Har node pe leftHeight + rightHeight update karo (diameter candidate)
//   - Height return karte waqt max diameter track karo
//   - Diameter = max(leftH + rightH) across all nodes
//
// Complexity: Time O(n) single pass  |  Space O(h)
//
// Note: Implementation abhi pending — sirf approach documented hai.
// ════════════════════════════════════════════════════════════════════════════
