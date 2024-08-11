/**
 * Author: Krzysztof Potępa / Antoni Długosz
 * Date: 2024
 * License: N/A
 * Description: sat.either(x, \~y). Uses kosaraju
 * Usage: SAT2 sat(variable_cnt), sat.solve(),
 * sat[i] = value of i-th variable (0 or 1),
 * (internally: i_false_id = 2i, i_true_id = 2i + 1)
 * Time: O(|Santa Clauses| + |Variables|)
 * Status: tested on https://judge.yosupo.jp/submission/227184 & https://basecamp.eolymp.com/en/problems/7538
 */
#pragma once
struct SAT2 : vi {
	vector<vi> G; vi order, flags;
	SAT2(int n = 0) : G(n*2) {}
	void imply(int i, int j) { // Add (i => j) constraint
		i = max(2*i, -1-2*i); j = max(2*j, -1-2*j);
		G[i^1].pb(j^1); G[j].pb(i);
	} // Add (i v j) constraint
	void either(int i, int j) { imply(~i, j); }
	bool solve() { // Saves assignment in values[]
		assign(sz(G)/2, -1); flags.assign(sz(G), 0);
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
		order.pb(i);
	}
	bool propag(int i, bool first) {
		if (!flags[i]) { return 1; } flags[i] = 0;
		if (at(i/2) >= 0) return first;
		at(i/2) = i&1;
		for (auto e : G[i]) if (!propag(e, 0)) return 0;
		return 1;
	}
	// NEXT PART NOT ALWAYS NEEDED
	int addVar() { G.resize(sz(G)+2); return sz(G)/2 - 1; }
	void atMostOneTrue(vi& vars) {
		int y, x = addVar();
		for (auto i : vars) {
			imply(x, y = addVar());
			imply(i, ~x); imply(i, x = y);
		} } };