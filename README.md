<div align="center">

# C++ — DSA & Competitive Programming

**570+ solutions** · interview prep · contest templates · searchable browser UI

[![GitHub Pages](https://img.shields.io/badge/site-GitHub%20Pages-6366f1?style=for-the-badge&logo=github)](https://subhm2004.github.io/DSA-CP/)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![DSA](https://img.shields.io/badge/DSA-332%20files-10b981?style=for-the-badge)](./DSA/)
[![CP](https://img.shields.io/badge/CP-237%20files-f59e0b?style=for-the-badge)](./CP/)

**Author:** [Shubham Malik](https://github.com/subhm2004) · [GitHub](https://github.com/subhm2004/DSA-CP)

[Browse live site](https://subhm2004.github.io/DSA-CP/) · [DSA index](./DSA/) · [CP index](./CP/) · [Contest template](./CP_Template/)

</div>

---

## At a glance

| | Count | Purpose |
|---|------:|---------|
| **DSA/** | **332** | LeetCode · FAANG · college interviews |
| **CP/** | **237** | Codeforces · AtCoder · ICPC templates |
| **CP_Template/** | **1** | Single-file contest starter |
| **Topic READMEs** | **100+** | Har folder mein file list + approach + TODO |
| **Topics (site index)** | **96** | DSA 30 + CP 66 browsable topics |

Har `.cpp` file mein **header comment** — topic, problem, approach, complexity. Jahan match ho, **LeetCode #** bhi tagged hai.

---

## Repo structure

```
C++/
├── DSA/                 Interview & FAANG — arrays, trees, graphs, DP, …
├── CP/                  Contest library — segtree, flows, strings, NT, …
├── CP_Template/         Lean single-file starter (copy → contest)
├── site/                Static browser UI (search, filter, GitHub links)
├── scripts/             README generator · site index · LeetCode tools
└── index.html           Local entry → redirects to /site/
```

| Section | Use when | Open |
|---------|----------|------|
| **[DSA](./DSA/)** | LeetCode, interviews, DSA course | [DSA/README.md](./DSA/README.md) |
| **[CP](./CP/)** | Contests, heavy templates, speed | [CP/README.md](./CP/README.md) |
| **[CP_Template](./CP_Template/)** | Live contest — ek file copy karo | [CP_Template/README.md](./CP_Template/README.md) |
| **[site/](./site/)** | Browser se search & browse | [site/README.md](./site/README.md) |

---

## Static site — search & browse

**Live:** **[https://subhm2004.github.io/DSA-CP/](https://subhm2004.github.io/DSA-CP/)**

- Search by topic, file name, LeetCode tag, problem name  
- Filter **All / DSA / CP**  
- Har file → GitHub pe direct open  
- Keyboard: **`/`** se search focus  

```bash
# Local (recommended)
bash scripts/serve_site.sh          # → http://localhost:8080/

# Ya repo root se
python3 -m http.server 8080         # auto-redirect → /site/

# Index regenerate (nayi files ke baad)
python3 scripts/generate_site_data.py
```

Deploy: push to `main` → GitHub Actions `gh-pages` branch → Pages source **`gh-pages` / root** ([setup](./site/README.md)).

---

## Learning path

```mermaid
flowchart LR
  A[Patterns] --> B[Basics]
  B --> C[Arrays / Strings]
  C --> D[Recursion]
  D --> E[Trees / Graphs]
  E --> F[DP / Greedy]
  F --> G[CP Templates]

  style A fill:#6366f1,color:#fff
  style G fill:#f59e0b,color:#fff
```

| Stage | Folder | Notes |
|-------|--------|-------|
| 1 | [Patterns](./DSA/patterns/) | Nested loops · [Thita Patterns Sheet](https://docs.google.com/spreadsheets/u/0/d/1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk/htmlview) |
| 2 | [Basics](./DSA/basics/) | Loops, functions, I/O |
| 3 | [Arrays](./DSA/arrays/) · [Strings](./DSA/strings/) | Two pointers, hash, sliding window |
| 4 | [Recursion](./DSA/recursion/) · [Backtracking](./DSA/backtracking/) | Subsets, permutations, N-Queens |
| 5 | [Trees](./DSA/trees/) · [Graphs](./DSA/graphs/) | BFS, DFS, topo, islands |
| 6 | [DP](./DSA/dynamic_programming/) · [Greedy](./DSA/greedy/) | Classic interview patterns |
| 7 | [CP_Template](./CP_Template/) → [CP/](./CP/) | Contest-ready structs & algos |

---

## DSA — interview library

**332 files** · [Full index →](./DSA/README.md)

| Area | Topics |
|------|--------|
| **Core** | [Arrays](./DSA/arrays/) · [Hash map](./DSA/hash_map/) · [Two pointers](./DSA/two_pointers/) · [Sliding window](./DSA/sliding_window/) |
| **Structures** | [Stacks](./DSA/stacks/) · [Queues](./DSA/queues/) · [Heaps](./DSA/heaps/) · [Linked list](./DSA/linked_list/) |
| **Trees** | [Trees](./DSA/trees/) · [BST](./DSA/bst/) · [Trie](./DSA/trie/) |
| **Advanced** | [Graphs](./DSA/graphs/) · [Backtracking](./DSA/backtracking/) · [DP](./DSA/dynamic_programming/) · [Greedy](./DSA/greedy/) |
| **Other** | [Binary search](./DSA/binary_search/) · [Intervals](./DSA/intervals/) · [Design](./DSA/design/) · [Math](./DSA/math/) · [Miscellaneous](./DSA/miscellaneous/) |

<details>
<summary><strong>FAANG coverage checklist</strong></summary>

| Area | Status |
|------|--------|
| Arrays, Hash, Two pointers, Sliding window | ✅ |
| Stack, Queue, Heap, Linked List, Median (two heaps) | ✅ |
| Trees, BST, Trie | ✅ |
| Graphs, Flood fill, Union Find, DP, Greedy | ✅ |
| Backtracking (N-Queens, Sudoku, subsets) | ✅ |
| Intervals, Design (LRU), Bit manipulation | ✅ |
| Math (GCD, LCM, sieve, primes) | ✅ |
| Floyd cycle detection (Tortoise & Hare) | ✅ |

</details>

---

## CP — contest library

**237 files** · [Full index →](./CP/README.md)

| Area | Topics |
|------|--------|
| **Core DS** | [Segment tree](./CP/segment_tree/) · [Fenwick](./CP/fenwick_tree/) · [Sparse table](./CP/sparse_table/) · [DSU / Graphs](./CP/graphs/) |
| **DP & search** | [DP](./CP/dp/) · [Binary search](./CP/binary_search/) · [Meet in the middle](./CP/meet_in_the_middle/) |
| **Strings & math** | [String algorithms](./CP/string_algorithms/) · [Number theory](./CP/number_theory/) · [FFT / NTT](./CP/math/) |
| **Advanced** | [Flows](./CP/graphs/flow/) · [HLD](./CP/graphs/heavy_light_decomposition/) · [Mo's](./CP/mos_algorithm/) · [Geometry](./CP/geometry/) |
| **MST extras** | [Second best MST](./CP/graphs/mst/second_best_mst.cpp) · [Kirchhoff](./CP/graphs/mst/kirchhoff_theorem.cpp) |

**Key templates:** `mod_int` · `ternary_search` · `aho_corasick` · `fft_ntt` · `treap` · `persistent_segment_tree` · `graham_scan` — details in [CP/README.md](./CP/README.md).

---

## DSA vs CP — kab kya use karein?

| | **DSA/** | **CP/** |
|---|----------|---------|
| **Goal** | Interviews, LeetCode clarity | Contests, speed, copy-paste |
| **Code style** | `Solution` class, LC header comments | Fast I/O, reusable structs, `#define int long long` optional |
| **Graphs** | BFS, DFS, flood fill, DSU | Dijkstra, flows, HLD, Two-SAT, bridges |
| **DP** | Knapsack, LCS, LIS, grid | Digit, bitmask, tree, interval DP |
| **When stuck** | Read file header → approach line | Topic folder README → copy template |

---

## Quick start

### Compile any file

```bash
g++ -std=c++17 -O2 DSA/graphs/number_of_islands.cpp -o sol && ./sol
g++ -std=c++17 -O2 CP/graphs/shortest_path/dijkstra.cpp -o sol && ./sol
```

### Contest mode

```bash
cp CP_Template/cp_template.cpp sol.cpp
# solve() mein logic likho
g++ -std=c++17 -O2 -DLOCAL sol.cpp -o sol && ./sol
```

`-DLOCAL` → `input.txt` se read + `dbg()` macro. Full guide: [CP_Template/README.md](./CP_Template/README.md).

### PBDS (GNU extension) — macOS

System `clang++` PBDS support nahi karta → GNU g++ use karo:

```bash
g++-14 -std=c++17 -O2 CP/data_structures/ordered_set_pbds.cpp -o sol
```

---

## File header format

Har solution is pattern follow karta hai (site search isi se LeetCode tag parse karta hai):

```cpp
/*
 * TOPIC    : Graphs — BFS
 * FILE     : number_of_islands.cpp
 * PROBLEM  : Count connected components of '1' in grid
 * LEETCODE : 200 — Number of Islands
 * APPROACH : Multi-source BFS / DFS flood fill
 * COMPLEX  : Time O(m·n)  |  Space O(m·n)
 */
```

---

## Scripts & maintenance

| Script | Kya karta hai |
|--------|---------------|
| [`generate_site_data.py`](./scripts/generate_site_data.py) | DSA/CP scan → `site/data.js` (browser index) |
| [`generate_folder_readmes.py`](./scripts/generate_folder_readmes.py) | Har topic folder ka README regenerate |
| [`add_leetcode_headers.py`](./scripts/add_leetcode_headers.py) | `LEETCODE : N — Title` headers inject |
| [`serve_site.sh`](./scripts/serve_site.sh) | Local site server (`localhost:8080`) |

**Nayi `.cpp` file add karne ke baad:**

```bash
python3 scripts/generate_folder_readmes.py   # README tables update
python3 scripts/generate_site_data.py        # site index update
git push origin main                         # → auto-deploy site (gh-pages)
```

---

## References & inspiration

- [CP-Algorithms](https://cp-algorithms.com/) — geometry, graphs, Josephus, tortoise & hare, MST, …
- [LeetCode](https://leetcode.com/) — DSA problem tagging
- [Thita Patterns Sheet](https://docs.google.com/spreadsheets/u/0/d/1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk/htmlview) — pattern practice list

---

## License

Personal learning repository — **free to use** for study and reference. Star ⭐ dena optional hai, lekin motivation boost karta hai.

<div align="center">

**[Browse the library →](https://subhm2004.github.io/DSA-CP/)**

</div>
