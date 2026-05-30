#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
    node(int x) : data(x), left(nullptr), right(nullptr) {}
};

bool kth_ancestor(node *root, int &k, node *p)
{
    // Base case: if the root is nullptr, return false
    if (root == nullptr)
    {
        return false;
    }

    // If the current node is the target node (p), return true
    if (root->data == p->data)
    {
        return true;
    }

    // Recursively search in the left and right subtrees
    bool left = kth_ancestor(root->left, k, p);
    bool right = kth_ancestor(root->right, k, p);

    // If the target node is found in either the left or right subtree, decrement k
    if (left || right)
    {
        k--;
    }

    // If k becomes 0, print the current node (which is the kth ancestor)
    if (k == 0)
    {
        cout << root->data << endl;
        k = -1; // Mark that the kth ancestor has been found to stop further recursion
    }

    // Return true if the node p is found in either the left or right subtree
    return left || right;
}

int main()
{
    // Sample binary tree creation
    node *root = new node(1);
    root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->left->left->left = new node(6);

    node *target = root->left->left->left; // Node 6 (we want its kth ancestor)

    int k = 2; // Find the 2nd ancestor
    if (!kth_ancestor(root, k, target))
    {
        if (k != -1)
        {
            cout << "No such ancestor found." << endl;
        }
    }

    return 0;
}
