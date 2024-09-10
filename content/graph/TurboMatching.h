/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: match[v] = vert matched to v or -1, returns num edges in matching
 * Time: O(?)
 */
#pragma once
int matching(vector<vi>& G, vi& match) {
	vector<bool> seen; int n = 0, k = 1;
	match.assign(sz(G), -1);
	auto dfs = [&](auto f, int i) -> int {
		if (seen[i]) { return 0; } seen[i] = 1;
		for (auto e : G[i]) {
			if (match[e] < 0 || f(f, match[e])) {
				match[i] = e; match[e] = i; return 1;
			}
		}
		return 0;
	};
	while (k) {
		seen.assign(sz(G), 0); k = 0;
		rep(i, sz(G)) if (match[i] < 0) k += dfs(dfs, i);
		n += k;
	}
	return n;
}