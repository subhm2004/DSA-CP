#pragma once
#include <bits/stdc++.h>

// ════════════════════════════════════════════════════════════════════════════
// COORDINATE COMPRESSION — Shared Header
// ────────────────────────────────────────────────────────────────────────────
// Bade values (1e9) ko chhote indices (0,1,2,...) me map karo.
// BIT / Segment Tree ka size = distinct count (memory bachta hai).
//
// compress[x]  → compressed id (0-based)
// rev_map[id]  → original value (sorted order)
// ════════════════════════════════════════════════════════════════════════════

class Coordinate_Compression {
public:
    std::unordered_map<int, int> compress;
    std::vector<int> rev_map;

    /*
     * Coordinate_Compression(arr)
     * -------------------------
     * Constructor: array ki unique values sort karke id assign.
     *
     *   1) set<int> me daalo — auto sort + duplicate remove
     *   2) chhote se bade id = 0,1,2,...
     *   3) compress map + rev_map dono bharo
     *
     * Pool trick: arr me sirf nums nahi — query boundaries bhi daal sakte ho
     *             (same constructor, koi bhi vector<int> pass karo).
     */
    Coordinate_Compression(const std::vector<int>& arr) {
        std::set<int> st(arr.begin(), arr.end());
        int id = 0;
        for (int x : st) {
            compress[x] = id;
            rev_map.push_back(x);
            id++;
        }
    }

    /*
     * get_compressed(arr)
     * Har element ko compress[arr[i]] se replace karke vector return.
     */
    std::vector<int> get_compressed(const std::vector<int>& arr) const {
        std::vector<int> res(arr.size());
        for (int i = 0; i < (int)arr.size(); i++)
            res[i] = compress.at(arr[i]);
        return res;
    }

    /*
     * get_original(val)
     * Compressed id → original value (rev_map lookup).
     */
    int get_original(int val) const { return rev_map[val]; }

    /*
     * size()
     * Kitne unique values compress hue — yahi BIT size hota hai.
     */
    int size() const { return (int)rev_map.size(); }

    /*
     * count_le(x)
     * Kitne unique values ≤ x hain.
     * rev_map sorted hai → upper_bound(x) - begin.
     */
    int count_le(int x) const {
        return (int)(std::upper_bound(rev_map.begin(), rev_map.end(), x)
                     - rev_map.begin());
    }

    /*
     * bit_id(x)
     * Value x ka 1-indexed BIT position (compress[x] + 1).
     * BIT 1-indexed hota hai isliye +1.
     */
    int bit_id(int x) const { return compress.at(x) + 1; }

    /*
     * lower_bit_id(x)
     * Sorted rev_map me pehla value ≥ x → uska 1-indexed BIT id.
     * Range query ke LEFT end ke liye (LC 327).
     */
    int lower_bit_id(int x) const {
        return (int)(std::lower_bound(rev_map.begin(), rev_map.end(), x)
                     - rev_map.begin()) + 1;
    }

    /*
     * upper_bit_id(x)
     * prefixSum(upper_bit_id(x)) = frequency of values ≤ x.
     * LC 493 me threshold se chhote/equal count ke liye.
     */
    int upper_bit_id(int x) const { return count_le(x); }
};

// ────────────────────────────────────────────────────────────────────────────
// Long long version — prefix sums, 2*nums (LC 327, LC 493)
// ────────────────────────────────────────────────────────────────────────────
class Coordinate_Compression_LL {
public:
    std::unordered_map<long long, int> compress;
    std::vector<long long> rev_map;

    /*
     * Coordinate_Compression_LL(arr)
     * int version jaisa — bas long long values support.
     */
    Coordinate_Compression_LL(const std::vector<long long>& arr) {
        std::set<long long> st(arr.begin(), arr.end());
        int id = 0;
        for (long long x : st) {
            compress[x] = id;
            rev_map.push_back(x);
            id++;
        }
    }

    int size() const { return (int)rev_map.size(); }

    int count_le(long long x) const {
        return (int)(std::upper_bound(rev_map.begin(), rev_map.end(), x)
                     - rev_map.begin());
    }

    int bit_id(long long x) const { return compress.at(x) + 1; }

    int lower_bit_id(long long x) const {
        return (int)(std::lower_bound(rev_map.begin(), rev_map.end(), x)
                     - rev_map.begin()) + 1;
    }

    int upper_bit_id(long long x) const { return count_le(x); }
};
