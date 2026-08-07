#!/usr/bin/env python3
"""Generate PATTERNS.md — a Markdown progress tracker for the DSA patterns sheet.

Source sheet : https://docs.google.com/spreadsheets/d/1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk/htmlview
  (bare CSV export = the full 94-pattern tab)

Output is a contents table plus one plain table per pattern: LeetCode number,
problem (linked to LeetCode), and the repo file solving it. That last column is
matched by the `LEETCODE : N` header comment inside every .cpp file (and by
leetcode_<N>_ filenames); unsolved problems show a dash.

Usage:
    python3 scripts/generate_patterns.py            # fetch from Google
    python3 scripts/generate_patterns.py --offline  # use cached CSVs only
"""

import argparse
import csv
import re
import sys
import urllib.request
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "PATTERNS.md"
CACHE = ROOT / "scripts" / ".patterns_cache"

AUTHOR = "Shubham Malik"
AUTHOR_URL = "https://github.com/subhm2004"
REPO_URL = "https://github.com/subhm2004/DSA-CP"

SHEET_ID = "1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk"
SHEET_URL = f"https://docs.google.com/spreadsheets/d/{SHEET_ID}/htmlview"
EXPORT = f"https://docs.google.com/spreadsheets/d/{SHEET_ID}/export?format=csv"
# The first tab has no usable gid on this sheet — the bare export returns it.
SHEET_CSV = EXPORT

# Roman numeral category headers: "I. Two Pointer Patterns"
CATEGORY_RE = re.compile(r"^([IVXL]+)\.\s*(.+?)\s*$")
# "Pattern 12: Level Order Traversal"  /  "Pattern 94. Tries"
PATTERN_RE = re.compile(r"^Pattern\s*(\d+)\s*[:.]?\s*(.*)$", re.I)
ROMAN = {"I": 1, "II": 2, "III": 3, "IV": 4, "V": 5, "VI": 6, "VII": 7, "VIII": 8,
         "IX": 9, "X": 10, "XI": 11, "XII": 12, "XIII": 13, "XIV": 14, "XV": 15}
ROMAN_OUT = {v: k for k, v in ROMAN.items()}

# Problems missing their LeetCode number in the source sheet.
TITLE_TO_ID = {"merge k sorted lists": 23}


def md_escape(text: str) -> str:
    """A literal pipe would split a Markdown table cell in two."""
    return text.replace("|", "\\|")


def gh_anchor(heading: str) -> str:
    """Mimic github-slugger so the summary table's links actually land.

    Each space maps to its own hyphen — collapsing runs would be wrong, because
    a removed "&" leaves two spaces behind and GitHub emits "dfs--bfs".
    """
    return re.sub(r"[^\w\s-]", "", heading.lower()).strip().replace(" ", "-")


def slugify(title: str) -> str:
    """Title -> LeetCode URL slug ("Container With Most Water" -> the same, dashed).

    LeetCode drops punctuation and joins on hyphens, so "Sqrt(x)" -> "sqrtx" and
    "String to Integer (atoi)" -> "string-to-integer-atoi".
    """
    s = re.sub(r"[^a-z0-9 ]+", "", title.lower())
    return re.sub(r"\s+", "-", s.strip())


def fetch(url: str, name: str, offline: bool) -> str:
    """Download a sheet tab, caching it so --offline reruns work."""
    CACHE.mkdir(exist_ok=True)
    cached = CACHE / f"{name}.csv"
    if not offline:
        try:
            with urllib.request.urlopen(url, timeout=30) as r:
                text = r.read().decode("utf-8")
            cached.write_text(text, encoding="utf-8")
            return text
        except Exception as e:  # noqa: BLE001 - fall back to cache on any network error
            print(f"  ! fetch failed for {name} ({e}); trying cache", file=sys.stderr)
    if cached.exists():
        return cached.read_text(encoding="utf-8")
    sys.exit(f"ERROR: no network and no cache for {name}")


def clean_problem_cell(cell: str) -> str:
    """Strip the sheet's stray footnote digits out of a problem list.

    The published sheet carries comment markers inline, e.g.
      "... Deleting One Element, 1  1658. Minimum Operations ..."
      "1011. Capacity To Ship Packages 6  Within D Days"
    Both look like a lone digit followed by 2+ spaces, which never occurs in a
    real LeetCode title, so that is a safe thing to drop.
    """
    cell = cell.replace("\n", " ")
    cell = re.sub(r"(?<![\d.])\b\d\s{2,}", "", cell)
    return re.sub(r"\s+", " ", cell).strip()


def explode_unnumbered(chunk: str) -> list[str]:
    """Peel off trailing problems the sheet forgot to number.

    Pattern 75 reads "21. Merge Two Sorted Lists, Merge k Sorted Lists" — the
    second entry has no id, so the numbered split above cannot see it. Only
    titles we recognise in TITLE_TO_ID get peeled, which keeps titles that
    legitimately contain a comma intact.
    """
    tail = []
    while (m := re.search(r",\s*([^,]+)$", chunk)) and \
            m.group(1).strip().lower() in TITLE_TO_ID:
        tail.insert(0, m.group(1).strip())
        chunk = chunk[: m.start()]
    return [chunk, *tail]


def split_problems(cell: str) -> list[tuple[int | None, str]]:
    """Split "11. Container With Most Water, 15. 3Sum" into (id, title) pairs."""
    cell = clean_problem_cell(cell)
    if not cell:
        return []
    numbered = re.split(r",\s*(?=\d{1,4}\s*\.)", cell)
    out = []
    for chunk in (c for part in numbered for c in explode_unnumbered(part)):
        chunk = chunk.strip().strip(",").strip()
        if not chunk:
            continue
        m = re.match(r"^(\d{1,4})\s*\.\s*(.+)$", chunk)
        if m:
            pid, title = int(m.group(1)), m.group(2).strip()
        else:
            pid, title = TITLE_TO_ID.get(chunk.lower()), chunk
        title = re.sub(r"\s+\d\s*$", "", title).strip()  # trailing footnote digit
        # "1.TwoSum" style — no space after the dot ran the words together
        if title.isalnum():
            title = re.sub(r"([a-z])([A-Z])", r"\1 \2", title)
        if title:
            out.append((pid, title))
    return out


def parse_full(text: str) -> list[dict]:
    """Walk the sheet top to bottom, carrying the current category header."""
    rows, cat_no, cat_name, pat_no, pat_name = [], 0, "", 0, ""
    reader = csv.reader(text.splitlines())
    started = False
    for row in reader:
        if not row:
            continue
        first = (row[0] or "").strip()
        second = (row[1] if len(row) > 1 else "").strip()
        if first == "Pattern" and second == "Problems":
            started = True
            continue
        if not started or not first:
            continue

        m = CATEGORY_RE.match(first)
        if m and m.group(1) in ROMAN and not second:
            cat_no, cat_name = ROMAN[m.group(1)], m.group(2).strip()
            continue

        m = PATTERN_RE.match(first)
        if not m:
            continue
        pat_no = int(m.group(1))
        pat_name = m.group(2).strip().rstrip(":").strip()
        pat_name = re.sub(r"\s*:\s*video\s*$", "", pat_name, flags=re.I).strip()
        for pid, title in split_problems(second):
            rows.append({
                "category_no": cat_no, "category": cat_name,
                "pattern_no": pat_no, "pattern": pat_name,
                "leetcode_id": pid, "problem": title,
            })
    return rows


def repo_index() -> dict[int, list[str]]:
    """Map LeetCode id -> repo files, from `LEETCODE : N` headers + filenames."""
    header_re = re.compile(r"LEETCODE\s*:\s*#?\s*(\d{1,4})", re.I)
    fname_re = re.compile(r"(?:leetcode|lc)[_-]?(\d{1,4})", re.I)
    index: dict[int, list[str]] = {}
    for path in sorted(ROOT.glob("**/*.cpp")):
        if ".git" in path.parts:
            continue
        rel = path.relative_to(ROOT).as_posix()
        ids = set()
        try:
            head = path.read_text(encoding="utf-8", errors="ignore")[:4000]
        except OSError:
            head = ""
        ids.update(int(x) for x in header_re.findall(head))
        ids.update(int(x) for x in fname_re.findall(path.name))
        for pid in ids:
            index.setdefault(pid, []).append(rel)
    return index


def build_markdown(rows: list[dict], index: dict[int, list[str]]) -> str:
    """Render the tracker as plain GitHub-flavoured Markdown tables."""
    for r in rows:
        r["files"] = index.get(r["leetcode_id"], []) if r["leetcode_id"] else []

    total = len(rows)
    cats = sorted({(r["category_no"], r["category"]) for r in rows})
    out: list[str] = []
    add = out.append

    add("# DSA Patterns\n")
    add(f"**Author:** [{AUTHOR}]({AUTHOR_URL}) &nbsp;·&nbsp; "
        f"[{REPO_URL.split('/')[-1]}]({REPO_URL})  ")
    add(f"**Generated:** {date.today().isoformat()}\n")
    add(f"{len(cats)} categories &nbsp;·&nbsp; "
        f"{len({r['pattern_no'] for r in rows})} patterns &nbsp;·&nbsp; "
        f"{total} problems\n")
    add("---\n")

    # ── Contents ─────────────────────────────────────────────────────────────
    add("## Contents\n")
    add("| # | Category | Patterns | Problems |")
    add("|--:|----------|---------:|---------:|")
    for cno, cname in cats:
        sub = [r for r in rows if r["category_no"] == cno]
        anchor = gh_anchor(f"{ROMAN_OUT[cno]}. {cname}")
        add(f"| {ROMAN_OUT[cno]} | [{md_escape(cname)}](#{anchor}) | "
            f"{len({r['pattern_no'] for r in sub})} | {len(sub)} |")
    add(f"| | **Total** | **{len({r['pattern_no'] for r in rows})}** | **{total}** |")
    add("\n---\n")

    # ── One section per category, one table per pattern ──────────────────────
    for cno, cname in cats:
        sub = [r for r in rows if r["category_no"] == cno]
        add(f"## {ROMAN_OUT[cno]}. {cname}\n")

        for pno in sorted({r["pattern_no"] for r in sub}):
            prob = [r for r in sub if r["pattern_no"] == pno]
            add(f"### Pattern {pno} — {md_escape(prob[0]['pattern'])}\n")
            add("| No. | Problem | Solution |")
            add("|----:|---------|----------|")
            for r in prob:
                url = f"https://leetcode.com/problems/{slugify(r['problem'])}/"
                sol = " · ".join(f"[`{f}`](./{f})" for f in r["files"]) or "—"
                add(f"| {r['leetcode_id']} | "
                    f"[{md_escape(r['problem'])}]({url}) | {sol} |")
            add("")
        add("---\n")

    add(f"<sub>Auto-generated — edit karne ke bajaye "
        f"`python3 scripts/{Path(__file__).name}` dobara chalao. "
        f"Solution column `LEETCODE : N` header comment se match hota hai.</sub>")
    return "\n".join(out) + "\n"


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--offline", action="store_true", help="use cached sheet CSVs")
    args = ap.parse_args()

    print("Fetching sheet…")
    rows = parse_full(fetch(SHEET_CSV, "full", args.offline))
    index = repo_index()
    print(f"  {len(rows)} problems · {len({r['pattern_no'] for r in rows})} patterns "
          f"· {len(index)} LeetCode ids in repo")

    OUT.write_text(build_markdown(rows, index), encoding="utf-8")
    solved = sum(bool(index.get(r["leetcode_id"])) for r in rows)
    print(f"Wrote {OUT.relative_to(ROOT)} — {len(rows)} problems, "
          f"{solved} solved ({solved * 100 // len(rows)}%)")


if __name__ == "__main__":
    main()
