#!/usr/bin/env bash
# Serve the static site (not the repo root listing)
cd "$(dirname "$0")/../site" || exit 1
PORT="${1:-8080}"
echo "→ http://localhost:${PORT}/"
python3 -m http.server "$PORT"
