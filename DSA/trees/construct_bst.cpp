/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : construct_bst.cpp
 * PROBLEM  : Construct Bst
 * LEETCODE : 1008 — Construct Binary Search Tree from Preorder Traversal
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// CONSTRUCT BST — Values se BST insert karke banao
// ────────────────────────────────────────────────────────────────────────────
// Problem: Array of values se valid BST construct karo.
//
// Approach: Standard BST insert
//   - val < root → left subtree
//   - val >= root → right subtree
//
// Complexity: Time O(n log n) avg  |  Space O(n)
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── insertBST: ek value BST me insert ──
//   1) Empty → naya node return
//   2) val < root->val → left me insert
//   3) Warna right me insert
//   4) BST property maintain
TreeNode *insertBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);

    return root;
}

// ── buildBST: array se poora BST banao ──
//   1) root = nullptr se start
//   2) Har value (except -1) insert karo
//   3) Final root return
TreeNode *buildBST(const vector<int> &values)
{
    TreeNode *root = nullptr;
    for (int val : values)
    {
        if (val != -1) // -1 = NULL marker ignore
            root = insertBST(root, val);
    }
    return root;
}

// ── inorderTraversal: BST inorder = sorted order ──
//   1) Left → root print → right
void inorderTraversal(TreeNode *root)
{
    if (!root)
        return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

// ── main: BST build + inorder verify ──
int main()
{
    vector<int> values = {5, 3, 7, 2, 4, 6, 8}; // BST values
    TreeNode *root = buildBST(values);

    cout << "Inorder Traversal (Sorted BST): ";
    inorderTraversal(root);
    cout << endl;

    return 0;
}
