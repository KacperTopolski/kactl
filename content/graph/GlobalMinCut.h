/**
 * Author: Simon Lindholm
 * Date: 2021-01-09
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: Stress-tested together with GomoryHu
 */
#pragma once

using T = ll;
const T INF = 1e18;
pair<T, vi> globalMinCut(vector<vector<T>> mat) {
	pair<T, vi> best = {INF, {}};
	int n = sz(mat);
	vector<vi> co(n);
	rep(i,n) co[i] = {i};
	fwd(ph,1,n) {
		auto w = mat[0];
		size_t s = 0, t = 0;
		fwd(it,0,n-ph) { // O(V^2) -> O(E log V) with
			w[t] = -INF; // prio. queue
			s = t, t = max_element(all(w)) - w.begin();
			rep(i,n) w[i] += mat[t][i];
		}
		best = min(best, {w[t] - mat[t][t], co[t]});
		co[s].insert(co[s].end(), all(co[t]));
		rep(i,n) mat[s][i] += mat[t][i];
		rep(i,n) mat[i][s] = mat[s][i];
		mat[0][t] = -INF;
	}
	return best;
}
