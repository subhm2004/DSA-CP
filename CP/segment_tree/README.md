# CP — Segment Tree

Range queries, lazy propagation, persistent.

**Path:** [`CP/segment_tree/`](./)

## Subfolders

| Folder | README |
|--------|--------|
| [types_of_segment_tree/](./types_of_segment_tree/) | [Open →](./types_of_segment_tree/README.md) | 1D + **2D** seg trees (24 files) |
| [merge_sort_tree/](./merge_sort_tree/) | [Open →](./merge_sort_tree/README.md) | (10 files) |

## Files (23)

| File | Type / Notes |
|------|------------------|
| [2d_segment_tree_legacy.cpp](./2d_segment_tree_legacy.cpp) | 2D seg tree (legacy) |
| [affine_lazy_segment_tree.cpp](./affine_lazy_segment_tree.cpp) | Range `×a+b` update + range sum |
| [all_trees.cpp](./all_trees.cpp) | Collection / reference |
| [bitwise_and_or_segment_tree.cpp](./bitwise_and_or_segment_tree.cpp) | Range AND / OR + point update |
| [dynamic_segment_tree.cpp](./dynamic_segment_tree.cpp) | Sparse indices, on-demand nodes |
| [euler_tour_plus_segment_tree.cpp](./euler_tour_plus_segment_tree.cpp) | Tree → flat array + seg tree |
| [gcd_problem_segment_tree.cpp](./gcd_problem_segment_tree.cpp) | Range GCD + point update |
| [k_smallest_number_in_range.cpp](./k_smallest_number_in_range.cpp) | → redirect to `merge_sort_tree/` |
| [lazy_propogation.cpp](./lazy_propogation.cpp) | Lazy propagation basics |
| [lazy_propogation_root.cpp](./lazy_propogation_root.cpp) | Range add + range sum |
| [max_subarray_sum_segment_tree.cpp](./max_subarray_sum_segment_tree.cpp) | Max subarray sum in `[L,R]` (Kadane merge) |
| [LC_2940_Segment_tree_+_Binary_search.cpp](./LC_2940_Segment_tree_+_Binary_search.cpp) | LC 2940 |
| [LC_699_falling_squares.cpp](./LC_699_falling_squares.cpp) | LC 699 |
| [leetcode_218_skyline_problem.cpp](./leetcode_218_skyline_problem.cpp) | LC 218 skyline |
| [li_chao_segment_tree.cpp](./li_chao_segment_tree.cpp) | Lines `y=mx+c`, min at point x |
| [min_max_segment_tree.cpp](./min_max_segment_tree.cpp) | Min/max + lazy range add |
| [persistent_segment_tree.cpp](./persistent_segment_tree.cpp) | Versioned range sum |
| [range_assign_lazy_segment_tree.cpp](./range_assign_lazy_segment_tree.cpp) | Range set + range add + range sum |
| [segment_tree_2d.cpp](./segment_tree_2d.cpp) | 2D point update + submatrix sum |
| [segment_tree_2d_important.cpp](./segment_tree_2d_important.cpp) | 2D seg tree (important) |
| [segment_tree_beats.cpp](./segment_tree_beats.cpp) | Range chmin/chmax/add + sum |
| [subtree_query_problems.cpp](./subtree_query_problems.cpp) | Euler tour subtree queries |
| [variations_in_seg_tree.cpp](./variations_in_seg_tree.cpp) | SUM 3 variations (legacy — see `types_of_segment_tree/`) |
| [types_of_segment_tree/](./types_of_segment_tree/) | **sum, max, min, xor, gcd** — point/range update × 3 each |
| [xor_segment_tree.cpp](./xor_segment_tree.cpp) | Range XOR + point update |

## By type (quick pick)

| Need | File |
|------|------|
| Sum/max/min/**min_max**/xor/gcd — 3 update types | [`types_of_segment_tree/`](./types_of_segment_tree/) |
| 2D matrix point update + submatrix query | [`types_of_segment_tree/segment_tree_2d/`](./types_of_segment_tree/segment_tree_2d/) |
| Sum + range add | `lazy_propogation_root.cpp` |
| Range set (assign) + sum | `range_assign_lazy_segment_tree.cpp` |
| Max subarray sum in range | `max_subarray_sum_segment_tree.cpp` |
| Min/max + range add | `min_max_segment_tree.cpp` |
| GCD (non-invertible) | `gcd_problem_segment_tree.cpp` |
| AND / OR (non-invertible) | `bitwise_and_or_segment_tree.cpp` |
| XOR range | `xor_segment_tree.cpp` |
| Affine `×a+b` on range | `affine_lazy_segment_tree.cpp` |
| chmin/chmax beats | `segment_tree_beats.cpp` |
| K-th smallest / order stats | `merge_sort_tree/` |
| Lines min at x | `li_chao_segment_tree.cpp` |
| Historical versions | `persistent_segment_tree.cpp` |
| Huge coordinate range | `dynamic_segment_tree.cpp` |
| Tree on graph | `euler_tour_plus_segment_tree.cpp` |
| Values 1e9, indices chhote | [`coordinate_compression/`](../coordinate_compression/) — compress karke seg tree/BIT lagao |

---
**Status:** ✅ Good coverage
