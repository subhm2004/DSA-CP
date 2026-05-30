#include <bits/stdc++.h> // Segment tree with lazy propagation
// This code implements a dynamic segment tree with lazy propagation for range updates and queries.
// It allows for efficient range updates (adding a value to a range) and range queries (finding the maximum value in a range).
// The segment tree is designed to handle large ranges efficiently,
// and it uses lazy propagation to defer updates until necessary, which optimizes performance for multiple updates
// and queries on the same range.
// The maximum range is defined as 1,000,000,000, which allows for handling large indices without needing to store all values explicitly.
// The code is structured to be efficient and clear, making it suitable for competitive programming and algorithmic challenges.
using namespace std;

// Yeh maximum range define karta hai jo humara segment tree handle kar sakta hai
#define MAX_RANGE 1e9 // dynamic segment tree use hi tab hota hai jab values 1e5 se badi ho jaye like 1e9

class SegmentTree
{
private:
    // Yeh humara node structure hai jo segment tree ke har node ko represent karta hai
    struct Node
    {
        long val = 0;          // Is node ka maximum value store hota hai
        long lazy = 0;         // Lazy propagation ke liye - pending updates yahan store hote hain
        Node *left = nullptr;  // Left child ka pointer
        Node *right = nullptr; // Right child ka pointer
    };

    Node *root; // Root node ka pointer

    // Yeh function lazy propagation handle karta hai
    // Matlab pending updates ko actually apply karta hai
    void push(Node *node, int l, int r)
    {
        // Agar left child exist nahi karta toh naya create kar do
        if (!node->left)
            node->left = new Node();

        // Agar right child exist nahi karta toh naya create kar do
        if (!node->right)
            node->right = new Node();

        // Agar koi lazy value pending hai toh usko apply karo
        if (node->lazy != 0)
        {
            // Current node ki value me lazy value add kar do
            node->val += node->lazy;

            // Agar yeh leaf node nahi hai (l != r) toh children ko bhi lazy value pass kar do
            if (l != r)
            {
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy;
            }

            // Lazy value ko reset kar do kyunki ab apply ho gaya
            node->lazy = 0;
        }
    }

    // Range update function - range [ql, qr] me val add karta hai
    void update(Node *node, int l, int r, int ql, int qr, int val)
    {
        // Pehle pending updates apply kar do
        push(node, l, r);

        // Agar current segment [l, r] aur query range [ql, qr] me koi overlap nahi hai
        // toh kuch nahi karna
        if (r < ql || l > qr)
            return;

        // Agar current segment puri tarah se query range ke andar hai
        // toh lazy value add kar do aur push kar do
        if (ql <= l && r <= qr)
        {
            node->lazy += val;
            push(node, l, r); // Immediately apply the lazy value
            return;
        }

        // Partial overlap ka case - dono children me jaana padega
        int mid = (l + r) / 2; // Mid point calculate karo

        // Left child me update karo
        update(node->left, l, mid, ql, qr, val);
        // Right child me update karo
        update(node->right, mid + 1, r, ql, qr, val);

        // Update ke baad current node ki value ko update karo
        // Yeh dono children ka maximum hoga
        push(node->left, l, mid);      // Left child ko push karo
        push(node->right, mid + 1, r); // Right child ko push karo
        node->val = max(node->left->val, node->right->val);
    }

    // Range query function - range [ql, qr] ka maximum value return karta hai
    long query(Node *node, int l, int r, int ql, int qr)
    {
        // Agar node exist nahi karta ya koi overlap nahi hai toh 0 return karo
        if (!node || r < ql || l > qr)
            return 0;

        // Pending updates apply karo
        push(node, l, r);

        // Agar current segment puri tarah se query range ke andar hai
        // toh current node ki value return kar do
        if (ql <= l && r <= qr)
            return node->val;

        // Partial overlap ka case - dono children se query karo aur maximum lo
        int mid = (l + r) / 2; // Mid point calculate karo

        // Left aur right subtree se maximum value nikalo
        long leftMax = query(node->left, l, mid, ql, qr);
        long rightMax = query(node->right, mid + 1, r, ql, qr);

        // Dono ka maximum return karo
        return max(leftMax, rightMax);
    }

public:
    // Constructor - root node create karta hai
    SegmentTree()
    {
        root = new Node();
    }

    // Public update function - range [l, r] me val add karta hai
    void update(int l, int r, int val)
    {
        update(root, 0, MAX_RANGE, l, r, val);
    }

    // Public query function - range [l, r] ka maximum value return karta hai
    long query(int l, int r)
    {
        return query(root, 0, MAX_RANGE, l, r);
    }
};

int main()
{
    // Segment tree ka object create karo
    SegmentTree tree;

    // Range [1, 5] me 10 add karo
    // Matlab index 1, 2, 3, 4, 5 sabme 10 add ho jayega
    tree.update(1, 5, 10);

    // Range [3, 7] me 5 add karo
    // Matlab index 3, 4, 5, 6, 7 sabme 5 add ho jayega
    // Ab index 3, 4, 5 me total 15 (10+5) ho gaya
    tree.update(3, 7, 5);

    // Range [1, 5] ka maximum query karo
    // Index 1,2 me 10 hai, index 3,4,5 me 15 hai
    // Toh maximum 15 hoga
    cout << tree.query(1, 5) << endl; // Output: 15

    // Index 6 ka value query karo
    // Yahan sirf 5 add hua tha (second update me)
    cout << tree.query(6, 6) << endl; // Output: 5

    // Index 0 ka value query karo
    // Yahan koi update nahi hua toh 0 hoga
    cout << tree.query(0, 0) << endl; // Output: 0

    return 0;
}