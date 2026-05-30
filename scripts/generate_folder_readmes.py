#!/usr/bin/env python3
"""Generate README.md for every DSA/CP topic folder."""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

# Optional: topics still worth adding (shown in README)
MISSING = {
    "DSA/arrays": ["product_of_array_except_self (LC 238)", "majority_element (LC 169)"],
    "DSA/strings": ["valid_palindrome (LC 125)", "longest_palindromic_substring (LC 5)"],
    "DSA/graphs": ["course_schedule (LC 207 — also in CP)", "word_search (LC 79)"],
    "DSA/backtracking": ["word_search (LC 79)", "generate_parentheses (LC 22)"],
    "DSA/trie": ["implement_trie II / word dictionary (LC 212)"],
    "DSA/bit_manipulation": ["missing_number (LC 268)", "sum_of_two_integers (LC 371)"],
    "DSA/design": ["min_stack (LC 155 — in stacks/)", "implement_queue_using_stacks (LC 232)"],
    "DSA/recursion": ["basic recursion drills (factorial, fib)"],
    "CP/number_theory": ["stress_test_template.cpp"],
    "CP/data_structures": ["implicit_treap.cpp (see treap.cpp — ImplicitTreap)"],
    "CP/string_algorithms": ["suffix_automaton.cpp"],
    "CP/binary_search": [],
    "CP/segment_tree": ["li_chao_segment_tree.cpp"],
    "CP/math": [],
    "CP/graphs/matching": ["hungarian_algorithm.cpp"],
}

DESCRIPTIONS = {
    "DSA/arrays": "Array manipulation, two pointers, prefix sum, matrix.",
    "DSA/binary_search": "Standard BS, rotated array, BS on answer.",
    "DSA/bit_manipulation": "XOR tricks, bit DP basics for interviews.",
    "DSA/bst": "Binary Search Tree operations.",
    "DSA/char_array": "C-style char arrays.",
    "DSA/design": "Object-oriented design problems (LRU, etc.).",
    "DSA/dynamic_programming": "Classic interview DP patterns.",
    "DSA/graphs": "BFS, DFS, flood fill, islands, topo — interview level.",
    "DSA/backtracking": "N-Queens, Sudoku, subsets, permutations, combination sum.",
    "DSA/greedy": "Activity selection, jump game, intervals.",
    "DSA/hash_map": "Hash table patterns.",
    "DSA/heaps": "Priority queue, kth element, median from stream (two heaps).",
    "DSA/intervals": "Merge, insert, meeting rooms.",
    "DSA/linked_list": "Singly/doubly LL, cycle, reversal.",
    "DSA/miscellaneous": "Classic puzzles — Josephus, etc.",
    "DSA/math": "GCD, LCM, sieve, prime check — interview number theory.",
    "DSA/queues": "Queue, deque, circular queue.",
    "DSA/recursion": "Backtracking, subsets, permutations.",
    "DSA/sliding_window": "Variable/fixed window problems.",
    "DSA/sorting": "All major sorting algorithms.",
    "DSA/stacks": "Monotonic stack, max histogram area, parentheses.",
    "CP/meet_in_the_middle": "Split n in half; enumerate subset sums — O(2^(n/2)).",
    "CP/geometry": "Convex hull, line intersection, point in polygon.",
    "CP/math": "FFT, NTT — polynomial convolution.",
    "DSA/strings": "String basics and practice.",
    "DSA/trees": "Binary tree traversals, views, construction.",
    "DSA/trie": "Prefix tree + word search.",
    "DSA/two_pointers": "Sorted array two-pointer patterns.",
    "CP/dp": "Competitive programming DP — all subtypes.",
    "CP/graphs": "Advanced graph algorithms for contests.",
    "CP/segment_tree": "Range queries, lazy propagation, persistent.",
    "CP/fenwick_tree": "Binary Indexed Tree variants.",
    "CP/number_theory": "Primes, mod arithmetic, CRT, sieve.",
    "CP/string_algorithms": "KMP, hashing, suffix array, Z-algo.",
    "CP/data_structures": "PBDS, treap, advanced DS.",
}


def parse_leetcode(path: Path) -> str:
    try:
        head = path.read_text(encoding="utf-8", errors="ignore")[:800]
    except OSError:
        return "—"
    m = re.search(r"LEETCODE\s*:\s*(.+)", head)
    if m:
        return m.group(1).strip()
    m = re.search(r"PROBLEM\s*:\s*(.+)", head)
    return m.group(1).strip()[:60] if m else "—"


def folder_title(rel: str) -> str:
    parts = rel.split("/")
    if len(parts) == 1:
        return parts[0]
    name = parts[-1].replace("_", " ").title()
    prefix = parts[0]
    return f"{prefix} — {name}"


def list_subdirs(folder: Path) -> list[Path]:
    return sorted([p for p in folder.iterdir() if p.is_dir() and not p.name.startswith(".")])


def list_cpp(folder: Path) -> list[Path]:
    return sorted(folder.glob("*.cpp"))


def generate_readme(folder: Path, base: str) -> str:
    rel = str(folder.relative_to(ROOT)).replace("\\", "/")
    title = folder_title(rel)
    desc = DESCRIPTIONS.get(rel, "C++ implementations for this topic.")
    subdirs = list_subdirs(folder)
    files = list_cpp(folder)
    missing = MISSING.get(rel, [])

    lines = [
        f"# {title}",
        "",
        desc,
        "",
        f"**Path:** [`{rel}/`](./)",
        "",
    ]

    if subdirs:
        lines += ["## Subfolders", "", "| Folder | README |", "|--------|--------|"]
        for sd in subdirs:
            sd_rel = sd.relative_to(folder)
            readme = sd / "README.md"
            link = f"[Open →](./{sd_rel}/README.md)" if readme.exists() else "—"
            n = len(list_cpp(sd))
            lines.append(f"| [{sd.name}/](./{sd_rel}/) | {link} | ({n} files)")
        lines.append("")

    if files:
        lines += [f"## Files ({len(files)})", "", "| File | LeetCode / Notes |", "|------|------------------|"]
        for f in files:
            lc = parse_leetcode(f)
            lines.append(f"| [{f.name}](./{f.name}) | {lc} |")
        lines.append("")
    elif not subdirs:
        lines += ["## Files", "", "_No `.cpp` files yet._", ""]

    if missing:
        lines += ["## TODO — add later", ""]
        for item in missing:
            lines.append(f"- [ ] {item}")
        lines.append("")

    status = "✅ Good coverage" if len(files) >= 5 or subdirs else ("🟡 Basic" if files else "🔴 Empty — add files")
    lines += ["---", f"**Status:** {status}", ""]

    return "\n".join(lines)


def main():
    SKIP = {
        str(ROOT / "DSA" / "README.md"),
        str(ROOT / "CP" / "README.md"),
    }
    for base_name in ("DSA", "CP"):
        base = ROOT / base_name
        if not base.exists():
            continue
        folders = [base]
        for p in sorted(base.rglob("*")):
            if p.is_dir() and not p.name.startswith("."):
                # include if has cpp or subdirs with content
                has_cpp = any(p.glob("*.cpp"))
                has_child = any(c.is_dir() for c in p.iterdir() if not c.name.startswith("."))
                if has_cpp or has_child or p == base:
                    folders.append(p)
        seen = set()
        for folder in folders:
            key = str(folder)
            if key in seen:
                continue
            seen.add(key)
            rel = folder.relative_to(ROOT)
            # skip if no cpp and no subdirs (leaf empty)
            if folder != base and not list_cpp(folder) and not list_subdirs(folder):
                continue
            out = folder / "README.md"
            if str(out) in SKIP:
                continue
            content = generate_readme(folder, base_name)
            out.write_text(content, encoding="utf-8")
            print(f"Wrote {out.relative_to(ROOT)}")

    print("Done.")


if __name__ == "__main__":
    main()
