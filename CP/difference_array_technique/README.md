# CP — Difference Array Technique

C++ implementations for this topic.

**Path:** [`CP/difference_array_technique/`](./)

## Files (3)

| File | LeetCode / Notes |
|------|------------------|
| [difference_array_1d.cpp](./difference_array_1d.cpp) | Range update [l,r] += val on array (offline / batch updates) |
| [range_update_point_query.cpp](./range_update_point_query.cpp) | Multiple range add updates, then point query |
| [difference_array_with_jumps.cpp](./difference_array_with_jumps.cpp) | **Diff array + jumps** — LC 1871 Jump Game VII, LC 3655 mult diff |

### Difference Array with Jumps — kab use karo?

| Situation | Naive | With diff array |
|-----------|-------|-----------------|
| Index `i` se `[i+minJ, i+maxJ]` tak jump | Har `i` pe window scan O(window) | `diff[l]+=val`, `diff[r+1]-=val` O(1) |
| "Kya last tak pahunch sakte?" | DP O(n × window) | Prefix `cur` O(n) |
| "Kitne tareeke?" | Same TLE | `diff` me `cur` paths propagate |
| Range multiply on `l, l+k, l+2k...` (LC 3655) | Har query O(n/k) | `diff[l]*=v`, `diff[R]*=v⁻¹`, prefix product |

---
**Status:** 🟡 Basic
