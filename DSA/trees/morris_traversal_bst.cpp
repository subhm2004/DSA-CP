/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : morris_traversal_bst.cpp
 * PROBLEM  : Morris Traversal Bst
 * LEETCODE : 94 — BST Inorder (Morris traversal)
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Use BST property: left < root < right.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MORRIS TRAVERSAL ON BST — O(1) space sorted order
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST ka inorder (sorted) bina stack/recursion ke.
//
// Approach: Morris threading (same as BT, BST me output sorted aata hai)
// Complexity: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ── insertBST: standard BST insert ──
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

// ── buildBST: array se BST construct ──
TreeNode *buildBST(const vector<int> &values)
{
    TreeNode *root = nullptr;
    for (int val : values)
    {
        if (val != -1)
            root = insertBST(root, val);
    }
    return root;
}

// ── inorderTraversal: recursive inorder (reference) ──
void inorderTraversal(TreeNode *root)
{
    if (!root)
        return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

// ── morrisTraversal: O(1) space inorder on BST ──
//   1) curr = root; left nahi → print + right
//   2) Left hai → predecessor (rightmost in left)
//   3) Thread nahi → link banao, left jao
//   4) Thread hai → unlink, print, right jao
void morrisTraversal(TreeNode *root)
{
    TreeNode *curr = root;
    while (curr)
    {
        if (!curr->left)
        {
            cout << curr->val << " ";
            curr = curr->right;
        }
        else
        {
            TreeNode *pre = curr->left;
            while (pre->right && pre->right != curr)
            {
                pre = pre->right;
            }

            if (!pre->right)
            {
                pre->right = curr; // thread banao
                curr = curr->left;
            }
            else
            {
                pre->right = nullptr; // thread hatao
                cout << curr->val << " ";
                curr = curr->right;
            }
        }
    }
}

// ── main: recursive vs Morris compare ──
int main()
{
    vector<int> values = {5, 3, 7, 2, 4, 6, 8};
    TreeNode *root = buildBST(values);

    cout << "Inorder Traversal (Recursive): ";
    inorderTraversal(root);
    cout << endl;

    cout << "Inorder Traversal (Morris Traversal - Space Optimized): ";
    morrisTraversal(root);
    cout << endl;

    return 0;
}
