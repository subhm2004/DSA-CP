# Types of Segment Tree

Har **operation** (sum, max, min, **min_max**, xor, gcd) ke liye **3 classic variations** — alag standalone files.

**Path:** [`CP/segment_tree/types_of_segment_tree/`](./)

## Folder structure

```
types_of_segment_tree/
├── sum/
│   ├── point_update_range_query.cpp      ← lazy NAHI
│   ├── range_update_point_query.cpp      ← lazy HAAN (range add)
│   └── range_update_range_query.cpp      ← lazy HAAN (range add)
├── max/   (same 3 files)
├── min/   (same 3 files)
├── min_max/   (same 3 files — min + max DONO ek tree me, ek lazy)
├── xor/   (same 3 files — lazy XOR, odd-length rule)
├── gcd/   (point update main; lazy files me note)
└── segment_tree_2d/   (2D matrix — point update + submatrix query)
    ├── sum/   compact_array + tree_of_trees
    ├── max/   compact_array
    ├── min/   compact_array
    └── min_max/ compact_array
```

## 3 variations — kab kaunsa?

| # | Update | Query | Lazy? | Kab use |
|---|--------|-------|-------|---------|
| 1 | Point (ek index) | Range | ❌ | LC 307 style — simple tree |
| 2 | Range (poori range) | Point (ek index) | ✅ | Bahut range updates, kuch points ki value |
| 3 | Range | Range | ✅ | Dono heavy — range add + range query |

**Rule:** Jab **range update** ho → **lazy propagation** lagta hai.

## Operations

| Folder | Merge | No-overlap identity | Lazy note |
|--------|-------|---------------------|-----------|
| `sum/` | `a + b` | `0` | `seg += lazy * len` |
| `max/` | `max(a,b)` | `INT_MIN` | `seg += lazy` (range add) |
| `min/` | `min(a,b)` | `INT_MAX` | `seg += lazy` (range add) |
| `min_max/` | min + max **dono** | `INT_MAX` / `INT_MIN` | **ek lazy** — dono trees sync |
| `xor/` | `a ^ b` | `0` | `seg ^= lazy` if odd len |
| `gcd/` | `gcd(a,b)` | `0` | **sirf point update** — range add lazy invalid |

## Min + Max ek saath — kab use?

| Situation | Use |
|-----------|-----|
| Sirf min **ya** sirf max chahiye | `min/` ya `max/` folder |
| **Dono** queries same array pe | `min_max/` — ek build, do answers, **ek lazy** |
| Reference (parent folder) | [`../min_max_segment_tree.cpp`](../min_max_segment_tree.cpp) |

**Idea:** `miniTree[i]` aur `maxiTree[i]` alag arrays, lekin range add uniform hai → lazy **shared**.

## 2D Segment Tree

[`segment_tree_2d/`](./segment_tree_2d/) — matrix pe point update + rectangle query.

| Folder | Kya hai |
|--------|---------|
| `sum/` | Compact 2D array + tree-of-trees (samajhne ke liye) |
| `max/`, `min/`, `min_max/` | Compact array submatrix max/min/dono |
| `xor/` | Submatrix XOR — merge `^`, identity `0` |
| `gcd/` | Submatrix GCD — merge `gcd`, **sirf point update** (lazy invalid) |

## Old file

[`../variations_in_seg_tree.cpp`](../variations_in_seg_tree.cpp) — ab **sirf SUM** ke teeno ek file me; naya structure yahan split hai.

---
**Status:** ✅ Complete (18 + 8 = 26 files)
