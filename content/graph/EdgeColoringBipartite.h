/**
 * Author: koosaga
 * License: N / A
 * Source: https://github.com/koosaga/olympiad/blob/master/Library/codes/graph_etc/edgecolor_bipartite.cpp
 * Description: Bipartite edge coloring, edges is list of (left vert, right vert). Returns number of used colors, which is equal to max degree.
 * col[i] = color of i-th edge [0..max\_deg-1]
 * Time: O(NM)
 */
#pragma once

int colorEdges(vector<pii>& edges, int n, vi& col) {
	int m = sz(edges), c[2] = {}, ans = 0;
	vi deg[2];
	vector<vector<pii>> has[2];
	col.assign(m, 0);
	rep(i, 2) {
		deg[i].resize(n+1);
		has[i].resize(n+1, vector<pii>(n+1));
	}

	auto dfs = [&](auto f, int x, int p)->void {
		pii i = has[p][x][c[!p]];
		if (has[!p][i.x][c[p]].y) f(f, i.x, !p);
		else has[!p][i.x][c[!p]] = {};
		has[p][x][c[p]] = i;
		has[!p][i.x][c[p]] = {x, i.y};
		if (i.y) col[i.y-1] = c[p]-1;
	};

	rep(i, m) {
		int x[2] = {edges[i].x+1, edges[i].y+1};
		rep(d, 2) {
			deg[d][x[d]]++;
			ans = max(ans, deg[d][x[d]]);
			for (c[d] = 1; has[d][x[d]][c[d]].y;)
				c[d]++;
		}
		if (c[0]-c[1]) dfs(dfs, x[1], 1);
		rep(d, 2)
			has[d][x[d]][c[0]] = {x[!d], i+1};
		col[i] = c[0]-1;
	}
	return ans;
}
