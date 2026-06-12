# CP — Sqrt Decomposition

Block size ~√n — simple alternative jab O(n) brute force slow ho aur segment tree heavy ho.

**Path:** [`CP/sqrt_decomposition/`](./)

## Kya hai?

Array ko `√n` size ke blocks me todo. Har block ka **precomputed answer** (sum, min, GCD, freq map) rakho.

```
Query [L,R]:
  left partial block  → scan O(√n)
  middle full blocks  → O(1) per block
  right partial block → scan O(√n)
Total: O(√n)
```

## Kab use karo?

| Situation | Approach |
|-----------|----------|
| Range sum + point update | `sqrt_decomposition.cpp` |
| Range min + point update | `sqrt_range_min_query.cpp` |
| Range GCD (non-invertible) | `sqrt_range_gcd_query.cpp` |
| Range add + range sum | `sqrt_lazy_range_add_sum.cpp` |
| Count distinct in range (offline) | `mos_algorithm_count_distinct.cpp` |
| Count value freq in range (LC 2080) | `leetcode_2080_range_frequency_queries.cpp` |

## Files (6)

| File | Problem / Notes |
|------|------------------|
| [sqrt_decomposition.cpp](./sqrt_decomposition.cpp) | Range sum + point update |
| [sqrt_range_min_query.cpp](./sqrt_range_min_query.cpp) | Range min + point update |
| [sqrt_range_gcd_query.cpp](./sqrt_range_gcd_query.cpp) | Range GCD + point update |
| [sqrt_lazy_range_add_sum.cpp](./sqrt_lazy_range_add_sum.cpp) | Range add + range sum (lazy on blocks) |
| [mos_algorithm_count_distinct.cpp](./mos_algorithm_count_distinct.cpp) | **Mo's** — distinct count in range |
| [leetcode_2080_range_frequency_queries.cpp](./leetcode_2080_range_frequency_queries.cpp) | **LC 2080** — freq in range |

## FAANG / Interview picks

| Problem | File | Kyun sqrt |
|---------|------|-----------|
| Count distinct in subarray queries | Mo's algorithm | Offline O((n+Q)√n) |
| How many times X in [L,R]? | LC 2080 | Block freq maps |
| Range add + sum (simple) | sqrt lazy | Lazy tag on full blocks |
| Range GCD with updates | sqrt GCD | GCD non-invertible |

## vs Segment Tree / Fenwick

| | Sqrt | Seg Tree | Fenwick |
|--|------|----------|---------|
| Code | Easy | Medium | Easy |
| Query | O(√n) | O(log n) | O(log n) |
| Sum | ✅ | ✅ | ✅ |
| Min/GCD | ✅ (rebuild block) | ✅ | ❌ |
| Offline distinct | ✅ Mo's | Overkill | ❌ |

---
**Status:** 🟢 Good coverage
