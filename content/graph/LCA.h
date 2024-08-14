/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N/A
 * Description: Provides lca(v, u) and compress(ss) functions. Compress returns a list of (par, orig\_index) representing a tree rooted at 0. ss is the subset of nodes to be compressed.
 * Status: stress-tested
 */
#pragma once
#include "../data-structures/RMQ.h"
struct LCA { // takes up 5 * N memory + RMQ (be careful)
	vi t, it, et, rv; // time, inverse-time, euler-tour times
	RMQ<int> rmq;  // times are given in dfs preorder
	LCA(vector<vi> &g) : t(sz(g)), rv(sz(g)) {
		if (sz(g) == 0) return;
		dfs(g, 0, -1);
		rmq = RMQ<int>(et);
	}
	void dfs(vector<vi> &g, int v, int p) {
		t[v] = sz(it); it.pb(v);
		for (int u : g[v]) if (u != p)
			et.pb(t[v]), dfs(g, u, v);
	}
	int lca(int v, int u) {
		if (v == u) return v;
		if (t[v] > t[u]) swap(v, u);
		return it[rmq.get(t[v], t[u] - 1)];
	}
	vector<pii> compress(vi &ss) { // 3 * sz(ss) lca queries
		if (sz(ss) == 0) return {};
		auto cmp = [&] (int v, int u) { return t[v] < t[u]; };
		sort(all(ss), cmp); int m = sz(ss) - 1;
		rep(i, m) ss.pb(lca(ss[i], ss[i + 1]));
		sort(all(ss), cmp);
		ss.erase(unique(all(ss)), ss.end());
		vector<pii> r; int v = ss[0], u;
		rep(i, sz(ss)) {
			rv[u = ss[i]] = i;
			r.pb({rv[lca(v, u)], u}), v = u;
		}
		return r; } };
