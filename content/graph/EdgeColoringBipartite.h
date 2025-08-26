/**
 * Author: koosaga
 * License: N / A
 * Source: https://github.com/koosaga/olympiad/blob/master/Library/codes/graph/edgecolor_bipartite.cpp
 * Description: Bipartite edge coloring (simple graphs only!), edges is list of (left vert, right vert).
 * Returns list of colors of edges, in the range [0..max\_deg-1]
 * Time: O(NM)
 */
#pragma once

vi edgeColoring(int n, vector<pii> eds) { // n = 1 + max over eds
	int m = sz(eds), c[2]{};
	vi deg[2], col(m);
	vector<vector<pii>> has[2];
	rep(i, 2) {
		deg[i].resize(n+1);
		has[i].resize(n+1, vector<pii>(n+1));
	}

	auto dfs = [&](auto f, int x, int p) -> void {
		pii i = has[p][x][c[!p]];
		if (has[!p][i.st][c[p]].nd) f(f, i.st, !p);
		else has[!p][i.st][c[!p]] = {};
		has[p][x][c[p]] = i;
		has[!p][i.st][c[p]] = {x, i.nd};
		if (i.nd) col[i.nd-1] = c[p]-1;
	};

	rep(i, m) {
		int x[2] = {eds[i].st+1, eds[i].nd+1};
		rep(d, 2) {
			deg[d][x[d]]++;
			for (c[d] = 1; has[d][x[d]][c[d]].nd;)
				c[d]++;
		}
		if (c[0]-c[1]) dfs(dfs, x[1], 1);
		rep(d, 2)
			has[d][x[d]][c[0]] = {x[!d], i+1};
		col[i] = c[0]-1;
	}
	return col;
}
