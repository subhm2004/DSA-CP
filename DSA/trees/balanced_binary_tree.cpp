/*
 * ============================================================================
 * TOPIC    : Trees
 * FILE     : balanced_binary_tree.cpp
 * PROBLEM  : Balanced Binary Tree
 * LEETCODE : 110 — Balanced Binary Tree
 * ABOUT    : Binary tree traversals, views, construction, Morris traversal
 * APPROACH : Recursive DFS; base case when node == nullptr.
 * COMPLEX  : See approach — depends on input size n.
 * ============================================================================
 */

#include <iostream>
#include <cmath>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// BALANCED BINARY TREE — Height-balanced check karo
// ────────────────────────────────────────────────────────────────────────────
// Problem: Har node pe left aur right subtree ki height ka diff ≤ 1 hona chahiye.
//
// Approach: Recursive DFS
//   - Har node pe dono subtrees ki height nikalo
//   - |left - right| ≤ 1 check karo + dono subtrees bhi balanced hon
//
// Complexity: Time O(n²) worst (har node pe height dubara count)
//             Space O(h) recursion stack
// ════════════════════════════════════════════════════════════════════════════

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int val)
    {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }
};

// ── CreateTree: recursive tree build karo ──
//   1) User se data lo (-1 = NULL node)
//   2) -1 aaye to NULL return karo
//   3) Naya Node banao aur left/right recursively build karo
//   4) Root pointer return karo
Node *CreateTree()
{
    int val;
    cout << "Enter data (-1 for NULL): ";
    cin >> val;
    if (val == -1)
    {
        return NULL;  // leaf ke neeche koi child nahi
    }
    Node *root = new Node(val);
    root->left = CreateTree();
    root->right = CreateTree();
    return root;
}

// ── maximumDepth: subtree ki height nikalo ──
//   1) NULL node → height 0
//   2) Left aur right subtree ki depth recursively lo
//   3) Dono me se bada + 1 (current node count)
//   4) Ye height balanced check me use hoti hai
int maximumDepth(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = maximumDepth(root->left);
    int right = maximumDepth(root->right);
    return max(left, right) + 1;
}

// ── isBalanced: poora tree height-balanced hai? ──
//   1) Empty tree → balanced maan lo (true)
//   2) Current node pe left/right height ka diff nikalo
//   3) Diff ≤ 1 hona chahiye
//   4) Left aur right subtrees bhi recursively balanced hon
//   5) Teen conditions AND se combine karo
bool isBalanced(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    int left = maximumDepth(root->left);
    int right = maximumDepth(root->right);
    bool difference = (abs(left - right) <= 1);  // height diff check
    bool lsubtree = isBalanced(root->left);
    bool rsubtree = isBalanced(root->right);
    return difference && lsubtree && rsubtree;
}

// ── main: tree banao aur balanced check karo ──
//   1) CreateTree se user input se tree build
//   2) isBalanced call karo
//   3) Result print karo
int main()
{
    Node *root = CreateTree();
    if (isBalanced(root))
    {
        cout << "The tree is height balanced." << endl;
    }
    else
    {
        cout << "The tree is NOT height balanced." << endl;
    }
    return 0;
}
