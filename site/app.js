(function () {
  const data = window.REPO_DATA;
  if (!data) {
    document.body.innerHTML = '<p class="p-8 text-red-400">Missing data.js — run: python3 scripts/generate_site_data.py</p>';
    return;
  }

  const meta = data.meta || {};
  const isLocal = ['localhost', '127.0.0.1', ''].includes(location.hostname) || location.protocol === 'file:';
  const isPages = location.hostname.endsWith('github.io');

  let section = 'all';
  let query = '';

  const $ = (sel) => document.querySelector(sel);
  const tabsEl = $('#tabs');
  const topicsEl = $('#topics');
  const statsEl = $('#stats');
  const searchEl = $('#search');
  const modal = $('#modal');

  const TAB_COLORS = {
    all: 'bg-ink-700 text-white',
    dsa: 'bg-emerald-600/20 text-emerald-300 ring-emerald-500/40',
    cp: 'bg-amber-600/20 text-amber-300 ring-amber-500/40',
  };

  function repoFile(path) {
    if (isLocal && location.protocol !== 'file:') return '../' + path;
    if (isLocal) return meta.repoUrl ? `${meta.repoUrl}/blob/${meta.branch}/${path}` : path;
    return `${meta.repoUrl}/blob/${meta.branch}/${path}`;
  }

  function repoReadme(path) {
    return repoFile(path);
  }

  function ext(path) {
    return isPages || isLocal && location.protocol === 'file:' ? ' target="_blank" rel="noopener"' : '';
  }

  function initStats() {
    const s = data.stats;
    statsEl.innerHTML = [
      { label: 'DSA files', val: s.dsaFiles, cls: 'text-emerald-400' },
      { label: 'CP files', val: s.cpFiles, cls: 'text-amber-400' },
      { label: 'Topics', val: s.dsaTopics + s.cpTopics, cls: 'text-slate-300' },
    ].map(({ label, val, cls }) =>
      `<span class="px-3 py-1.5 rounded-lg bg-ink-800 border border-ink-700"><span class="${cls} font-semibold">${val}</span> <span class="text-slate-500">${label}</span></span>`
    ).join('');
    $('#generated-at').textContent = `Data generated: ${data.generated}`;

    if (isPages && meta.pagesUrl) {
      const sub = $('#subtitle');
      if (sub) sub.innerHTML = `Live on <a href="${meta.pagesUrl}" class="text-accent hover:underline">GitHub Pages</a>`;
    }
  }

  function initQuickLinks() {
    const links = [
      ['#link-root', 'README.md'],
      ['#link-dsa', 'DSA/README.md'],
      ['#link-cp', 'CP/README.md'],
    ];
    links.forEach(([sel, path]) => {
      const el = $(sel);
      if (el) {
        el.href = repoReadme(path);
        if (isPages || location.protocol === 'file:') el.target = '_blank';
      }
    });

    const pagesEl = $('#pages-url');
    if (pagesEl && meta.pagesUrl) {
      pagesEl.href = meta.pagesUrl;
      pagesEl.textContent = meta.pagesUrl.replace('https://', '');
    }
  }

  function initTabs() {
    ['all', 'dsa', 'cp'].forEach((t) => {
      const btn = document.createElement('button');
      btn.type = 'button';
      btn.dataset.tab = t;
      btn.textContent = t === 'all' ? 'All' : t.toUpperCase();
      btn.className = 'tab-btn px-4 py-2 rounded-lg text-sm font-medium ring-1 ring-ink-700 transition';
      btn.addEventListener('click', () => {
        section = t;
        document.querySelectorAll('.tab-btn').forEach((b) => {
          b.className = 'tab-btn px-4 py-2 rounded-lg text-sm font-medium ring-1 ring-ink-700 text-slate-400 hover:text-white transition';
        });
        btn.className = `tab-btn px-4 py-2 rounded-lg text-sm font-medium ring-1 ${TAB_COLORS[t]} transition`;
        render();
      });
      tabsEl.appendChild(btn);
    });
    tabsEl.querySelector('[data-tab="all"]').click();
  }

  function allTopics() {
    const dsa = data.dsa.map((t) => ({ ...t, section: 'dsa' }));
    const cp = data.cp.map((t) => ({ ...t, section: 'cp' }));
    return [...dsa, ...cp];
  }

  function matches(topic, q) {
    if (!q) return true;
    q = q.toLowerCase();
    if (topic.name.toLowerCase().includes(q)) return true;
    if (topic.path.toLowerCase().includes(q)) return true;
    return topic.files.some(
      (f) =>
        f.name.toLowerCase().includes(q) ||
        f.problem.toLowerCase().includes(q) ||
        f.leetcode.toLowerCase().includes(q)
    );
  }

  function filtered() {
    let list = allTopics();
    if (section === 'dsa') list = list.filter((t) => t.section === 'dsa');
    if (section === 'cp') list = list.filter((t) => t.section === 'cp');
    if (query) list = list.filter((t) => matches(t, query));
    return list;
  }

  function openModal(topic) {
    $('#modal-title').textContent = topic.name;
    $('#modal-path').textContent = topic.path + '/';
    const box = $('#modal-files');
    box.innerHTML = topic.files
      .map((f) => {
        const lc = f.leetcode
          ? `<span class="text-xs text-accent-light">${esc(f.leetcode)}</span>`
          : '';
        const href = repoFile(f.path);
        return `<a href="${escAttr(href)}"${ext(f.path)} class="block p-3 rounded-lg bg-ink-800 border border-ink-700 hover:border-accent/30 transition group">
          <div class="font-mono text-sm text-white group-hover:text-accent-light">${esc(f.name)}</div>
          <div class="text-xs text-slate-500 mt-1">${esc(f.problem)}</div>
          ${lc}
        </a>`;
      })
      .join('');
    modal.classList.remove('hidden');
  }

  function esc(s) {
    const d = document.createElement('div');
    d.textContent = s;
    return d.innerHTML;
  }

  function escAttr(s) {
    return s.replace(/&/g, '&amp;').replace(/"/g, '&quot;').replace(/</g, '&lt;');
  }

  function render() {
    const list = filtered();
    $('#result-count').textContent = `${list.length} topic${list.length !== 1 ? 's' : ''}${query ? ` for “${query}”` : ''}`;
    $('#empty').classList.toggle('hidden', list.length > 0);
    topicsEl.innerHTML = list
      .map((t) => {
        const badge =
          t.section === 'dsa'
            ? 'bg-emerald-500/10 text-emerald-400'
            : 'bg-amber-500/10 text-amber-400';
        const preview = t.files
          .slice(0, 3)
          .map((f) => f.name.replace('.cpp', ''))
          .join(', ');
        return `<article class="topic-card cursor-pointer p-5 rounded-xl bg-ink-800 border border-ink-700 hover:border-slate-600 transition flex flex-col"
          data-id="${esc(t.id)}">
          <div class="flex items-start justify-between gap-2 mb-2">
            <h3 class="font-semibold text-white leading-tight">${esc(t.name)}</h3>
            <span class="shrink-0 text-xs px-2 py-0.5 rounded-full ${badge}">${t.section.toUpperCase()}</span>
          </div>
          <p class="text-xs font-mono text-slate-500 mb-3">${esc(t.path)}/</p>
          <p class="text-xs text-slate-400 line-clamp-2 flex-1">${esc(preview)}${t.fileCount > 3 ? '…' : ''}</p>
          <div class="mt-4 pt-3 border-t border-ink-700 flex justify-between items-center">
            <span class="text-sm font-medium text-slate-300">${t.fileCount} files</span>
            <span class="text-xs text-accent">View →</span>
          </div>
        </article>`;
      })
      .join('');

    topicsEl.querySelectorAll('.topic-card').forEach((el, i) => {
      el.addEventListener('click', () => openModal(list[i]));
    });
  }

  function initModal() {
    modal.querySelectorAll('[data-close]').forEach((el) => {
      el.addEventListener('click', () => modal.classList.add('hidden'));
    });
    document.addEventListener('keydown', (e) => {
      if (e.key === 'Escape') modal.classList.add('hidden');
    });
  }

  function initTemplate() {
    if (!data.template) return;
    $('#template-section').classList.remove('hidden');
    const link = $('#template-link');
    link.href = repoFile(data.template.path);
    if (isPages || location.protocol === 'file:') link.target = '_blank';
  }

  function initFooter() {
    const localHint = $('#local-hint');
    const pagesHint = $('#pages-hint');
    if (isPages) {
      if (localHint) localHint.classList.add('hidden');
      if (pagesHint) pagesHint.classList.remove('hidden');
    }
  }

  searchEl.addEventListener('input', (e) => {
    query = e.target.value.trim();
    render();
  });

  initStats();
  initQuickLinks();
  initTabs();
  initModal();
  initTemplate();
  initFooter();
})();
