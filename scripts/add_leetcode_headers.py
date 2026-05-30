#!/usr/bin/env python3
"""Insert LEETCODE : N — Title into DSA .cpp headers where missing."""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DSA_ROOT = ROOT / "DSA"
CP_ROOT = ROOT / "CP"

# CP: relative path from CP/ -> "N — Title"
CP_LEETCODE: dict[str, str] = {
    "monotonic_stack/monotonic_stack.cpp": "496 — Next Greater Element I / 84 — Largest Rectangle in Histogram",
    "monotonic_queue/monotonic_queue.cpp": "239 — Sliding Window Maximum",
    "meet_in_the_middle/subset_sum.cpp": "416 — Partition Equal Subset Sum (MITM for n≤40)",
}

# filename stem (no .cpp) -> "N — Title"
LEETCODE: dict[str, str] = {
    # stacks
    "leetcode_1003_valid_after_deletion": "1003 — Check If String Is Deletable",
    "celebrity_problem": "277 — Find the Celebrity",
    "remove_duplicates_stack": "1047 — Remove All Adjacent Duplicates In String",
    "minimum_bracket_reversals": "1249 — Minimum Remove to Make Valid Parentheses",
    "check_redundant_brackets": "678 — Valid Parenthesis String",
    # trees
    "right_view_binary_tree": "199 — Binary Tree Right Side View",
    "zigzag_level_order": "103 — Binary Tree Zigzag Level Order Traversal",
    "binary_tree_height": "104 — Maximum Depth of Binary Tree",
    "build_tree_inorder_preorder": "105 — Construct Binary Tree from Preorder and Inorder",
    "build_tree_inorder_postorder": "106 — Construct Binary Tree from Inorder and Postorder",
    "construct_bst": "1008 — Construct Binary Search Tree from Preorder Traversal",
    "boundary_traversal": "545 — Boundary of Binary Tree",
    "binary_tree_leaf_nodes": "404 — Sum of Left Leaves",
    "morris_traversal_binary_tree": "94 — Binary Tree Inorder Traversal (Morris O(1) space)",
    "morris_traversal_bst": "94 — BST Inorder (Morris traversal)",
    # recursion / backtracking (recursion folder)
    "generate_parenthesis": "22 — Generate Parentheses",
    "generate_subsets": "78 — Subsets",
    "generate_subsequences": "78 — Subsets / Subsequence variant",
    "phone_keypad_problem": "17 — Letter Combinations of a Phone Number",
    "coin_change": "322 — Coin Change",
    "house_robber": "198 — House Robber",
    "palindrome_string": "125 — Valid Palindrome",
    "permutations_of_string": "46 — Permutations",
    "rat_in_maze": "490 — The Maze (grid path backtracking)",
    "maximum_sum": "53 — Maximum Subarray",
    "cut_rod_max_segments": "322 — Coin Change (rod cutting variant)",
    # binary search
    "k_diff_pairs": "532 — K-diff Pairs in an Array",
    "square_root_binary_search": "69 — Sqrt(x)",
    "painter_partition": "410 — Split Array Largest Sum",
    "book_allocation": "410 — Split Array Largest Sum",
    "pivot_element": "33 — Search in Rotated Sorted Array",
    "find_quotient_binary_search": "29 — Divide Two Integers",
    "total_occurrences": "34 — Find First and Last Position of Element in Sorted Array",
    "exponential_search": "704 — Binary Search (exponential search variant)",
    "odd_occurrence_binary_search": "540 — Single Element in a Sorted Array",
    # linked list
    "tortoise_algo": "141 — Linked List Cycle / 142 — Linked List Cycle II",
    "addone": "369 — Plus One Linked List",
    "doubly_linked_list": "146 — LRU Cache (doubly linked list pattern)",
    "linkedlistdelete": "237 — Delete Node in a Linked List",
    "linked_list_deletion": "203 — Remove Linked List Elements",
    "middle_of_linked_list": "876 — Middle of the Linked List",
    # heaps
    "find_k_smallest_elements": "215 — Kth Largest Element in an Array",
    "heap_sort": "912 — Sort an Array (heap sort approach)",
    # queues
    "reverse_k_queue_elements": "25 — Reverse Nodes in k-Group",
    "nonrepeating_char": "387 — First Unique Character in String",
    "queue_using_two_stacks": "232 — Implement Queue using Stacks",
    "circular_queue_implementation": "622 — Design Circular Queue",
    # strings
    "remove_k_duplicates": "1209 — Remove All Adjacent Duplicates in String II",
    "remove_occurrences": "1910 — Remove All Occurrences of a Substring",
    # arrays
    "binary_search": "704 — Binary Search",
    "rotate_matrix": "48 — Rotate Image",
    "transpose_matrix": "867 — Transpose Matrix",
    "first_occurrence": "34 — Find First and Last Position of Element in Sorted Array",
    "sort_colors": "75 — Sort Colors",
    "duplicate_number": "287 — Find the Duplicate Number",
    "shift_one": "189 — Rotate Array",
    "reverse": "344 — Reverse String (array variant)",
    # bst
    "bst_search": "700 — Search in a Binary Search Tree",
    "bst_deletion": "450 — Delete Node in a BST",
    "bst_creation": "701 — Insert into a Binary Search Tree",
    "largest_bst_subtree": "333 — Largest BST Subtree",
    "bst_to_doubly_linked_list": "426 — Convert BST to Sorted Doubly Linked List",
    "bst_to_dll_construction": "426 — Convert BST to Sorted Doubly Linked List",
    "lca_in_bst": "235 — Lowest Common Ancestor of a BST",
    "two_sum_bst": "653 — Two Sum IV - Input is a BST",
    # graphs (traversal templates)
    "bfs_traversal": "102 — Binary Tree Level Order Traversal (BFS pattern)",
    "dfs_traversal": "104 — Maximum Depth (DFS pattern)",
    # greedy
    "job_sequencing": "435 — Non-overlapping Intervals (scheduling variant)",
    # design / misc interview
    "lru_cache": "146 — LRU Cache",
    # sorting (classic LC tagged)
    "merge_sort": "912 — Sort an Array",
    "quick_sort": "912 — Sort an Array",
    "counting_sort": "912 — Sort an Array (counting sort)",
    # CP-style in DSA binary search
    "ekos_spoj": "410 — Split Array Largest Sum (binary search on answer)",
    "pratas_poj": "410 — Split Array Largest Sum (binary search on answer)",
    "euclidean_gcd_lcm": "1071 — Greatest Common Divisor of Strings",
    "count_primes": "204 — Count Primes",
    "is_prime_sqrt": "204 — Count Primes (prime check / sieve helper)",
    # trees (views)
    "top_view_binary_tree": "314 — Binary Tree Vertical Order Traversal",
    "left_view_binary_tree": "199 — Binary Tree Right Side View (mirror pattern)",
    "diagonal_traversal": "545 — Boundary of Binary Tree (diagonal — GFG variant)",
    "make_binary_tree": "894 — All Possible Full Binary Trees",
    # stacks design
    "two_stacks_in_array": "155 — Min Stack (two-stack design pattern)",
    "n_stacks_in_array": "716 — Max Stack (multi-stack design)",
    "insert_at_bottom_of_stack": "225 — Implement Stack using Queues",
    # queues
    "interleave_queue": "950 — Reveal Cards In Order (queue reorder pattern)",
    "reverse_queue": "206 — Reverse Linked List (queue reverse pattern)",
    "deque_implementation": "239 — Sliding Window Maximum (deque pattern)",
    # binary search
    "aggressive_cows": "410 — Split Array Largest Sum (BS on answer — GFG variant)",
    "search_nearly_sorted": "540 — Single Element in a Sorted Array",
    "unbounded_binary_search": "704 — Binary Search (unbounded range)",
}

# Known titles for leetcode_NNN filenames
LC_TITLES = {
    "1003": "Check If String Is Deletable",
}


def lookup_leetcode(stem: str) -> str | None:
    if stem in LEETCODE:
        return LEETCODE[stem]
    m = re.match(r"leetcode_(\d+)", stem)
    if m:
        num = m.group(1)
        title = LC_TITLES.get(num, "see problem name")
        return f"{num} — {title}"
    return None


def inject(content: str, lc_line: str) -> tuple[str, bool]:
    if re.search(r"LEETCODE\s*:", content[:900], re.I):
        return content, False

    lines = content.split("\n")
    out: list[str] = []
    inserted = False
    for line in lines:
        out.append(line)
        if not inserted and re.match(r"\s*\* PROBLEM\s*:", line):
            out.append(f" * LEETCODE : {lc_line}")
            inserted = True
    if inserted:
        return "\n".join(out), True
    return content, False


def main():
    updated = 0
    skipped = 0
    for path in sorted(DSA_ROOT.rglob("*.cpp")):
        lc = lookup_leetcode(path.stem)
        if not lc:
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        new_text, changed = inject(text, lc)
        if changed:
            path.write_text(new_text, encoding="utf-8")
            print(f"  + {path.relative_to(ROOT)}")
            updated += 1
        else:
            skipped += 1

    for rel, lc in CP_LEETCODE.items():
        path = CP_ROOT / rel
        if not path.exists():
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        new_text, changed = inject(text, lc)
        if changed:
            path.write_text(new_text, encoding="utf-8")
            print(f"  + {path.relative_to(ROOT)}")
            updated += 1
        else:
            skipped += 1

    print(f"Updated {updated} files ({skipped} already had LEETCODE).")


if __name__ == "__main__":
    main()
