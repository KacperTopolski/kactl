/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: match[v] = vert matched to v or -1, returns num edges in matching
 * Time: O(?)
 */
#pragma once
vi vertexCover(vector<vi>& G, vi& match) {
	vi ret, col(sz(G)), seen(sz(G));
	auto dfs = [&](auto f, int i, int c) -> void {
		if (col[i]) { return; } col[i] = c+1;
		for (auto e : G[i]) f(f, e, !c);
	};
	auto aug = [&](auto f, int i) -> void {
		if (seen[i] || col[i] != 1) { return;} seen[i]=1;
		for (auto e : G[i]) seen[e] = 1, f(f, match[e]);
	};
	rep(i, sz(G)) dfs(dfs, i, 0);
	rep(i, sz(G)) if (match[i]<0) aug(aug, i);
	rep(i, sz(G)) if (seen[i]==col[i]-1)ret.pb(i);
	return ret; }
