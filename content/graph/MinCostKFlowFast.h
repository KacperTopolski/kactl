/**
 * Author: Amtek
 * Date: 2023-10-24
 * License: CC0
 * Source: N/A
 * Description: Min cost K-flow. Supports fast 1st phase distance computation
 * Time: O(INIT + Fn\log n) $INIT \le V E$ and depends on first dist computation
 * Status: tested on https://codeforces.com/gym/102759/problem/F and kattis:maxflowmincost
 */

#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

struct MCMF {
	const ll INF = 2e18;
	struct edge {
		int from, to, rev; ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vi seen;
	vector<ll> dist, pi;
	vector<edge*> par;
	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}
	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].pb(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].pb(edge{ to,from,sz(ed[from])-1,0,-cost,0 });
	}
	void path(int s) {
		fill(all(seen), 0); fill(all(dist), INF);
		dist[s] = 0; ll di;
		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});
		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		rep(i,N) pi[i] = min(pi[i] + dist[i], INF);
	}
	pair<ll, ll> maxflow(int s, int t, ll k = -1) {
		if (k == -1) k = INF;
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = k - totflow;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);
			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
			if (totflow == k) break;
		}
		rep(i,N) for(edge& e : ed[i]) totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}
	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			rep(i,N) if (pi[i] != INF)
				for (edge& e : ed[i]) if (e.cap)
					if ((v = pi[i] + e.cost) < pi[e.to])
						pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};
