# CP — Fenwick Tree

Binary Indexed Tree variants.

**Path:** [`CP/fenwick_tree/`](./)

> 📖 **Concept guide:** [`concept.md`](./concept.md) — kya hai, `i & -i` trick, teen variations, kab use karo, problem map

## Files (14)

| File | LeetCode / Notes |
|------|------------------|
| [count_inversion.cpp](./count_inversion.cpp) | Inversion count (basic) |
| [count_inversion_fenwick_tree.cpp](./count_inversion_fenwick_tree.cpp) | Inversion count — BIT + compression |
| [count_of_number_in_array_less_than_x_using_fenwick_tree.cpp](./count_of_number_in_array_less_than_x_using_fenwick_tree.cpp) | Count `< x` in array |
| [fenwick_range_update.cpp](./fenwick_range_update.cpp) | Range add, point query |
| [fenwick_tree.cpp](./fenwick_tree.cpp) | 3 classic BIT variations |
| [fenwick_tree_2d.cpp](./fenwick_tree_2d.cpp) | 2D point update + submatrix sum |
| [fenwick_tree_2d_alt.cpp](./fenwick_tree_2d_alt.cpp) | 2D BIT (alt) |
| [fenwick_tree_variations_types.cpp](./fenwick_tree_variations_types.cpp) | 3 variations reference |
| [fenwick_tree_xor.cpp](./fenwick_tree_xor.cpp) | XOR BIT 1D + 2D |
| [leetcode_315_count_smaller_after_self.cpp](./leetcode_315_count_smaller_after_self.cpp) | **LC 315** — smaller after self, BIT + compression |
| [leetcode_315_fenwick_tree.cpp](./leetcode_315_fenwick_tree.cpp) | LC 315 (older version) |
| [leetcode_327_count_of_range_sum.cpp](./leetcode_327_count_of_range_sum.cpp) | **LC 327** — range sum in [lower,upper], prefix + BIT |
| [leetcode_493_reverse_pairs.cpp](./leetcode_493_reverse_pairs.cpp) | **LC 493** — reverse pairs, BIT + compression |
| [xor_fenwick_tree.cpp](./xor_fenwick_tree.cpp) | XOR BIT (duplicate of fenwick_tree_xor) |

**Coordinate compression:** sab files `#include "../coordinate_compression/coordinate_compression.h"` use karte hain — duplicate class nahi.

## LC problems — BIT + Coordinate Compression

| LC | File | Pattern |
|----|------|---------|
| 315 | `leetcode_315_count_smaller_after_self.cpp` | Right→left scan, count smaller in BIT |
| 327 | `leetcode_327_count_of_range_sum.cpp` | Prefix sums, range query on BIT |
| 493 | `leetcode_493_reverse_pairs.cpp` | Left→right, count `> 2*nums[j]` in BIT |

---
**Status:** ✅ Good coverage
