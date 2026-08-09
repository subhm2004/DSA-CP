# Static Site

Browser UI for DSA & CP — deployed on **GitHub Pages**.

## Live URL

After enabling Pages (see below):

**https://subhm2004.github.io/DSA-CP/**

## One-time GitHub setup

1. Push to `main` (workflow creates `gh-pages` branch automatically)
2. Open **[Settings → Pages](https://github.com/subhm2004/DSA-CP/settings/pages)**
3. **Build and deployment** → Source: **Deploy from a branch**
4. Branch: **`gh-pages`** · Folder: **`/ (root)`** → **Save**
5. Wait ~1 min, open **https://subhm2004.github.io/DSA-CP/**

If it still 404, go to **Actions** → re-run **Deploy static site to GitHub Pages**.

## Local dev

```bash
bash scripts/serve_site.sh
# → http://localhost:8080/

# Or from repo root (auto-redirects to /site/):
python3 -m http.server 8080
```

## Regenerate index

```bash
python3 scripts/generate_site_data.py
```

Updates `site/data.js` (topics, LeetCode tags, GitHub URLs).

## Files

| File | Role |
|------|------|
| `index.html` | UI (Tailwind CDN) |
| `app.js` | Search, filters, GitHub file links |
| `data.js` | Auto-generated index |
| `.nojekyll` | Disable Jekyll on Pages |

On GitHub Pages, `.cpp` links open on GitHub (source view).
