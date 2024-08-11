/**
 * Author: Krzysztof Potępa, Bartłomiej Bosek
 * Date: 202-10-27
 * License: ???
 * Source: ???
 * Description: Bosek's algorithm for partially online bipartite maximum matching - 
 * white vertices (right side) are fixed, black vertices (left) are added
 * one by one. 
 *  \begin{itemize*}
 *  \item match[v] = index of black vertex matched to white vertex v or -1 if unmatched
 *  \item Black vertices are indexed in order they were added, from 0.
 *  \end{itemize*}
 * 
 * Time: O(E\sqrt V)
 * Status: Tested on https://judge.yosupo.jp/problem/bipartitematching
 */

struct Matching : vi { // Usage: Matching match(num_white);
	vector<vi> adj; vi rank, low, pos, vis, seen; int k{0};
	Matching(int n = 0) : vi(n, -1), rank(n) {} 
	bool add(vi vec) { //match.add(indices_of_white_neighbours);
		adj.pb(move(vec));
		low.pb(0); pos.pb(0); vis.pb(0);
		if (!adj.back().empty()) {
			int i = k;
		nxt:
			seen.clear();
			if (dfs(sz(adj)-1, ++k-i)) return 1;
			for(auto v: seen) for(auto e: adj[v])
				if (rank[e] < 1e9 && vis[at(e)] < k)
					goto nxt;
			for(auto v: seen) for(auto w: adj[v])
				rank[w] = low[v] = 1e9;
		}
		return 0;
	} //returns 1 if matching size increased
	bool dfs(int v, int g) {
		if (vis[v] < k) vis[v] = k, seen.pb(v);
		while (low[v] < g) {
			int e = adj[v][pos[v]];
			if (at(e) != v && low[v] == rank[e]) {
				rank[e]++;
				if (at(e) == -1 || dfs(at(e), rank[e]))
					return at(e) = v, 1;
			} else if (++pos[v] == sz(adj[v])) {
				pos[v] = 0, low[v]++;
			}
		}
		return 0; } };