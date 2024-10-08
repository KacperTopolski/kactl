/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: Biconnected bi(graph),
 * bi[v] = indices of components containing v,
 * bi.verts[i] = vertices of i-th component,
 * bi.edges[i] = edges of i-th component,
 * Bridges $\iff$ components with 2 vertices,
 * Articulation points $\iff$ vertices in $> 1$ comp,
 * Isolated vertex $\iff$ empty component list
 * Time: O(|E| + |V|)
 */
#pragma once
struct Biconnected : vector<vi> {
	vector<vi> verts; vector<pii> S;
	vector<vector<pii>> edges;
	Biconnected() {}
	Biconnected(vector<vi>& G) : S(sz(G)) {
		resize(sz(G));
		rep(i, sz(G)) S[i].x ?: dfs(G, i, -1);
		rep(c, sz(verts)) for(auto v : verts[c])
			at(v).pb(c);
	}
	int dfs(vector<vi>& G, int v, int p) {
		int low = S[v].x = sz(S)-1; S.pb({v, -1});
		for (auto e : G[v]) if (e != p) {
			if (S[e].x < S[v].x) S.pb({v, e});
			low = min(low, S[e].x ?: dfs(G, e, v));
		}
		if (p + 1 && low >= S[p].x) {
			verts.pb({p}); edges.pb({});
			fwd(i, S[v].x, sz(S)) {
				if (S[i].y == -1)
					verts.back().pb(S[i].x);
				else edges.back().pb(S[i]);
			}
			S.resize(S[v].x);
		}
		return low; } };
