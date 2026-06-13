# CP — Difference Array Technique

C++ implementations for this topic.

**Path:** [`CP/difference_array_technique/`](./)

## Files (5)

| File | LeetCode / Notes |
|------|------------------|
| [difference_array_1d.cpp](./difference_array_1d.cpp) | Range update [l,r] += val on array (offline / batch updates) |
| [difference_array_2d.cpp](./difference_array_2d.cpp) | **2D submatrix** — `DiffArray2DAdd` (+val) + `DiffArray2DMultiply` (*val) |
| [range_update_point_query.cpp](./range_update_point_query.cpp) | Multiple range add updates, then point query |
| [difference_array_with_jumps.cpp](./difference_array_with_jumps.cpp) | **[L,R,val,k] additive jump diff** |
| [leetcode_3655_xor_range_multiply.cpp](./leetcode_3655_xor_range_multiply.cpp) | **LC 3655** — sqrt threshold + multiplicative jump diff |

### 1D vs 2D Difference Array

| | 1D | 2D Add | 2D Multiply |
|--|-----|--------|-------------|
| Range | `[l, r]` | `[r1,c1]..[r2,c2]` | same |
| Marks | 2 | 4 corners `+=` | 4 corners `*=` |
| Rebuild | 1D prefix sum | 2D prefix sum | 2D prefix product |
| Class | `DiffArray` | `DiffArray2DAdd` | `DiffArray2DMultiply` |

### Difference Array with Jumps — kab use karo?

| Situation | Naive | With diff array |
|-----------|-------|-----------------|
| **[L,R,val,k] jump range add** | Har query O((R-L)/k) walk | `diff[L]+=val`, `diff[stop]-=val`, prefix on chain |
| Index `i` se `[i+minJ, i+maxJ]` tak jump (reachability) | Har `i` pe window scan | sliding window diff O(n) |
| Range multiply on `l, l+k, l+2k...` (LC 3655) | Har query O(n/k) | `SqrtThreshold` + `MultiplicativeDiffJump` |

---
**Status:** 🟡 Basic
