#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COORDINATE COMPRESSION CLASS
// ════════════════════════════════════════════════════════════════════════════
// Problem kyun aata hai?
//   X coordinates 10^8 tak ho sakti hain
//   Segment tree seedha itna bada nahi bana sakte (memory/time dono waste)
//
// Solution kya hai?
//   Sirf "important" X points rakho
//   Har square sirf 2 points generate karta hai: left aur right
//   n=1000 squares → max 2000 unique points
//   In 2000 points ko 0,1,2,...,1999 pe map karo
//
// Example:
//   Real points:       {1, 2, 3, 5, 6, 7}
//   Compressed points: {0, 1, 2, 3, 4, 5}
//   Segment tree size: 6 (instead of 10^8!)
// ════════════════════════════════════════════════════════════════════════════
class Coordinate_Compression {
public:
    unordered_map<int, int> compress; // original value -> compressed id
    vector<int> rev_map;              // compressed id -> original value

    // ── Constructor ─────────────────────────────────────────────────────────
    // Kaam: Array se unique sorted values nikaal ke 0,1,2,... id assign karo
    //
    // Step 1: set mein daalo
    //         → duplicates automatically remove ho jaate hain
    //         → automatically sorted ho jaate hain (set property)
    //
    // Step 2: har unique value ko id assign karo
    //         compress[original_value] = id   → lookup ke liye
    //         rev_map[id] = original_value    → reverse lookup ke liye
    //
    // Example:
    //   arr = {1, 3, 2, 5, 6, 7, 3, 1}
    //   set  = {1, 2, 3, 5, 6, 7}  (sorted, unique)
    //   compress: 1->0, 2->1, 3->2, 5->3, 6->4, 7->5
    //   rev_map:  [1, 2, 3, 5, 6, 7]
    // ────────────────────────────────────────────────────────────────────────
    Coordinate_Compression(const vector<int>& arr) {
        set<int> st(arr.begin(), arr.end()); // unique + sorted
        int id = 0;
        for (int x : st) {
            compress[x] = id;    // original -> compressed
            rev_map.push_back(x); // compressed -> original
            id++;
        }
    }

    // ── get_compressed ───────────────────────────────────────────────────────
    // Kaam: Poori array ke har element ko uska compressed id de do
    //
    // Example:
    //   arr = {1, 3, 2, 1, 5}
    //   res = {0, 2, 1, 0, 3}  (compress map se lookup)
    //
    // Use case: Jab poori array ek saath compress karni ho
    // ────────────────────────────────────────────────────────────────────────
    vector<int> get_compressed(const vector<int>& arr) {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]]; // har element ka compressed id lo
        return res;
    }

    // ── get_original ─────────────────────────────────────────────────────────
    // Kaam: Compressed id se wapas original value lo
    //
    // Example:
    //   get_original(3) → 5  (rev_map[3] = 5)
    //
    // Use case: Answer display karna ho original coordinates mein
    // ────────────────────────────────────────────────────────────────────────
    int get_original(int val) {
        return rev_map[val];
    }
};

// ════════════════════════════════════════════════════════════════════════════
// SEGMENT TREE WITH LAZY PROPAGATION
// ════════════════════════════════════════════════════════════════════════════
// Kaam kya karta hai?
//   Range max query:  "Index l se r tak max height kya hai?"
//   Range max update: "Index l se r tak sab ki height h kar do"
//
// Lazy Propagation kyun?
//   Bina lazy: Range update O(n) — har node individually update karo
//   Lazy ke saath: Range update O(log n) — "pending" store karo, baad mein apply karo
//
// Tree Structure (0-indexed nodes):
//         node 0 → root, covers [0, n-1]
//         node i → left child: 2*i+1, right child: 2*i+2
//
//   Example (n=4):
//              [0,3] node0
//             /           \
//        [0,1] node1    [2,3] node2
//        /    \          /    \
//    [0] n3  [1] n4  [2] n5  [3] n6
// ════════════════════════════════════════════════════════════════════════════
class SegmentTree {
private:
    vector<int> segTree; // segTree[i] = node i ki actual max height
    vector<int> lazy;    // lazy[i] = node i pe pending update (abhi children ko nahi bataya)
    int size;            // total leaf nodes (= total unique coordinates)

    // ── build ────────────────────────────────────────────────────────────────
    // Kaam: Tree initialize karo — sab values 0 se start
    //
    // i    = current node index
    // l, r = current node ki range (compressed indices)
    //
    // Base case: l==r matlab leaf node — ek single coordinate
    //            height = 0 (koi square abhi nahi gira)
    //
    // Recursive case: pehle left subtree banao, phir right subtree
    //                 (internal nodes build ke time mein 0 hi rahenge)
    // ────────────────────────────────────────────────────────────────────────
    void build(int i, int l, int r) {
        if (l == r) {
            segTree[i] = 0; // leaf node, height = 0
            return;
        }
        int mid = (l + r) / 2;
        build(2*i+1, l, mid);   // left subtree
        build(2*i+2, mid+1, r); // right subtree
        // internal nodes bhi 0 hi hain, koi merge nahi karna abhi
    }

    // ── push ─────────────────────────────────────────────────────────────────
    // Kaam: Node pe jo "pending update" stored hai usse actually apply karo
    //
    // Lazy propagation ka core idea:
    //   Jab range update karte hain, hum SIRF us node pe lazy store karte hain
    //   Children ko tab batate hain jab unhe actually query ya update karna ho
    //   Ye O(n) se O(log n) karta hai range update ko
    //
    // Push kab call hota hai?
    //   1. Query ke time — pehle push karo, phir query karo
    //   2. Update ke time — pehle push karo, phir decide karo kya karna hai
    //
    // Example:
    //   lazy[node] = 5 (matlab ye node aur iske subtree ki height >= 5 honi chahiye)
    //
    //   push ke baad:
    //   segTree[node] = max(segTree[node], 5)  → khud update ho gaya
    //   lazy[left_child] = max(lazy[left], 5)  → children ko bataya
    //   lazy[right_child] = max(lazy[right], 5)
    //   lazy[node] = 0                          → pending clear
    // ────────────────────────────────────────────────────────────────────────
    void push(int i, int l, int r) {
        if (lazy[i]) { // koi pending update hai?

            // Khud ko update karo
            segTree[i] = max(segTree[i], lazy[i]);

            if (l != r) { // leaf nahi hai → children ko pending batao
                // Children ke lazy mein add karo (actual update nahi, sirf pending store)
                lazy[2*i+1] = max(lazy[2*i+1], lazy[i]);
                lazy[2*i+2] = max(lazy[2*i+2], lazy[i]);
            }

            lazy[i] = 0; // apna pending clear karo
        }
    }

    // ── query (internal) ─────────────────────────────────────────────────────
    // Kaam: Range [ql, qr] mein maximum height nikalo
    //
    // Parameters:
    //   i       = current node index
    //   l, r    = current node ki range
    //   ql, qr  = query range (humein kya chahiye)
    //
    // 3 Cases:
    //   Case 1 — No overlap: current range [l,r] query [ql,qr] ke bahar hai
    //            → 0 return karo (koi relevant data nahi)
    //
    //   Case 2 — Full overlap: current range [l,r] poori query ke andar hai
    //            → seedha is node ki value return karo
    //
    //   Case 3 — Partial overlap: dono mein kuch overlap hai
    //            → dono children se poochho, max lo
    //
    // Example:
    //   Tree range [0,5], Query [1,3]
    //
    //        [0,5] → partial overlap → children mein jao
    //       /      \
    //   [0,2]      [3,5]  → dono partial → aur neeche jao
    //   /   \      /   \
    // [0,1][2,2][3,4][5,5]
    //            ↑
    //       full overlap!
    // ────────────────────────────────────────────────────────────────────────
    int query(int i, int l, int r, int ql, int qr) {
        push(i, l, r); // pehle pending update apply karo

        // Case 1: Poori range bahar hai → irrelevant
        if (qr < l || ql > r) return 0;

        // Case 2: Poori range andar hai → seedha return
        if (ql <= l && r <= qr) return segTree[i];

        // Case 3: Partial overlap → dono children se poochho
        int mid = (l + r) / 2;
        return max(
            query(2*i+1, l, mid, ql, qr),    // left child
            query(2*i+2, mid+1, r, ql, qr)   // right child
        );
    }

    // ── update (internal) ────────────────────────────────────────────────────
    // Kaam: Range [ql, qr] ki height h se update karo (max operation)
    //
    // Parameters:
    //   i       = current node index
    //   l, r    = current node ki range
    //   ql, qr  = update range
    //   h       = new height value
    //
    // 3 Cases (query jaisi hi logic):
    //   Case 1 — No overlap: kuch mat karo
    //
    //   Case 2 — Full overlap: lazy mein daal do
    //            → children ko abhi mat batao (lazy propagation!)
    //            → sirf push karo khud pe
    //
    //   Case 3 — Partial overlap: children ko update karo
    //            → phir parent ko children se update karo (pull up)
    //
    // Kyun max use kiya, assign nahi?
    //   Squares sirf stack hote hain, height kabhi kam nahi hoti
    //   Ek range pe pehle height=3 thi, naya square height=7 karta hai
    //   max(3, 7) = 7 → correct
    //   Agar directly assign karo toh pehle wali height kho sakti hai
    // ────────────────────────────────────────────────────────────────────────
    void update(int i, int l, int r, int ql, int qr, int h) {
        push(i, l, r); // pehle pending update apply karo

        // Case 1: Poori range bahar → kuch nahi karna
        if (qr < l || ql > r) return;

        // Case 2: Poori range andar → lazy mein store karo
        if (ql <= l && r <= qr) {
            lazy[i] = max(lazy[i], h); // pending update store karo
            push(i, l, r);             // khud pe toh apply karo
            return;
        }

        // Case 3: Partial overlap → children ko update karo
        int mid = (l + r) / 2;
        update(2*i+1, l, mid, ql, qr, h);    // left child update
        update(2*i+2, mid+1, r, ql, qr, h);  // right child update

        // Children update ho gaye → parent = max of children
        // (parent ki value children se derive hoti hai)
        segTree[i] = max(segTree[2*i+1], segTree[2*i+2]);
    }

public:
    // ── Constructor ──────────────────────────────────────────────────────────
    // n = total unique coordinates (compressed size)
    // 4*n isliye: segment tree worst case mein 4*n nodes leta hai
    // ────────────────────────────────────────────────────────────────────────
    SegmentTree(int n) {
        size = n;
        segTree.resize(4*n, 0); // sab heights 0 se start
        lazy.resize(4*n, 0);    // koi pending update nahi
        build(0, 0, size-1);    // tree initialize karo
    }

    // ── Public wrappers ───────────────────────────────────────────────────────
    // Andar ki i, l, r complexity hide karte hain
    // User sirf range deta hai → internally root (i=0) se shuru hota hai
    // ────────────────────────────────────────────────────────────────────────
    int query(int l, int r) {
        return query(0, 0, size-1, l, r);
    }

    void update(int l, int r, int h) {
        update(0, 0, size-1, l, r, h);
    }
};

// ════════════════════════════════════════════════════════════════════════════
// SOLUTION CLASS
// ════════════════════════════════════════════════════════════════════════════
// Overall Flow:
//   1. Saare X coordinates collect karo (left aur right edges)
//   2. Coordinate compression karo → chhote indices pe map karo
//   3. Segment tree banao compressed size ka
//   4. Har square ke liye:
//      a. Query: is range mein abhi max height kya hai?
//      b. Calculate: new_height = curr_height + square_size
//      c. Update: is range ki height new_height se update karo
//      d. Track global max, push to answer
// ════════════════════════════════════════════════════════════════════════════
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {

        // ── STEP 1: Important X coordinates collect karo ────────────────────
        // Kyu sirf left aur right?
        // Height sirf square boundaries pe change hoti hai
        // Beeche ke points irrelevant hain segment tree ke liye
        //
        // positions = [[1,2],[2,3],[6,1]]
        // coords = {1,3, 2,5, 6,7}
        //           ↑↑  ↑↑  ↑↑
        //          sq1  sq2  sq3 ke left,right
        // ────────────────────────────────────────────────────────────────────
        vector<int> coords;
        for (auto& p : positions) {
            coords.push_back(p[0]);        // left edge
            coords.push_back(p[0] + p[1]); // right edge
        }

        // ── STEP 2: Compress karo ────────────────────────────────────────────
        // coords = {1,3,2,5,6,7}
        // Unique sorted: {1,2,3,5,6,7}
        // Compressed:    {0,1,2,3,4,5}
        //
        // cc.compress: 1->0, 2->1, 3->2, 5->3, 6->4, 7->5
        // cc.rev_map:  [1, 2, 3, 5, 6, 7]
        // total = 6 (segment tree sirf 6 nodes pe!)
        // ────────────────────────────────────────────────────────────────────
        Coordinate_Compression cc(coords);
        int total = cc.rev_map.size(); // unique coordinates ki count

        // ── STEP 3: Segment tree banao ───────────────────────────────────────
        // Size = total unique coordinates
        // Sab heights 0 se initialize
        // ────────────────────────────────────────────────────────────────────
        SegmentTree st(total);

        vector<int> ans;
        int max_height = 0;

        // ── STEP 4: Har square process karo ─────────────────────────────────
        for (auto& p : positions) {
            int left  = p[0];       // square ka left edge (real coordinate)
            int size  = p[1];       // square ki side length
            int right = left + size; // square ka right edge (real coordinate)

            // Real coordinates → compressed indices
            int l = cc.compress[left];  // left ka compressed id
            int r = cc.compress[right]; // right ka compressed id

            // ── r-1 kyun? ────────────────────────────────────────────────────
            // Square physically [left, right) occupy karta hai
            // right boundary pe square nahi hai — open bracket!
            //
            // Example:
            //   left=1, size=2 → X range [1, 3)
            //   Compressed: index[1]=0, index[3]=2
            //   Actual occupied: index 0 aur 1 (NOT 2)
            //   Toh r = 2-1 = 1
            //
            // Agar r-1 na karo:
            //   Square [1,3) aur Square [3,5) dono ke beech
            //   index 2 (real coordinate 3) pe overlap dikhega
            //   Jabki actually ye sirf touch kar rahe hain!
            //   → Galat answer aayega
            // ────────────────────────────────────────────────────────────────
            r = r - 1;

            // ── Query: Abhi is range mein kitni height hai? ──────────────────
            // Koi purana square yahan tha toh uski height milegi
            // Koi nahi tha toh 0 milega (x-axis)
            // ────────────────────────────────────────────────────────────────
            int curr_height = st.query(l, r);

            // ── New height calculate karo ────────────────────────────────────
            // Naya square curr_height ke upar baithega
            // Uski top = curr_height + apna size
            // ────────────────────────────────────────────────────────────────
            int new_height = curr_height + size;

            // ── Update: Is range ko new_height se update karo ────────────────
            // Agle squares jab is range pe query karenge
            // toh unhe new_height milegi base mein
            // ────────────────────────────────────────────────────────────────
            st.update(l, r, new_height);

            // Global max update karo aur answer mein daalo
            max_height = max(max_height, new_height);
            ans.push_back(max_height);
        }

        return ans;
    }
};

// ════════════════════════════════════════════════════════════════════════════
// MAIN
// ════════════════════════════════════════════════════════════════════════════
int main() {
    Solution sol;

    // Example 1: [[1,2],[2,3],[6,1]] → [2,5,5]
    vector<vector<int>> pos1 = {{1,2},{2,3},{6,1}};
    vector<int> res1 = sol.fallingSquares(pos1);
    cout << "Example 1: ";
    for (int x : res1) cout << x << " ";
    cout << "\nExpected:  2 5 5\n\n";

    // Example 2: [[100,100],[200,100]] → [100,100]
    vector<vector<int>> pos2 = {{100,100},{200,100}};
    vector<int> res2 = sol.fallingSquares(pos2);
    cout << "Example 2: ";
    for (int x : res2) cout << x << " ";
    cout << "\nExpected:  100 100\n";

    return 0;
}