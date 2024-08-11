/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

#include "TurboMatching.h"

vi cover(vector<vi> &g, int n, int m) { // sizes of left and right sets, g = [left][right]
	vi match(n + m, -1);
	int res = turboMatching(g, match);
	vector<bool> lfound(n, true), seen(n + m);
	fwd(i, n, n + m) if (match[i] != -1) lfound[match[i]] = false;
	vi q, cover;
	rep(i,n) if (lfound[i]) q.pb(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.pb(match[e]);
		}
	}
	rep(i,n) if (!lfound[i]) cover.pb(i);
	fwd(i, n, n + m) if (seen[i]) cover.pb(i);
	assert(sz(cover) == res);
	return cover;
}
