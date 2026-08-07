#!/usr/bin/env python3
"""Generate patterns.csv from the Thita DSA Patterns Sheet (Swati Ahuja).

Source sheet : https://docs.google.com/spreadsheets/d/1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk/htmlview
  gid=0                -> full sheet (94 patterns)
  gid=2094977620       -> "30 day" core subset

Each output row is ONE problem, so the CSV sorts/filters cleanly in Excel or
pandas. Solved problems are matched against this repo by the `LEETCODE : N`
header comment inside every .cpp file (and by leetcode_<N>_ filenames).

The file opens with a META_ROWS-line author block (same convention the source
sheet uses), so readers must skip those before the column header:
    pandas.read_csv("patterns.csv", skiprows=6)

Usage:
    python3 scripts/generate_patterns_csv.py            # fetch from Google
    python3 scripts/generate_patterns_csv.py --offline  # use cached CSVs only
"""

import argparse
import csv
import re
import sys
import urllib.request
from datetime import date
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "patterns.csv"
CACHE = ROOT / "scripts" / ".patterns_cache"

AUTHOR = "Shubham Malik"
AUTHOR_URL = "https://github.com/subhm2004"
REPO_URL = "https://github.com/subhm2004/DSA-CP"

SHEET_ID = "1EEYzyD_483B-7CmWxsJB_zycdv4Y5dxnzcoEQtaIfuk"
SHEET_URL = f"https://docs.google.com/spreadsheets/d/{SHEET_ID}/htmlview"
META_ROWS = 6  # metadata + blank lines written above the column header
EXPORT = f"https://docs.google.com/spreadsheets/d/{SHEET_ID}/export?format=csv"
# The first tab has no usable gid on this sheet — bare export returns it.
TABS = {"full": EXPORT, "core30": f"{EXPORT}&gid=2094977620"}

# Roman numeral category headers: "I. Two Pointer Patterns"
CATEGORY_RE = re.compile(r"^([IVXL]+)\.\s*(.+?)\s*$")
# "Pattern 12: Level Order Traversal"  /  "Pattern 94. Tries"
PATTERN_RE = re.compile(r"^Pattern\s*(\d+)\s*[:.]?\s*(.*)$", re.I)
ROMAN = {"I": 1, "II": 2, "III": 3, "IV": 4, "V": 5, "VI": 6, "VII": 7, "VIII": 8,
         "IX": 9, "X": 10, "XI": 11, "XII": 12, "XIII": 13, "XIV": 14, "XV": 15}

# Problems missing their LeetCode number in the source sheet.
TITLE_TO_ID = {"merge k sorted lists": 23}


def comma_safe(label: str) -> str:
    """Drop commas from label columns so plain `awk -F,` stays correct.

    Only one pattern name carries a comma ("0/1 Knapsack, Subset Sum Style"),
    but a quoted field silently shifts every column after it for naive splitters,
    so normalise it here rather than leaving a trap in the data.
    """
    return re.sub(r"\s*,\s*", " & ", label).strip()


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


def parse_core30(text: str) -> set[int]:
    """Collect the LeetCode ids that appear in the condensed 30-day tab."""
    ids = set()
    for row in csv.reader(text.splitlines()):
        if len(row) < 2 or not PATTERN_RE.match((row[0] or "").strip()):
            continue
        for pid, _ in split_problems(row[1]):
            if pid:
                ids.add(pid)
    return ids


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


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--offline", action="store_true", help="use cached sheet CSVs")
    args = ap.parse_args()

    print("Fetching sheet…")
    rows = parse_full(fetch(TABS["full"], "full", args.offline))
    core = parse_core30(fetch(TABS["core30"], "core30", args.offline))
    index = repo_index()
    print(f"  {len(rows)} problems · {len({r['pattern_no'] for r in rows})} patterns "
          f"· {len(core)} in 30-day core · {len(index)} LeetCode ids in repo")

    fields = ["sr", "category_no", "category", "pattern_no", "pattern",
              "leetcode_id", "problem", "status", "repo_file", "in_30day_core",
              "leetcode_url"]
    solved = 0
    with OUT.open("w", newline="", encoding="utf-8") as fh:
        # Metadata block, same shape as the source sheet's own header rows.
        # META_ROWS lines sit above the real header — see README for pandas usage.
        meta = csv.writer(fh)
        for row in [
            ["Author", AUTHOR],
            ["GitHub", AUTHOR_URL],
            ["Repo", REPO_URL],
            ["Tracker", "DSA Patterns — progress tracker (Done/Todo auto-mapped from repo)"],
            ["Generated", date.today().isoformat()],
            [],
        ]:
            meta.writerow(row)

        w = csv.DictWriter(fh, fieldnames=fields)
        w.writeheader()
        for i, r in enumerate(rows, 1):
            pid = r["leetcode_id"]
            files = index.get(pid, []) if pid else []
            solved += bool(files)
            w.writerow({
                "sr": i,
                "category_no": r["category_no"],
                "category": comma_safe(r["category"]),
                "pattern_no": r["pattern_no"],
                "pattern": comma_safe(r["pattern"]),
                "leetcode_id": pid or "",
                "problem": comma_safe(r["problem"]),
                "status": "Done" if files else "Todo",
                "repo_file": " | ".join(files),
                "in_30day_core": "Yes" if pid in core else "No",
                "leetcode_url": f"https://leetcode.com/problems/{slugify(r['problem'])}/",
            })
    pct = solved * 100 // len(rows) if rows else 0
    print(f"Wrote {OUT.relative_to(ROOT)} — {len(rows)} rows, {solved} solved ({pct}%)")

    # Guard the awk-friendliness the README promises.
    body = OUT.read_text(encoding="utf-8").splitlines()[META_ROWS:]
    if quoted := [ln.split(",")[0] for ln in body if '"' in ln]:
        print(f"  ! {len(quoted)} row(s) still need CSV quoting (sr {quoted[:5]}) "
              f"— `awk -F,` will mis-split these", file=sys.stderr)


if __name__ == "__main__":
    main()
