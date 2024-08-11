/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N/A
 * Description: BF dist(E). unreachable <=> dist[v] = INF. reachable by negative cycle dist[v] = -INF. par[v] = parent in shortest path tree cyc = negative vertices in order. set s=-1 to find any negative cycle
 * set INF and T according to specific needs. optimize the middle loop if you dont need to reconstruct the negative cycle / dont need shortest path tree. set its = n / 3 + 100 if you random shuffle vertex ids beforehand
 * Time: O(VE)
 * Status: Tested on stresstests & https://cses.fi/problemset/task/1197/ & https://open.kattis.com/problems/shortestpath3
 */
#pragma once
using T = ll; const T INF = LLONG_MAX;
struct Edge {
	int v, u; T w; // var_u <= var_v + w
	int f() { return v < u ? v + 1 : -v; }
};
struct BF : vector<T> {
	vi par, cyc;
	BF(vector<Edge> E, int n, int s = -1)
	: vector<T>(n, ~s ? INF : 0), par(n, -1) {
		if (~s) { at(s) = 0; } int k, its = n / 2 + 2;
		sort(all(E), [&] (Edge a, Edge b) {
			return a.f() < b.f();
		});
		rep(i, its) { k = -1;
			for (auto [v, u, w] : E) {
				T d = (abs(at(v)) == INF ? INF : at(v) + w);
				if (d < at(u)) {
					at(u) = (i < its - 1 ? d : -INF);
					par[k = u] = v;
				}
			}
		} // optimize above if no need for negative cycle
		if (k >= 0) { // finds negative simple cycle
			rep(i, its) for (auto [v, u, w] : E)
			if (at(v) == -INF) at(u) = -INF;
			rep(i, n) { k = par[k]; } cyc = {k};
			for (int v = par[k]; v != k; v = par[v])
				cyc.pb(v);
			reverse(all(cyc)); } } };