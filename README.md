# C++ — DSA & Competitive Programming

Personal C++ library for **interview prep** and **contest coding** — organized by topic, LeetCode tags where relevant, and a README in every folder.

**Author:** [Shubham Malik](https://github.com/subhm2004)

| | Count |
|---|------:|
| DSA solutions | **340** |
| CP templates | **233** |
| Contest template | **1** |
| Topic READMEs | **100+** |

---

## What's inside

```
C++/
├── DSA/              Interview & FAANG — arrays, trees, graphs, DP, …
├── CP/               Contest library — segtree, flows, strings, NT, …
├── CP_Template/      Lean single-file starter for Codeforces / AtCoder
├── site/             Static browser UI (HTML + Tailwind + JS)
└── scripts/          README generator, site data, LeetCode tools
```

| Section | Use when | Index |
|---------|----------|-------|
| **[DSA](./DSA/)** | LeetCode, FAANG, college DSA | [DSA/README.md](./DSA/README.md) |
| **[CP](./CP/)** | Codeforces, AtCoder, ICPC | [CP/README.md](./CP/README.md) |
| **[CP_Template](./CP_Template/)** | Copy one file → contest | [CP_Template/README.md](./CP_Template/README.md) |

Har topic folder ke andar **`README.md`** — file list, approach notes, LeetCode #, aur TODO (agar kuch missing ho).

### Static site (browser UI)

**Live (after Pages enabled):** [https://subhm2004.github.io/DSA-CP/](https://subhm2004.github.io/DSA-CP/)

Search topics, filter DSA/CP, open files on GitHub.

```bash
# Local — open the site (NOT the repo folder listing)
bash scripts/serve_site.sh          # → http://localhost:8080/
# or: python3 -m http.server 8080    # → http://localhost:8080/  (auto-redirects to /site/)

# Regenerate index
python3 scripts/generate_site_data.py
```

Deploy: push to `main` → set Pages branch **`gh-pages`** / root ([setup](./site/README.md)).

---

## Quick start

### Compile any solution

```bash
g++ -std=c++17 -O2 DSA/graphs/number_of_islands.cpp -o sol && ./sol
g++ -std=c++17 -O2 CP/graphs/shortest_path/dijkstra.cpp -o sol && ./sol
```

### Contest (copy template)

```bash
cp CP_Template/cp_template.cpp sol.cpp
# solve() me logic likho
g++ -std=c++17 -O2 -DLOCAL sol.cpp -o sol && ./sol
```

`-DLOCAL` → `input.txt` se read + `dbg()` macro. Details: [CP_Template/README.md](./CP_Template/README.md).

### PBDS (GNU extension)

macOS pe system `clang++` PBDS support nahi karta. GNU g++ use karo:

```bash
g++-14 -std=c++17 -O2 CP/data_structures/ordered_set_pbds.cpp -o sol
```

---

## DSA — highlights

Interview-focused folders (full list → [DSA/README.md](./DSA/README.md)):

| Area | Topics |
|------|--------|
| Core | [Arrays](./DSA/arrays/) · [Hash map](./DSA/hash_map/) · [Two pointers](./DSA/two_pointers/) · [Sliding window](./DSA/sliding_window/) |
| Structures | [Stacks](./DSA/stacks/) · [Queues](./DSA/queues/) · [Heaps](./DSA/heaps/) · [Linked list](./DSA/linked_list/) |
| Trees | [Trees](./DSA/trees/) · [BST](./DSA/bst/) · [Trie](./DSA/trie/) |
| Advanced | [Graphs](./DSA/graphs/) · [Backtracking](./DSA/backtracking/) · [DP](./DSA/dynamic_programming/) · [Greedy](./DSA/greedy/) |
| Other | [Binary search](./DSA/binary_search/) · [Intervals](./DSA/intervals/) · [Design](./DSA/design/) · [Math](./DSA/math/) |

**Starting from zero?** → [Patterns](./DSA/patterns/) (nested loops) → [Basics](./DSA/basics/) → phir arrays / recursion.

---

## CP — highlights

Contest templates (full list → [CP/README.md](./CP/README.md)):

| Area | Topics |
|------|--------|
| Core DS | [Segment tree](./CP/segment_tree/) · [Fenwick](./CP/fenwick_tree/) · [Sparse table](./CP/sparse_table/) · [DSU / graphs](./CP/graphs/) |
| DP & search | [DP](./CP/dp/) · [Binary search](./CP/binary_search/) · [Meet in the middle](./CP/meet_in_the_middle/) |
| Strings & math | [String algorithms](./CP/string_algorithms/) · [Number theory](./CP/number_theory/) · [FFT / NTT](./CP/math/) |
| Advanced | [Flows](./CP/graphs/flow/) · [HLD / centroid](./CP/graphs/) · [Mo's](./CP/mos_algorithm/) · [Geometry](./CP/geometry/) |

Key templates: `mod_int` · `ternary_search` · `aho_corasick` · `fft_ntt` · `treap` — paths in [CP/README.md](./CP/README.md).

---

## DSA vs CP

| | **DSA/** | **CP/** |
|---|----------|---------|
| **Goal** | Interviews, LeetCode | Contests, speed |
| **Style** | Clean `Solution` class, LC comments | Fast I/O, reusable structs |
| **Graphs** | BFS, DFS, flood fill, DSU | Dijkstra, flows, HLD, Two-SAT |
| **DP** | Knapsack, LCS, LIS, grid | Digit, bitmask, tree, interval |
| **When stuck** | Read header comment + approach | Copy snippet from topic folder |

---

## Scripts

| Script | Kya karta hai |
|--------|----------------|
| [`generate_site_data.py`](./scripts/generate_site_data.py) | Static site index → `site/data.js` |
| [`generate_folder_readmes.py`](./scripts/generate_folder_readmes.py) | Har topic folder ka README regenerate |
| [`add_leetcode_headers.py`](./scripts/add_leetcode_headers.py) | `LEETCODE : N — Title` headers inject |

Nayi files add karne ke baad:

```bash
python3 scripts/generate_folder_readmes.py
```

---


## License

Personal learning repo — use freely for study and reference.
