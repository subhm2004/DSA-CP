# Graham's Scan — Convex Hull

**Code:** [`graham_scan_convex_hull.cpp`](./graham_scan_convex_hull.cpp)  
**Reference:** [CP-Algorithms — Convex hull construction](https://cp-algorithms.com/geometry/convex-hull.html#implementation_1)

---

## Convex hull kya hai?

Plane par **N points** diye hon. **Convex hull** = sabse chhota convex polygon jisme saare points andar ya boundary par hon.

```
    *  *                    *---*
   *    *        →         |   |
    *  *                    *---*
  (scattered)              (hull)
```

Contest / geometry problems mein hull se:
- outer boundary nikalna
- diameter / farthest pair
- point inside polygon checks
- onion layers (nested hulls)

---

## Graham's Scan — idea

1972, Ronald Graham. **Polar angle sort + stack.**

| Step | Kya hota hai | Time |
|------|----------------|------|
| 1 | **p0** = bottom-most point (min `y`, tie → min `x`) | O(n) |
| 2 | Baaki points ko **p0 ke around polar angle** se sort (clockwise) | O(n log n) |
| 3 | Stack par scan: jab tak last 3 points **clockwise turn** na banaye, pop karo | O(n) amortized |
| 4 | Stack = hull vertices **clockwise order** mein | — |

**Total:** O(n log n) time, O(n) space — optimal comparison-based.

---

## Kab use karein?

| Situation | Graham's scan? |
|-----------|----------------|
| 2D points se hull chahiye, offline | ✅ Best choice (simple, fast) |
| Collinear boundary points **include** karne hain | ✅ `include_collinear = true` |
| Sirf integer coordinates, cross product overflow se bachna | ✅ `long long` orientation (is repo mein) |
| Points already **x-sorted** stream mein aa rahe hain | ⚠️ [Monotone chain](./convex_hull.cpp) thoda cleaner |
| 3D convex hull | ❌ alag algorithm |
| Dynamic insert/delete | ❌ dono static algorithms |

### Graham vs Monotone Chain (Andrew)

| | **Graham's scan** | **Monotone chain** ([`convex_hull.cpp`](./convex_hull.cpp)) |
|--|-------------------|-------------------------------------------------------------|
| Sort key | Polar angle around p0 | `(x, y)` lexicographic |
| Scan | Ek stack, ek pass feel | Upper + lower hull, do passes |
| Collinear on horizontal edge | Extra reverse step | `include_collinear` flag + degenerate check |
| Code length | Thoda zyada (polar sort) | Often shorter in contests |
| Complexity | O(n log n) | O(n log n) |

**Practical tip:** Dono same complexity. Jo yaad ho / jo template ready ho — use karo. Is repo mein **dono** rakhe hain taaki compare kar sako.

---

## Orientation & clockwise turn

Graham scan har step par check karta hai: teen consecutive points **clockwise turn** banate hain ya nahi.

```text
orientation(a, b, c):
  v = a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y)

  v < 0  → clockwise
  v > 0  → counter-clockwise
  v = 0  → collinear
```

Ye wahi signed area idea hai jo [`oriented_triangle_area.cpp`](./oriented_triangle_area.cpp) mein hai — hull pop tab hota hai jab turn convex nahi rehta.

---

## `include_collinear` flag

| Value | Hull mein kya aata hai |
|-------|-------------------------|
| `false` (default) | Sirf **corner** vertices — collinear edge points hata diye |
| `true` | Collinear points bhi boundary par rehte hain (Kattis / some OJ format) |

**Collinear `true` ke baad:** farthest collinear points ke order ke liye CP-Algo extra **reverse** step use karta hai (code mein included).

**Degenerate:** saare points ek line par → `include_collinear = false` se hull 2 points; `true` se poori line.

---

## API (is repo)

```cpp
void convex_hull_graham(vector<Point> &a, bool include_collinear = false);
```

- Input: `a` = point list  
- Output: `a` replace ho kar hull vertices (clockwise)  
- `Point`: `long long x, y`

---

## Compile & run

```bash
g++ -std=c++17 -O2 CP/geometry/graham_scan_convex_hull.cpp -o sol && ./sol
```

---

## Practice problems (CP-Algo list)

| Problem | Link |
|---------|------|
| Kattis — Convex Hull | [open.kattis.com/problems/convexhull](https://open.kattis.com/problems/convexhull) |
| Kattis — Keep the Parade Safe | [open.kattis.com/problems/parade](https://open.kattis.com/problems/parade) |
| Codeforces — Birthday | CF 598F |
| Onion Layers | LA 2006 |
| Timus 1185 — Wall | timus.online |

---

## Related files (is folder mein)

| File | Topic |
|------|--------|
| [`convex_hull.cpp`](./convex_hull.cpp) | Monotone chain (Andrew) |
| [`oriented_triangle_area.cpp`](./oriented_triangle_area.cpp) | Signed area / CW / CCW |
| [`ccw_orientation.cpp`](./ccw_orientation.cpp) | Orientation triplet test |

---

## Quick cheat sheet

```text
Need hull?  → Graham OR Monotone chain (O(n log n))
Need CW?    → Graham naturally outputs clockwise
Collinear?  → pass include_collinear = true
Overflow?   → long long coordinates + long long cross
```
