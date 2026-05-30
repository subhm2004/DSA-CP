# Static Site

Browser UI for DSA & CP — deployed on **GitHub Pages**.

## Live URL

After enabling Pages (see below):

**https://subhm2004.github.io/DSA/**

## One-time GitHub setup

1. Push this repo to `main`
2. GitHub repo → **Settings** → **Pages**
3. **Build and deployment** → Source: **GitHub Actions**
4. Push triggers [`.github/workflows/pages.yml`](../.github/workflows/pages.yml) automatically

First deploy ~1–2 min. Check **Actions** tab if site doesn’t load.

## Local dev

```bash
python3 -m http.server 8080
# → http://localhost:8080/site/
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
