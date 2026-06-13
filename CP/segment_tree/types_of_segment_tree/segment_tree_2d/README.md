# 2D Segment Tree

Matrix pe **point update** + **submatrix (rectangle) query** — nested segment tree.

**Path:** [`CP/segment_tree/types_of_segment_tree/segment_tree_2d/`](./)

## Idea — "Tree of Trees"

```
Outer tree  →  ROWS (x dimension)
Inner tree  →  COLUMNS (y dimension)

Har row-node ke andar poora column segment tree hota hai.
Query: pehle rows filter (3-case), phir columns filter (3-case).
```

## Folder structure

```
segment_tree_2d/
├── sum/
│   ├── compact_array_point_update_submatrix_query.cpp   ← contest template (2D array st[][])
│   └── tree_of_trees_point_update_submatrix_query.cpp   ← samajhne ke liye (vector<SegTree1D>)
├── max/   compact_array_point_update_submatrix_query.cpp
├── min/   compact_array_point_update_submatrix_query.cpp
├── min_max/ compact_array_point_update_submatrix_query.cpp
├── xor/   compact_array_point_update_submatrix_query.cpp
└── gcd/   compact_array_point_update_submatrix_query.cpp   ← lazy NAHI (invalid)
```

## Do approaches — kab kaunsa?

| Approach | File | Pros | Cons |
|----------|------|------|------|
| **Compact 2D array** | `compact_array_*` | Fast, ek `st[vx][vy]`, contest me copy-paste easy | Thoda abstract — X/Y recursion samajhni padti hai |
| **Tree of trees** | `tree_of_trees_*` (sirf sum/) | Outer = rows, inner = real 1D seg tree object — intuitive | Zyada memory, build me merge slow |

## Common params (har file me detail hai)

| Param | Matlab |
|-------|--------|
| `vx, sx, ex` | Row tree: node index + row range `[sx, ex]` |
| `vy, sy, ey` | Col tree: node index + col range `[sy, ey]` |
| `x, y` | Point update cell |
| `x1,y1,x2,y2` | Query rectangle |

**Complexity:** build `O(n·m)`, point update `O(log n · log m)`, rectangle query `O(log n · log m)`

## 2D me lazy?

| Update type | Lazy? | Note |
|-------------|-------|------|
| Point update + submatrix query | ❌ | Yahi files — CP me 90% yahi |
| Rectangle add + submatrix sum | ✅ | 2D lazy — alag advanced topic; parent me abhi file nahi |

Rectangle add lazy ke liye dekho: [`../../segment_tree_2d.cpp`](../../segment_tree_2d.cpp) (point update wala) + future lazy file.

## Old reference files (parent folder)

| File | Note |
|------|------|
| [`../../segment_tree_2d.cpp`](../../segment_tree_2d.cpp) | Compact array sum (1-indexed vx) |
| [`../../segment_tree_2d_important.cpp`](../../segment_tree_2d_important.cpp) | Important template (0-indexed) |
| [`../../2d_segment_tree_legacy.cpp`](../../2d_segment_tree_legacy.cpp) | Tree of trees |

---
**Status:** ✅ Complete (8 files)
