# CP Template

**Ek lean file — roz contest ke liye. Bhaari DS ke liye `CP/` library use karo.**

## File

| File | Description |
|------|-------------|
| [**cp_template.cpp**](./cp_template.cpp) | Copy → `solve()` me logic |

## Isme kya hai (roz ka kaam)

- Fast I/O + `dbg()` (`-DLOCAL`)
- Mod: `modPow`, `modInv`, `modMul`
- `Comb` — nCr (jab chahiye tab `Comb C(n);` banao)
- `DSU`, `Fenwick`, `dijkstra`
- `bsMin` / `bsMax` — binary search on answer

## Isme nahi hai (jaan-boojh kar)

SegTree, lazy segtree, FFT, flows, Mo's, PBDS — har contest me nahi chahiye, file moti ho jati hai.  
Copy from: [`CP/`](../CP/) (topic folder + README).

## Use

```bash
cp CP_Template/cp_template.cpp sol.cpp
# solve() edit karo
g++ -std=c++17 -O2 -DLOCAL sol.cpp -o sol && ./sol
```

Local: same folder me `input.txt` rakho.

Single test / no `t`? `main()` me `cin >> t` hata do ya `int t = 1;` rakho.

Full library: [`CP/`](../CP/) | DSA: [`DSA/`](../DSA/)
