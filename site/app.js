(function () {
  const data = window.REPO_DATA;
  if (!data) {
    document.body.innerHTML =
      '<div class="min-h-screen flex items-center justify-center p-8"><p class="text-red-400 bg-red-950/30 border border-red-500/30 rounded-xl px-6 py-4">Missing data.js — run: python3 scripts/generate_site_data.py</p></div>';
    return;
  }

  const meta = data.meta || {};
  const isLocal =
    ['localhost', '127.0.0.1', ''].includes(location.hostname) || location.protocol === 'file:';
  const isPages = location.hostname.endsWith('github.io');

  let section = 'all';
  let query = '';

  const $ = (sel) => document.querySelector(sel);
  const tabsEl = $('#tabs');
  const topicsEl = $('#topics');
  const statsEl = $('#stats');
  const searchEl = $('#search');
  const modal = $('#modal');

  const TAB_STYLES = {
    all: {
      active: 'active bg-white/10 text-white ring-white/20 shadow-sm',
      idle: 'text-slate-400 hover:text-white hover:bg-white/5',
    },
    dsa: {
      active: 'active bg-emerald-500/15 text-emerald-300 ring-emerald-500/30',
      idle: 'text-slate-400 hover:text-emerald-300 hover:bg-emerald-500/5',
    },
    cp: {
      active: 'active bg-amber-500/15 text-amber-300 ring-amber-500/30',
      idle: 'text-slate-400 hover:text-amber-300 hover:bg-amber-500/5',
    },
  };

  const STAT_ICONS = {
    dsa: `<svg class="w-3.5 h-3.5" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 12l2 2 4-4"/></svg>`,
    cp: `<svg class="w-3.5 h-3.5" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M13 10V3L4 14h7v7l9-11h-7z"/></svg>`,
    topics: `<svg class="w-3.5 h-3.5" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 6h16M4 10h16M4 14h16M4 18h16"/></svg>`,
  };

  function repoFile(path) {
    if (isLocal && location.protocol !== 'file:') return '../' + path;
    if (isLocal) return meta.repoUrl ? `${meta.repoUrl}/blob/${meta.branch}/${path}` : path;
    return `${meta.repoUrl}/blob/${meta.branch}/${path}`;
  }

  function ext() {
    return isPages || (isLocal && location.protocol === 'file:') ? ' target="_blank" rel="noopener"' : '';
  }

  function esc(s) {
    const d = document.createElement('div');
    d.textContent = s;
    return d.innerHTML;
  }

  function escAttr(s) {
    return s.replace(/&/g, '&amp;').replace(/"/g, '&quot;').replace(/</g, '&lt;');
  }

  function highlight(text, q) {
    if (!q || !text) return esc(text);
    const lower = text.toLowerCase();
    const idx = lower.indexOf(q.toLowerCase());
    if (idx === -1) return esc(text);
    const before = text.slice(0, idx);
    const match = text.slice(idx, idx + q.length);
    const after = text.slice(idx + q.length);
    return `${esc(before)}<mark class="hl">${esc(match)}</mark>${esc(after)}`;
  }

  function initStats() {
    const s = data.stats;
    statsEl.innerHTML = [
      { label: 'DSA', val: s.dsaFiles, cls: 'text-emerald-400', icon: STAT_ICONS.dsa },
      { label: 'CP', val: s.cpFiles, cls: 'text-amber-400', icon: STAT_ICONS.cp },
      { label: 'Topics', val: s.dsaTopics + s.cpTopics, cls: 'text-indigo-300', icon: STAT_ICONS.topics },
    ]
      .map(
        ({ label, val, cls, icon }) =>
          `<span class="inline-flex items-center gap-2 px-3 py-1.5 rounded-xl bg-ink-800/80 border border-ink-600/60 backdrop-blur-sm">
            <span class="${cls} opacity-80">${icon}</span>
            <span class="${cls} font-bold tabular-nums">${val}</span>
            <span class="text-slate-500">${label}</span>
          </span>`
      )
      .join('');

    $('#generated-at').textContent = `Index updated ${data.generated}`;

    if (isPages && meta.pagesUrl) {
      const sub = $('#subtitle');
      if (sub)
        sub.innerHTML = `Live on <a href="${meta.pagesUrl}" class="text-accent hover:underline font-medium">GitHub Pages</a>`;
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
        el.href = repoFile(path);
        if (isPages || location.protocol === 'file:') el.target = '_blank';
      }
    });

    const repoLink = $('#repo-link');
    if (repoLink && meta.repoUrl) {
      repoLink.href = meta.repoUrl;
      if (isPages || location.protocol === 'file:') repoLink.target = '_blank';
    }

    const pagesEl = $('#pages-url');
    const pagesHint = $('#pages-hint');
    if (pagesEl && meta.pagesUrl) {
      pagesEl.href = meta.pagesUrl;
      pagesEl.textContent = meta.pagesUrl.replace('https://', '');
      pagesEl.classList.remove('hidden');
      if (pagesHint) pagesHint.classList.remove('hidden');
    }
  }

  function initTabs() {
    ['all', 'dsa', 'cp'].forEach((t) => {
      const btn = document.createElement('button');
      btn.type = 'button';
      btn.dataset.tab = t;
      btn.textContent = t === 'all' ? 'All topics' : t.toUpperCase();
      btn.className =
        'tab-btn px-5 py-2 rounded-full text-sm font-medium ring-1 ring-ink-600/80 transition-all duration-200';
      btn.addEventListener('click', () => {
        section = t;
        document.querySelectorAll('.tab-btn').forEach((b) => {
          const tab = b.dataset.tab;
          b.className = `tab-btn px-5 py-2 rounded-full text-sm font-medium ring-1 ring-ink-600/80 transition-all duration-200 ${TAB_STYLES[tab].idle}`;
        });
        btn.className = `tab-btn px-5 py-2 rounded-full text-sm font-medium ring-1 transition-all duration-200 ${TAB_STYLES[t].active}`;
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

  function topicAccent(section) {
    return section === 'dsa'
      ? {
          bar: 'bg-emerald-500',
          badge: 'bg-emerald-500/12 text-emerald-400 ring-emerald-500/20',
          icon: 'text-emerald-400 bg-emerald-500/10',
          arrow: 'text-emerald-400',
        }
      : {
          bar: 'bg-amber-500',
          badge: 'bg-amber-500/12 text-amber-400 ring-amber-500/20',
          icon: 'text-amber-400 bg-amber-500/10',
          arrow: 'text-amber-400',
        };
  }

  function openModal(topic) {
    const accent = topicAccent(topic.section);
    $('#modal-title').innerHTML = highlight(topic.name, query);
    $('#modal-path').textContent = topic.path + '/';
    $('#modal-meta').textContent = `${topic.fileCount} file${topic.fileCount !== 1 ? 's' : ''} · click to open on GitHub`;

    const box = $('#modal-files');
    box.innerHTML = topic.files
      .map((f) => {
        const lc = f.leetcode
          ? `<span class="inline-flex items-center gap-1 mt-1.5 text-xs text-indigo-300 bg-indigo-500/10 px-2 py-0.5 rounded-md">${highlight(f.leetcode, query)}</span>`
          : '';
        const href = repoFile(f.path);
        return `<a href="${escAttr(href)}"${ext()} class="file-row block p-4 rounded-xl bg-ink-800/60 border border-ink-600/50 hover:border-indigo-500/30 hover:bg-ink-800 group">
          <div class="flex items-start gap-3">
            <div class="w-8 h-8 rounded-lg ${accent.icon} flex items-center justify-center shrink-0 mt-0.5">
              <svg class="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10 20l4-16m4 4l4 4-4 4M6 16l-4-4 4-4"/></svg>
            </div>
            <div class="min-w-0 flex-1">
              <div class="font-mono text-sm text-white group-hover:text-indigo-300 transition-colors truncate">${highlight(f.name, query)}</div>
              <div class="text-xs text-slate-500 mt-1 line-clamp-2">${highlight(f.problem, query)}</div>
              ${lc}
            </div>
            <svg class="w-4 h-4 text-slate-600 group-hover:text-indigo-400 shrink-0 mt-1 transition-colors" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M10 6H6a2 2 0 00-2 2v10a2 2 0 002 2h10a2 2 0 002-2v-4M14 4h6m0 0v6m0-6L10 14"/></svg>
          </div>
        </a>`;
      })
      .join('');
    modal.classList.remove('hidden');
    document.body.style.overflow = 'hidden';
  }

  function closeModal() {
    modal.classList.add('hidden');
    document.body.style.overflow = '';
  }

  function render() {
    const list = filtered();
    const q = query.toLowerCase();

    $('#result-count').textContent =
      list.length > 0
        ? `${list.length} topic${list.length !== 1 ? 's' : ''}${query ? ` matching “${query}”` : ''}`
        : '';

    $('#empty').classList.toggle('hidden', list.length > 0);
    topicsEl.innerHTML = list
      .map((t, i) => {
        const a = topicAccent(t.section);
        const preview = t.files
          .slice(0, 3)
          .map((f) => f.name.replace('.cpp', ''))
          .join(' · ');
        const lcCount = t.files.filter((f) => f.leetcode).length;
        const delay = Math.min(i * 0.03, 0.45);

        return `<article class="topic-card ${t.section} cursor-pointer p-5 rounded-2xl bg-ink-800/50 border border-ink-600/50 flex flex-col relative overflow-hidden"
          data-id="${esc(t.id)}" style="animation: fadeUp 0.4s ease-out ${delay}s both">
          <div class="absolute top-0 left-0 right-0 h-0.5 ${a.bar} opacity-60"></div>
          <div class="flex items-start justify-between gap-2 mb-2">
            <h3 class="font-display font-semibold text-white leading-tight">${highlight(t.name, q)}</h3>
            <span class="shrink-0 text-[10px] font-semibold uppercase tracking-wide px-2 py-0.5 rounded-full ring-1 ${a.badge}">${t.section}</span>
          </div>
          <p class="text-[11px] font-mono text-slate-600 mb-3 truncate">${esc(t.path)}/</p>
          <p class="text-xs text-slate-400 line-clamp-2 flex-1 leading-relaxed">${esc(preview)}${t.fileCount > 3 ? ' …' : ''}</p>
          <div class="mt-4 pt-3 border-t border-ink-700/60 flex justify-between items-center">
            <div class="flex items-center gap-3">
              <span class="text-sm font-semibold text-slate-300 tabular-nums">${t.fileCount} <span class="font-normal text-slate-500">files</span></span>
              ${lcCount ? `<span class="text-[10px] text-indigo-400/80 bg-indigo-500/10 px-1.5 py-0.5 rounded">${lcCount} LC</span>` : ''}
            </div>
            <span class="text-xs font-medium ${a.arrow} flex items-center gap-0.5 group-hover:gap-1.5 transition-all">
              Browse
              <svg class="w-3.5 h-3.5" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M9 5l7 7-7 7"/></svg>
            </span>
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
      el.addEventListener('click', closeModal);
    });
    document.addEventListener('keydown', (e) => {
      if (e.key === 'Escape') closeModal();
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
    if (isPages && localHint) localHint.classList.add('hidden');
  }

  function initSearchShortcut() {
    document.addEventListener('keydown', (e) => {
      if (e.key === '/' && document.activeElement !== searchEl) {
        e.preventDefault();
        searchEl.focus();
      }
    });
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
  initSearchShortcut();
})();
