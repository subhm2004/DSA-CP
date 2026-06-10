/*
 * ============================================================================
 * TOPIC    : Persistent Segment Tree (Path-Copying / Versioned Segment Tree)
 * FILE     : persistent_segment_tree.cpp
 * PROBLEM  : Range sum queries on many historical versions of an array
 * APPROACH : Har update par poori tree copy nahi — sirf root se leaf tak
 *            wale path par naye nodes banate hain; baaki subtrees purane
 *            nodes ko reuse karte hain (path copying / fat node technique)
 * COMPLEX  : Build O(n) | Update O(log n) per version | Query O(log n)
 * MEMORY   : O(n + q·log n) nodes for q updates (pool-based, no leaks)
 * ============================================================================
 *
 * NORMAL vs PERSISTENT
 * --------------------
 * Normal seg tree: update in-place → purana data kho jata hai.
 * Persistent PST : update → naya root, purana root safe → version id se
 *                  kisi bhi past state par query kar sakte ho.
 *
 * PATH COPYING (idea)
 * -------------------
 *        [v0 root]                    update index 2
 *         /     \                              |
 *       [A]     [B]                    naya [A'] (copy path)
 *       / \     / \                      / \
 *     ... ... ... ...          reuse → ... ... [B] (same pointer as v0)
 *
 * Sirf O(log n) naye nodes per update; shared children = memory bachta hai.
 *
 * COMMON USE CASES
 * ----------------
 * 1. Range sum on version t (yeh file)
 * 2. K-th smallest in prefix / range (coordinate compression + freq PST)
 * 3. Historical queries: "array jaisa tha update i ke baad, [L,R] ka sum?"
 * 4. Offline: queryVersion(v+1, L, R) - queryVersion(v, L, R) = delta of update
 *
 * NOTE: Point update set karta hai (assign). Range add ke liye lazy + persistence
 *       alag topic hai — yahan classic interview/contest template hai.
 * ============================================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// PersistentSegmentTree
// ─────────────────────────────────────────────────────────────────────────────
class PersistentSegmentTree {
public:
    // ── Node pool ────────────────────────────────────────────────────────────
    // Pointer-based tree ki jagah vector<int> indices — CP mein fast + safe.
    // nodes[i].left / .right = child indices in pool (0 = null sentinel).
    struct Node {
        long long sum;  // is segment [tl, tr] par elements ka sum
        int left;       // left child index in pool (0 if leaf with no left)
        int right;      // right child index in pool
    };

private:
    vector<Node> pool;   // saare nodes yahan allocate (monotonically grow)
    vector<int> roots;   // roots[v] = version v ka root index
    int n;               // array size (0-indexed, indices 0 .. n-1)

    // ── newNode: pool me naya node allocate karo ──
    //   1) pool vector me {sum, leftChild, rightChild} push karo
    //   2) Naya node ka index = pool.size()-1 return karo
    //   3) Index 0 reserved hai as NULL sentinel — real nodes 1 se shuru
    int newNode(long long sum, int leftChild, int rightChild) {
        pool.push_back({sum, leftChild, rightChild});
        return (int)pool.size() - 1;
    }

    static constexpr int NULL_NODE = 0;

    // ── build: initial array se version 0 ki tree banao ──
    //   1) Base case tl==tr → leaf node, sum=a[tl], koi child nahi (NULL)
    //   2) tm = (tl+tr)/2 se segment ko do halves me todo
    //   3) Left aur right subtree recursively build karo
    //   4) Parent node = left.sum + right.sum, left/right child indices store
    int build(const vector<long long> &a, int tl, int tr) {
        if (tl == tr) {
            return newNode(a[tl], NULL_NODE, NULL_NODE);
        }
        int tm = (tl + tr) >> 1;
        int l = build(a, tl, tm);
        int r = build(a, tm + 1, tr);
        return newNode(pool[l].sum + pool[r].sum, l, r);
    }

    // ── update: path-copy se naya version banao (point assign) ──
    //   1) Leaf (tl==tr) → bilkul naya node with val, purana leaf reuse nahi
    //   2) pos left half me → left child naya banao (recursive), right PURANA reuse
    //   3) pos right half me → left PURANA reuse, right child naya banao
    //   4) Har step pe naya parent node — sirf O(log n) nodes copy, baaki share
    int update(int prevRoot, int tl, int tr, int pos, long long val) {
        if (tl == tr) {
            return newNode(val, NULL_NODE, NULL_NODE);
        }

        int tm = (tl + tr) >> 1;
        if (pos <= tm) {
            int newLeft = update(pool[prevRoot].left, tl, tm, pos, val);
            int oldRight = pool[prevRoot].right;  // right subtree purana reuse
            long long newSum = pool[newLeft].sum + pool[oldRight].sum;
            return newNode(newSum, newLeft, oldRight);
        } else {
            int oldLeft = pool[prevRoot].left;  // left subtree purana reuse
            int newRight = update(pool[prevRoot].right, tm + 1, tr, pos, val);
            long long newSum = pool[oldLeft].sum + pool[newRight].sum;
            return newNode(newSum, oldLeft, newRight);
        }
    }

    // ── query: kisi bhi version ke root se range [ql,qr] ka sum ──
    //   1) Case 1 NULL/out of range → 0 return (sum identity)
    //   2) Case 2 FULL overlap (ql<=tl && tr<=qr) → pool[root].sum return
    //   3) Case 3 PARTIAL → tm se todo, left sum + right sum combine
    long long query(int root, int tl, int tr, int ql, int qr) const {
        if (root == NULL_NODE || ql > tr || qr < tl) {
            return 0;  // Case 1: null / out of range
        }
        if (ql <= tl && tr <= qr) {
            return pool[root].sum;  // Case 2: poora segment andar hai
        }
        int tm = (tl + tr) >> 1;  // Case 3: partial
        return query(pool[root].left, tl, tm, ql, qr)
             + query(pool[root].right, tm + 1, tr, ql, qr);
    }

public:
    // ── PersistentSegmentTree: constructor — version 0 banao ──
    //   1) n = array size, pool ko reserve karo (memory pre-allocate)
    //   2) Index 0 = null sentinel push karo
    //   3) build() se version 0 ka root banao aur roots[0] me store
    explicit PersistentSegmentTree(const vector<long long> &a) {
        n = (int)a.size();
        pool.reserve(max(4 * n, 1) + n * 25);
        pool.push_back({0, NULL_NODE, NULL_NODE});
        roots.push_back(build(a, 0, n - 1));
    }

    int size() const { return n; }
    int versionCount() const { return (int)roots.size(); }
    int nodeCount() const { return (int)pool.size(); }

    // ── updateVersion: baseVersion se naya version banao ──
    //   1) baseVersion ka root lo (roots[baseVersion])
    //   2) update() se path-copy karke naya root banao
    //   3) Naya root roots me push karo, naya version id return karo
    int updateVersion(int baseVersion, int pos, long long val) {
        assert(0 <= baseVersion && baseVersion < (int)roots.size());
        assert(0 <= pos && pos < n);
        int newRoot = update(roots[baseVersion], 0, n - 1, pos, val);
        roots.push_back(newRoot);
        return (int)roots.size() - 1;
    }

    // ── queryVersion: version v par range [l,r] ka sum ──
    //   1) roots[version] se us version ka root index lo
    //   2) query() se standard seg tree range sum nikalo
    long long queryVersion(int version, int l, int r) const {
        assert(0 <= version && version < (int)roots.size());
        assert(0 <= l && l <= r && r < n);
        return query(roots[version], 0, n - 1, l, r);
    }

    // ── queryAll: poori array ka sum is version par ──
    long long queryAll(int version) const {
        return queryVersion(version, 0, n - 1);
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// Demo — versions independent rehte hain
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Initial: [1, 3, 5, 7, 9, 11]
    vector<long long> a = {1, 3, 5, 7, 9, 11};
    PersistentSegmentTree pst(a);

    cout << "=== Persistent Segment Tree Demo ===\n\n";
    cout << "Initial array: ";
    for (long long x : a) cout << x << ' ';
    cout << "\n\n";

    // Version 0 queries
    cout << "[v0] sum[0..5] = " << pst.queryAll(0) << "\n";
    cout << "[v0] sum[1..3] = " << pst.queryVersion(0, 1, 3) << "  (3+5+7=15)\n\n";

    // v1: index 2 ko 100 set karo (5 → 100), v0 se branch
    int v1 = pst.updateVersion(0, 2, 100);
    cout << "Update v0 → v1: a[2] = 100\n";
    cout << "[v0] sum[1..3] = " << pst.queryVersion(0, 1, 3) << "  (still 15 — old version safe)\n";
    cout << "[v1] sum[1..3] = " << pst.queryVersion(v1, 1, 3) << "  (3+100+7=110)\n";
    cout << "[v1] sum[0..5] = " << pst.queryAll(v1) << "\n\n";

    // v2: v1 se a[0] = 50
    int v2 = pst.updateVersion(v1, 0, 50);
    cout << "Update v1 → v2: a[0] = 50\n";
    cout << "[v0] a[0] implicit = " << pst.queryVersion(0, 0, 0) << "  (still 1)\n";
    cout << "[v1] a[0] implicit = " << pst.queryVersion(v1, 0, 0) << "  (still 1)\n";
    cout << "[v2] a[0] implicit = " << pst.queryVersion(v2, 0, 0) << "  (50)\n";
    cout << "[v2] sum[0..5] = " << pst.queryAll(v2) << "\n\n";

    // v3: v0 se hi alag branch — v1/v2 ko affect nahi karta
    int v3 = pst.updateVersion(0, 4, 0);
    cout << "Update v0 → v3: a[4] = 0  (branch from v0, not v2)\n";
    cout << "[v2] sum[0..5] = " << pst.queryAll(v2) << "  (unchanged)\n";
    cout << "[v3] sum[0..5] = " << pst.queryAll(v3) << "\n\n";

    cout << "Versions: " << pst.versionCount()
         << " | Nodes in pool: " << pst.nodeCount()
         << "  (shared subtrees → less than 4 * n * versions)\n";

    return 0;
}
