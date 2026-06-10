#include <bits/stdc++.h>
using namespace std;

// ════════════════════════════════════════════════════════════════════════════
// COORDINATE COMPRESSION — Bade values ko chhote indices me map karo
// ────────────────────────────────────────────────────────────────────────────
// Problem: values 1e9 tak ho sakti hain lekin distinct kam hain.
//          BIT/Segment Tree ke liye chhota index chahiye.
// Approach: unique values sort karo, 0,1,2,... id assign karo.
//
// compress[x] -> compressed id
// rev_map[id] -> original value
// ════════════════════════════════════════════════════════════════════════════

class Coordinate_Compression
{
public:
    unordered_map<int, int> compress; // original -> compressed id
    vector<int> rev_map;              // compressed id -> original

    // ── Constructor: array se unique sorted values nikaal ke id assign karo ─
    //   1) saare elements set me daalo — duplicates auto remove, sort ho jaate hain
    //   2) chhote se bade har unique value pe id = 0,1,2,... assign karo
    //   3) compress map me original->id, rev_map me id->original store karo
    //   4) isse BIT/segment tree ka size sirf distinct count tak limited rehta hai
    Coordinate_Compression(const vector<int> &arr)
    {
        set<int> st(arr.begin(), arr.end());
        int id = 0;
        for (int x : st)
        {
            compress[x] = id;
            rev_map.push_back(x);
            id++;
        }
    }

    // ── get_compressed: poori array ko compressed ids me convert karo ───────
    //   1) result array same size ka banao
    //   2) har index pe arr[i] ko compress map se lookup karke chhota id lo
    //   3) duplicates same id milenge — yahi compression ka fayda hai
    //   4) compressed array return karo (original values nahi, sirf ranks)
    vector<int> get_compressed(const vector<int> &arr)
    {
        vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress[arr[i]];
        return res;
    }

    // ── get_original: compressed id se wapas original value lo ──────────────
    //   1) val = compressed id (0 se rev_map.size()-1)
    //   2) rev_map[val] se wapas asli number nikalo
    //   3) answer queries me original value dikhane ke liye use hota hai
    int get_original(int val)
    {
        return rev_map[val];
    }
};

int main()
{
    vector<int> arr = {1000, 50, 1000, 200, 50, 1};

    cout << "Original Array: ";
    for (int x : arr)
        cout << x << " ";
    cout << "\n\n";

    Coordinate_Compression cc(arr);

    cout << "Compression Mapping (original -> compressed):\n";
    for (auto [val, id] : cc.compress)
        cout << "   " << val << " -> " << id << "\n";

    cout << "\nReverse Mapping (compressed -> original):\n";
    for (int i = 0; i < (int)cc.rev_map.size(); i++)
        cout << "   " << i << " -> " << cc.rev_map[i] << "\n";

    vector<int> compressed = cc.get_compressed(arr);

    cout << "\nCompressed Array: ";
    for (int x : compressed)
        cout << x << " ";
    cout << "\n";

    cout << "\nBIT size needed: " << cc.rev_map.size() << " (instead of 1001!)\n";

    return 0;
}
