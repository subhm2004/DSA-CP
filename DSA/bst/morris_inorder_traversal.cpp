/*
 * ============================================================================
 * TOPIC    : Bst
 * FILE     : morris_inorder_traversal.cpp
 * PROBLEM  : Morris Inorder Traversal (Threaded Tree)
 * ABOUT    : Inorder without recursion/stack — O(1) extra space
 * APPROACH : Inorder predecessor se temporary thread banao; visit karke hata do
 * COMPLEX  : Time O(n), Space O(1)
 * ============================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// MORRIS INORDER ON BST — Stack-free sorted traversal
// ────────────────────────────────────────────────────────────────────────────
// Problem: BST ka inorder bina extra space ke (O(1)).
//
// Approach: Threaded tree — predecessor->right temporary link
// Complexity: Time O(n)  |  Space O(1)
// ════════════════════════════════════════════════════════════════════════════

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

// ── CreateBST: insert nodes ──
Node *CreateBST(Node *root, int data)
{
    if (root == NULL)
    {
        root = new Node(data);
        return root;
    }
    if (data > root->data)
        root->right = CreateBST(root->right, data);
    else
        root->left = CreateBST(root->left, data);
    return root;
}

// ── inorderRecursive: reference implementation ──
void inorderRecursive(Node *root)
{
    if (root == NULL)
        return;
    inorderRecursive(root->left);
    cout << root->data << " ";
    inorderRecursive(root->right);
}

// ── morrisInorder: O(1) space inorder ──
//   1) Left nahi → print + right jao
//   2) Left hai → predecessor (rightmost in left)
//   3) Thread nahi → pred->right = curr, left jao
//   4) Thread hai → hatao, print, right jao
void morrisInorder(Node *root)
{
    Node *curr = root;
    while (curr != NULL)
    {
        if (curr->left == NULL)
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
        else
        {
            Node *pred = curr->left;
            while (pred->right != NULL && pred->right != curr)
                pred = pred->right;

            if (pred->right == NULL)
            {
                pred->right = curr; // temporary thread
                curr = curr->left;
            }
            else
            {
                pred->right = NULL; // thread remove
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
    }
}

// ── main: recursive vs Morris compare ──
int main()
{
    vector<int> arr = {50, 30, 70, 20, 40, 60, 80};
    Node *root = NULL;
    for (int x : arr)
        root = CreateBST(root, x);

    cout << "Recursive inorder : ";
    inorderRecursive(root);
    cout << "\n";

    cout << "Morris inorder    : ";
    morrisInorder(root);
    cout << "\n";

    return 0;
}
