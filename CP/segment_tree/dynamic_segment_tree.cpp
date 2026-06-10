#include <bits/stdc++.h> // Segment tree with lazy propagation

// This code implements a dynamic segment tree with lazy propagation for range updates and queries.
// It allows for efficient range updates (adding a value to a range) and range queries (finding the maximum value in a range).
// The segment tree is designed to handle large ranges efficiently,
// and it uses lazy propagation to defer updates until necessary, which optimizes performance for multiple updates
// and queries on the same range.
// The maximum range is defined as 1,000,000,000, which allows for handling large indices without needing to store all values explicitly.
// The code is structured to be efficient and clear, making it suitable for competitive programming and algorithmic challenges.
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// DYNAMIC (LAZY-CREATED) SEGMENT TREE — Range Add + Range Max
// ────────────────────────────────────────────────────────────────────────────
// "Dynamic" ka matlab: poora tree pehle se nahi banate. Range bahut badi hai
// (0 .. 1e9) to saare nodes banana memory me possible hi nahi. Isliye nodes
// pointer se ON-DEMAND bante hain — jab pehli baar koi raasta visit hota hai
// tabhi child node allocate hota hai. Jo hisse kabhi touch nahi hue, unke
// nodes exist hi nahi karte (default value 0 maan li jaati hai).
//
// Recursion ke common params (1D seg tree jaise hi):
//   node -> abhi jis node pe khade ho uska pointer
//   l    -> is node ka segment LEFT  end  (actual index range)
//   r    -> is node ka segment RIGHT end
//   ql   -> query/update ka left end
//   qr   -> query/update ka right end
//   mid  -> (l + r) / 2, segment ko do halves me todne ke liye
//
// Har recursion me wahi 3 case: NO overlap / FULL overlap / PARTIAL overlap.
// Lazy propagation: range add ko turant har leaf tak nahi le jaate; node pe
// "pending add" rakh dete hain aur zarurat padne pe (push) niche bhejte hain.
// ════════════════════════════════════════════════════════════════════════════

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

    // ── push: lazy apply + on-demand child create ──
    //   1) dynamic tree me bachhe NULL ho sakte hain — pehle left/right create karo agar nahi hain
    //   2) lazy != 0 ho to node->val me lazy add karo (range add se max badhta hai)
    //   3) internal node (l != r) ho to wahi lazy bachho ke lazy me += karo
    //   4) lazy = 0 kar do — pending clear, node ab updated hai
    void push(Node *node, int l, int r)
    {
        if (!node->left)   // child abhi exist nahi — pehli visit pe allocate karo
            node->left = new Node();

        if (!node->right)
            node->right = new Node();

        if (node->lazy != 0)
        {
            node->val += node->lazy;  // is segment ke max me pending add apply

            if (l != r)  // internal node — lazy niche defer karo
            {
                node->left->lazy += node->lazy;
                node->right->lazy += node->lazy;
            }

            node->lazy = 0;  // pending apply ho chuka
        }
    }

    // ── update: [ql,qr] me val add karo (recursive) ──
    //   1) push pehle — purana pending apply + bachhe create ho jaayein
    //   2) Case 1 NO overlap (r<ql || l>qr) — return, ye subtree touch nahi hua
    //   3) Case 2 FULL overlap — lazy += val, push turant, return (har leaf tak nahi jaana)
    //   4) Case 3 PARTIAL — mid split, dono bachho update, phir parent val = max(bachhe)
    void update(Node *node, int l, int r, int ql, int qr, int val)
    {
        push(node, l, r);

        if (r < ql || l > qr)  // Case 1: NO overlap
            return;

        if (ql <= l && r <= qr)  // Case 2: FULL overlap
        {
            node->lazy += val;
            push(node, l, r);  // turant apply taaki node->val query me sahi ho
            return;
        }

        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap

        update(node->left, l, mid, ql, qr, val);
        update(node->right, mid + 1, r, ql, qr, val);

        push(node->left, l, mid);       // bachho ka pending clear karo merge se pehle
        push(node->right, mid + 1, r);
        node->val = max(node->left->val, node->right->val);  // parent max refresh
    }

    // ── query: [ql,qr] ka maximum nikalo ──
    //   1) node NULL ya NO overlap ho to 0 return (kabhi touch nahi hua segment)
    //   2) push pehle — pending lazy apply karo warna purana max milega
    //   3) Case 2 FULL overlap — seedha node->val return
    //   4) Case 3 PARTIAL — left/right max lo, unka overall max return karo
    long query(Node *node, int l, int r, int ql, int qr)
    {
        if (!node || r < ql || l > qr)  // node exist nahi ya NO overlap
            return 0;

        push(node, l, r);

        if (ql <= l && r <= qr)  // Case 2: FULL overlap
            return node->val;

        int mid = (l + r) / 2;  // Case 3: PARTIAL overlap

        long leftMax = query(node->left, l, mid, ql, qr);
        long rightMax = query(node->right, mid + 1, r, ql, qr);

        return max(leftMax, rightMax);
    }

public:
    // ── SegmentTree: constructor — sirf root node banao ──
    //   1) poora tree pehle se nahi banate — range 0..1e9 bahut badi hai
    //   2) root = new Node() — default val=0, lazy=0, bachhe NULL
    //   3) baaki nodes on-demand create honge jab update/query un raaste pe aayegi
    SegmentTree()
    {
        root = new Node();
    }

    // ── update: public wrapper — [l,r] me val add ──
    //   1) user range aur value deta hai
    //   2) root se recursion [0, MAX_RANGE] pe start — dynamic nodes banenge zarurat pe
    void update(int l, int r, int val)
    {
        update(root, 0, MAX_RANGE, l, r, val);
    }

    // ── query: public wrapper — [l,r] ka max lao ──
    //   1) root se query start karo
    //   2) jo segments kabhi touch nahi hue unke nodes exist nahi — 0 return hota hai
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