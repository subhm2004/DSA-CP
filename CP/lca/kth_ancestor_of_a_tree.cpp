#include <iostream>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// K-th ANCESTOR — Binary Tree (Recursive DFS approach)
// ────────────────────────────────────────────────────────────────────────────
// Target node p dhoondho. Jab wapas aa rahe ho (post-order) to k-- karo.
// Jab k==0 ho, current node = k-th ancestor hai.
// ════════════════════════════════════════════════════════════════════════════

struct node
{
    int data;
    node *left;
    node *right;
    node(int x) : data(x), left(nullptr), right(nullptr) {}
};

// ── kth_ancestor: root se target p dhoondho, k-th ancestor print karo ───────
//   1) base: root NULL -> false; root==p -> true (target mil gaya)
//   2) left/right subtree me recursively p dhoondo
//   3) return path pe aate waqt k-- (har ancestor ek step upar)
//   4) k==0 ho to current node print, k=-1 set (aur recursion rok do)
bool kth_ancestor(node *root, int &k, node *p)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->data == p->data)
    {
        return true;             // target mil gaya — ab wapas jaate waqt k decrement hoga
    }

    bool left = kth_ancestor(root->left, k, p);
    bool right = kth_ancestor(root->right, k, p);

    if (left || right)
    {
        k--;                     // is node se ek level upar gaye — k kam karo
    }

    if (k == 0)
    {
        cout << root->data << endl;
        k = -1; // mil gaya, aur recursion rok do
    }

    return left || right;
}

int main()
{
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->left->left->left = new node(6);

    node *target = root->left->left->left;

    int k = 2;
    if (!kth_ancestor(root, k, target))
    {
        if (k != -1)
        {
            cout << "No such ancestor found." << endl;
        }
    }

    return 0;
}
