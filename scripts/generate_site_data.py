#!/usr/bin/env python3
"""Generate site/data.js from DSA/ and CP/ folder structure."""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "site" / "data.js"

LEETCODE_RE = re.compile(r"LEETCODE\s*:\s*(.+)", re.I)
PROBLEM_RE = re.compile(r"PROBLEM\s*:\s*(.+)", re.I)


def repo_meta() -> dict:
    """Read GitHub owner/name/branch from git remote."""
    import subprocess

    owner, name, branch = "subhm2004", "DSA-CP", "main"
    try:
        url = subprocess.check_output(
            ["git", "remote", "get-url", "origin"], cwd=ROOT, text=True, stderr=subprocess.DEVNULL
        ).strip()
        if "github.com" in url:
            part = url.split("github.com")[-1].strip(":/").replace(".git", "")
            bits = part.split("/")
            if len(bits) >= 2:
                owner, name = bits[0], bits[1]
        branch = subprocess.check_output(
            ["git", "branch", "--show-current"], cwd=ROOT, text=True, stderr=subprocess.DEVNULL
        ).strip() or "main"
    except (subprocess.CalledProcessError, FileNotFoundError):
        pass
    base = f"https://{owner}.github.io/{name}"
    return {
        "owner": owner,
        "name": name,
        "branch": branch,
        "repoUrl": f"https://github.com/{owner}/{name}",
        "pagesUrl": f"{base}/",
    }


def parse_header(path: Path) -> dict:
    try:
        head = path.read_text(encoding="utf-8", errors="ignore")[:600]
    except OSError:
        return {"leetcode": "", "problem": path.stem.replace("_", " ").title()}
    lc = LEETCODE_RE.search(head)
    pr = PROBLEM_RE.search(head)
    return {
        "leetcode": lc.group(1).strip() if lc else "",
        "problem": pr.group(1).strip()[:80] if pr else path.stem.replace("_", " ").title(),
    }


def scan_section(base: Path, prefix: str) -> list:
    topics = []
    if not base.exists():
        return topics

    def add_topic(folder: Path, rel: str):
        files = sorted(folder.glob("*.cpp"))
        if not files:
            return
        entries = []
        for f in files:
            meta = parse_header(f)
            entries.append({
                "name": f.name,
                "path": f"{prefix}/{rel}/{f.name}".replace("\\", "/"),
                "leetcode": meta["leetcode"],
                "problem": meta["problem"],
            })
        topics.append({
            "id": f"{prefix}-{rel}".replace("/", "-"),
            "name": rel.split("/")[-1].replace("_", " ").title(),
            "path": f"{prefix}/{rel}",
            "fileCount": len(entries),
            "files": entries,
        })

    for item in sorted(base.iterdir()):
        if not item.is_dir() or item.name.startswith("."):
            continue
        rel = item.name
        add_topic(item, rel)
        for sub in sorted(item.iterdir()):
            if sub.is_dir() and not sub.name.startswith("."):
                add_topic(sub, f"{rel}/{sub.name}")

    topics.sort(key=lambda t: t["name"].lower())
    return topics


def main():
    dsa = scan_section(ROOT / "DSA", "DSA")
    cp = scan_section(ROOT / "CP", "CP")
    template_path = ROOT / "CP_Template" / "cp_template.cpp"
    template = template_path.exists()

    stats = {
        "dsaFiles": sum(t["fileCount"] for t in dsa),
        "cpFiles": sum(t["fileCount"] for t in cp),
        "dsaTopics": len(dsa),
        "cpTopics": len(cp),
    }

    payload = {
        "generated": __import__("datetime").datetime.now().strftime("%Y-%m-%d %H:%M"),
        "meta": repo_meta(),
        "stats": stats,
        "dsa": dsa,
        "cp": cp,
        "template": {
            "path": "CP_Template/cp_template.cpp",
            "readme": "CP_Template/README.md",
        } if template else None,
    }

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text(
        "// Auto-generated — run: python3 scripts/generate_site_data.py\n"
        f"window.REPO_DATA = {json.dumps(payload, indent=2, ensure_ascii=False)};\n",
        encoding="utf-8",
    )
    print(f"Wrote {OUT.relative_to(ROOT)}")
    print(f"  DSA: {stats['dsaTopics']} topics, {stats['dsaFiles']} files")
    print(f"  CP:  {stats['cpTopics']} topics, {stats['cpFiles']} files")


if __name__ == "__main__":
    main()
