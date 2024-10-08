/**
 * Author: Marcin Smulewicz
 * Date: ????
 * License: N/A
 * Description: SPFA with subtree erasure heuristic. Returns array of distances or empty array if negative cycle is reachable from source.
 * par[v] = parent in shortest path tree
 * Time: O(V E) but fast on random
 * Status: ????
 */

using Edge = pair<int, ll>;
vector<ll> spfa(vector<vector<Edge>>& G,
                vi& par, int src) {
	int n = sz(G); vi que, prv(n+1);
	iota(all(prv), 0); vi nxt = prv;
	vector<ll> dist(n, INT64_MAX);
	par.assign(n, -1);
	auto add = [&](int v, int p, ll d) {
		par[v] = p; dist[v] = d;
		prv[n] = nxt[prv[v] = prv[nxt[v] = n]] = v;
	};
	auto del = [&](int v) {
		nxt[prv[nxt[v]] = prv[v]] = nxt[v];
		prv[v] = nxt[v] = v;
	};
	for (add(src, -2, 0); nxt[n] != n;) {
		int v = nxt[n]; del(v);
		for (auto e : G[v]) {
			ll alt = dist[v] + e.y;
			if (alt < dist[e.x]) {
				que = {e.x};
				rep(i, sz(que)) {
					int w = que[i]; par[w] = -1;
					del(w);
					for (auto f : G[w])
						if (par[f.x] == w) que.pb(f.x);
				}
				if (par[v] == -1) return {};
				add(e.x, v, alt);
			}
		}
	}
	return dist; }