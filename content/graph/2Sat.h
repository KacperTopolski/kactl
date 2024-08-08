/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: Variables are indexed from 1 and negations are negative indices.
 * Usage: SAT2 sat(variable_cnt), sat.solve(),
 * sat[i] = value of i-th variable (0 or 1),
 * (internally: i_false_id = 2i-2, i_true_id = 2i-1)
 * Time: O(|Santa Clauses| + |Variables|)
 */
#pragma once
struct SAT2 : vi {
	vector<vi> G; vi order, flags;
	SAT2(int n = 0) : G(n*2) {}
	void imply(int i, int j) { // Add (i => j) constraint
		i = i*2 ^ i >> 31; j = j*2 ^ j >> 31;
		G[--i].push_back(--j); G[j^1].push_back(i^1);
	} // Add (i v j) constraint
	void either(int i, int j) { imply(-i, j); }
	bool solve() { // Saves assignment in values[]
		assign(sz(G)/2+1, -1); flags.assign(sz(G), 0);
		rep(i, sz(G)) dfs(i);
		while (sz(order)) {
			if (!propag(order.back()^1, 1)) return 0;
			order.pop_back();
		}
		return 1;
	}
	void dfs(int i) {
		if (flags[i]) { return; } flags[i] = 1;
		for (auto e : G[i]) dfs(e);
		order.push_back(i);
	}
	bool propag(int i, bool first) {
		if (!flags[i]) { return 1; } flags[i] = 0;
		if (at(i/2+1) >= 0) return first;
		at(i/2+1) = i&1;
		for (auto e : G[i]) if (!propag(e, 0)) return 0;
		return 1;
	}
	// NEXT PART NOT ALWAYS NEEDED
	int addVar() { G.resize(sz(G)+2); return sz(G)/2; }
	void atMostOneTrue(vi& vars) {
		int y, x = addVar();
		for (auto i : vars) {
			imply(x, y = addVar());
			imply(i, -x); imply(i, x = y);
		} } };