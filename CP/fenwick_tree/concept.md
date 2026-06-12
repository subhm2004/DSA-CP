# Fenwick Tree (BIT) — Complete Concept Guide

**Path:** [`CP/fenwick_tree/`](./)  
**Main code:** [`fenwick_tree.cpp`](./fenwick_tree.cpp) — teen classic variations

---

## Fenwick Tree kya hai?

**Fenwick Tree** = **Binary Indexed Tree (BIT)**

Ek array jisme har index **kuch prefix ranges** ka sum (ya frequency) store karta hai — lekin segment tree jitna heavy nahi.

```
Normal array:     [ ?,  ?,  ?,  ?,  ? ]   → sirf elements
Fenwick (BIT):    [0, a, b, c, d, e]     → index 0 dummy, 1..n use (1-indexed!)
```

**Memory:** `O(n)` — segment tree `O(4n)` se half  
**Update / Query:** `O(log n)`  
**Code:** ~10 lines — segment tree se bahut chhota

---

## Ek line rule — kab use karo?

```
Operation INVERTIBLE hai?  (sum, XOR — undo ho sakta hai)
  + Point update + Prefix/Range query chahiye?
    → FENWICK TREE ✓

GCD / Min / Max chahiye?        → Segment Tree
Heavy range updates?            → Lazy Segment Tree
Order statistics (k-th)?          → Merge Sort Tree
```

| Situation | Use |
|-----------|-----|
| Prefix sum, range sum | BIT variation 1 |
| Range add, point value | BIT variation 2 |
| Range add, range sum | BIT variation 3 (do BIT) |
| Count inversions / smaller / pairs | BIT + coordinate compression |
| Prefix XOR | XOR BIT (`fenwick_tree_xor.cpp`) |
| 2D grid sum | 2D BIT (`fenwick_tree_2d.cpp`) |

---

## Core trick: `i & -i` (LSB — Lowest Set Bit)

Yeh **poora BIT** isi ek line pe tikta hai.

### `i & -i` kya deta hai?

Rightmost `1` bit ka value.

```
i = 12  →  binary 1100
-i       →  two's complement 0100
i & -i   →  0100 = 4

i = 6   →  0110  →  i & -i = 2
i = 5   →  0101  →  i & -i = 1
i = 8   →  1000  →  i & -i = 8
```

### Kyun kaam karta hai?

Har index `i` BIT me **kuch specific range** cover karta hai.  
`i & -i` batata hai: **agla kaun sa index update/query me include hoga**.

```
Index:  1  2  3  4  5  6  7  8
        |  |  |  |  |  |  |  |
i=4 covers length 4: [1..4] ya similar blocks (tree structure)

UPDATE: i += (i & -i)  →  UPAR jaate hue affected nodes update
QUERY:  i -= (i & -i)  →  NEECHE aate hue prefix sum nikalo
```

### Update loop (point add)

```cpp
void update(int i, ll x) {
    for (; i <= n; i += (i & -i))   // har step pe parent block
        bit[i] += x;
}
```

**Example:** `n=8`, index `3` pe `+5` add karo

```
i=3: bit[3] += 5,  i += 1 → i=4
i=4: bit[4] += 5,  i += 4 → i=8
i=8: bit[8] += 5,  i += 8 → i=16 > n, stop
```

Sirf **3 nodes** update — `O(log n)`.

### Query loop (prefix sum)

```cpp
ll prefixSum(int i) {
    ll total = 0;
    for (; i > 0; i -= (i & -i))   // har step pe ek block subtract
        total += bit[i];
    return total;
}
```

**Example:** `prefixSum(5)` for `n=8`

```
i=5: total += bit[5],  i -= 1 → i=4
i=4: total += bit[4],  i -= 4 → i=0, stop
```

`[1..5]` ka sum — **2 steps**, `O(log n)`.

---

## Prefix sum trick — Range query

BIT naturally **prefix** deta hai: `sum(1..i)`.

**Range `[l, r]` ka sum** = inclusion-exclusion:

```
rangeSum(l, r) = prefixSum(r) - prefixSum(l - 1)
```

```
Array:  [_, 2, 5, 3, 8, 1]   (1-indexed, _ = dummy 0)

prefixSum(3) = 2+5+3 = 10   → [1..3]
prefixSum(1) = 2             → [1..1]
rangeSum(2,4) = prefixSum(4) - prefixSum(1) = (2+5+3+8) - 2 = 16
```

Yahi `fenwick_tree.cpp` me `BIT_PointUpdate_RangeQuery::rangeSum()` karta hai.

---

## `fenwick_tree.cpp` — Teen variations (detailed)

### 1️⃣ Point Update + Range Query (sabse common)

**File class:** `BIT_PointUpdate_RangeQuery`

| Operation | Kya karta hai |
|-----------|---------------|
| `update(i, x)` | `arr[i] += x` (point add) |
| `prefixSum(i)` | `arr[1] + ... + arr[i]` |
| `rangeSum(l, r)` | `arr[l] + ... + arr[r]` |

**Kab use:**
- Subarray sum queries
- Frequency count (update = +1)
- Inversion count, LC 315 (frequency BIT)

**Demo (`main` me):**
```cpp
bit1.update(2, 10);   // index 2 pe +10
bit1.update(4, 5);    // index 4 pe +5
rangeSum(1,3)          // [1,3] ka sum
```

**Complexity:** update `O(log n)`, query `O(log n)`

---

### 2️⃣ Range Update + Point Query (difference array trick)

**File class:** `BIT_RangeUpdate_PointQuery`

**Problem:** Poori range `[l,r]` me `+x` karna hai, lekin **ek index** ki value poochni hai — har element tak walk nahi karna.

**Trick — Difference array on BIT:**

Normal difference array:
```
range [l,r] me +v:
  diff[l]   += v
  diff[r+1] -= v

arr[i] = diff[1] + diff[2] + ... + diff[i]  (prefix sum!)
```

BIT pe same:
```cpp
void rangeAdd(int l, int r, ll x) {
    // l se start: +x effect
    for (int i = l; i <= n; i += (i & -i))
        bit[i] += x;
    // r+1 se: effect band
    for (int i = r + 1; i <= n; i += (i & -i))
        bit[i] -= x;
}

ll pointQuery(int i) {
  // prefix sum of diff = actual arr[i]
    for (; i > 0; i -= (i & -i))
        total += bit[i];
}
```

**Walkthrough:** `n=5`, `rangeAdd(2, 4, 5)`

```
Diff array conceptually: [0, 0, +5, 0, 0, -5, 0]
pointQuery(3) = prefix = 5  ✓
pointQuery(1) = 0             ✓
pointQuery(5) = 0             ✓
```

Phir `rangeAdd(1, 3, 2)` — overlapping ranges bhi sahi kaam karti hain.

**Kab use:**
- Bahut range adds, sirf kuch indices ki value chahiye
- Painting / lazy effect without full lazy seg tree

**File:** `fenwick_range_update.cpp` (standalone version bhi hai)

---

### 3️⃣ Range Update + Range Query (do BIT trick)

**File class:** `BIT_RangeUpdate_RangeQuery`

**Problem:** Range me `+x` **aur** range ka **sum** bhi chahiye — variation 2 sirf point query deta hai.

**Idea:** Do BITs (`Bit1`, `Bit2`) se prefix sum reconstruct karo.

Range `[l,r]` me `+x` lagane ka math:

```
Bit1:  difference style     →  add(l, +x), add(r+1, -x)
Bit2:  weighted difference  →  add(l, +x*(l-1)), add(r+1, -x*r)

Actual prefix sum at i:
  prefSum(i) = sum(Bit1, i) * i - sum(Bit2, i)

Range sum:
  rangeSum(l, r) = prefSum(r) - prefSum(l-1)
```

**Kyun `Bit2` chahiye?**

Sirf `Bit1` se prefix nahi milta jab range adds ho chuki hon — linear correction term `x*(l-1)` chahiye.

**Demo (`main` me):**
```cpp
bit3.rangeAdd(1, 3, 2);   // [1,3] me sabko +2
bit3.rangeAdd(2, 5, 3);   // [2,5] me sabko +3
rangeSum(1,3)             // overlapping adds handle
```

**Kab use:**
- Range add + range sum dono heavy
- Segment tree lazy ka lightweight alternative (sirf sum ke liye)

---

## 1-indexed kyun?

BIT **hamesha 1-indexed** hota hai:

```cpp
vector<ll> bit(n + 1, 0);  // bit[0] dummy, use bit[1..n]
```

**Reason:** `i & -i` tab clean kaam karta hai jab `i >= 1`.  
`i=0` pe `i & -i = 0` → infinite loop!

CP me ya to:
- Array 1-indexed treat karo, **ya**
- 0-indexed array me `update(i+1, x)` karo

---

## Frequency BIT pattern (order statistics)

Jab BIT me **count / frequency** store ho (sum ki jagah):

```cpp
// Element x ko dekha — frequency +1
bit.add(cc.bit_id(x), 1);

// Kitne elements < x?
bit.prefixSum(cc.compress[x]);   // rank se chhote
```

| Problem | Scan | BIT me kya | Query |
|---------|------|------------|-------|
| **LC 315** smaller after self | Right→Left | Right wale freq | count `< nums[i]` |
| **Inversion count** | Left→Right | Left wale freq | count `> arr[i]` |
| **LC 493** reverse pairs | Left→Right | Left wale freq | count `> 2*nums[j]` |
| **LC 327** range sum | Left→Right | Prefix freq | count in `[lo,hi]` |

**Coordinate compression zaruri:** values `1e9` ho sakti hain → [`coordinate_compression.h`](../coordinate_compression/coordinate_compression.h)

---

## Problem → File map

| Problem type | File | Variation |
|--------------|------|-----------|
| Point add + range sum | `fenwick_tree.cpp` | 1️⃣ |
| Range add + point query | `fenwick_tree.cpp`, `fenwick_range_update.cpp` | 2️⃣ |
| Range add + range sum | `fenwick_tree.cpp` | 3️⃣ |
| LC 315 smaller after self | `leetcode_315_count_smaller_after_self.cpp` | Freq BIT + compression |
| LC 327 count range sum | `leetcode_327_count_of_range_sum.cpp` | Prefix + Freq BIT |
| LC 493 reverse pairs | `leetcode_493_reverse_pairs.cpp` | Freq BIT + compression |
| Inversion count | `count_inversion_fenwick_tree.cpp` | Freq BIT |
| Count `> x` in array | `Count_of_number...cpp` | Freq BIT |
| XOR prefix/range | `fenwick_tree_xor.cpp` | XOR instead of + |
| 2D submatrix sum | `fenwick_tree_2d.cpp` | 2D BIT |
| Tree subtree sum | `../euler_tour/euler_tour_subtree_sum_fenwick.cpp` | Euler tour + BIT |

---

## BIT vs Segment Tree (quick)

| | Fenwick Tree | Segment Tree |
|--|--------------|--------------|
| Memory | `O(n)` | `O(4n)` |
| Code | ~15 lines | ~50+ lines |
| Sum / XOR | ✅ Best | ✅ Works |
| Min / Max / GCD | ❌ | ✅ |
| Range update + range query | ⚠️ Do-BIT (sum only) | ✅ Lazy |
| Non-invertible ops | ❌ | ✅ |

---

## Decision flow

```
Problem padho
    │
    ├─ Sum ya XOR + updates?
    │       NO → Segment tree dekho
    │       YES ↓
    │
    ├─ Kya update/query type?
    │       Point update + range sum     → Variation 1️⃣
    │       Range add + point value      → Variation 2️⃣
    │       Range add + range sum        → Variation 3️⃣
    │       Count pairs / inversions     → Freq BIT + compression
    │
    └─ Values badi (1e9)?
            YES → coordinate_compression.h pehle
            NO  → direct BIT
```

---

## Cheat sheet (copy-paste yaad)

```cpp
// ── Variation 1: Point update + Range sum ──
void update(int i, ll x) {
    for (; i <= n; i += i & -i) bit[i] += x;
}
ll prefix(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += bit[i];
    return s;
}
ll range(int l, int r) { return prefix(r) - prefix(l - 1); }

// ── Variation 2: Range add + Point query ──
void rangeAdd(int l, int r, ll x) {
    for (int i = l; i <= n; i += i & -i) bit[i] += x;
    for (int i = r + 1; i <= n; i += i & -i) bit[i] -= x;
}
ll point(int i) { /* same prefix loop */ }

// ── Variation 3: Range add + Range sum ──
// Bit1, Bit2 + prefSum(i) = sum(B1,i)*i - sum(B2,i)
```

---

## Related folders

| Topic | Path |
|-------|------|
| Coordinate compression | [`../coordinate_compression/`](../coordinate_compression/) |
| Segment tree (alternative) | [`../segment_tree/`](../segment_tree/) |
| Euler tour + BIT | [`../euler_tour/`](../euler_tour/) |

---

## Ek line me yaad karo

> **Invertible op (sum/XOR) + point/range queries + simple code → Fenwick Tree. `i & -i` = poora magic.**

Pehle `fenwick_tree.cpp` run karo, phir specific problem file kholo.
