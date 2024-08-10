/**
 * Author: Oleksandr Bacherikov, chilli
 * Date: 2019-05-07
 * License: Boost Software License
 * Source: https://github.com/AlCash07/ACTL/blob/master/include/actl/geometry/algorithm/intersect/line_convex_polygon.hpp
 * Description: Line-convex polygon intersection. The polygon must be ccw and have no collinear points.
 * lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
 *  \begin{itemize*}
 *  \item $(-1, -1)$ if no collision,
 *  \item $(i, -1)$ if touching the corner $i$,
 *  \item $(i, i)$ if along side $(i, i+1)$,
 *  \item $(i, j)$ if crossing sides $(i, i+1)$ and $(j, j+1)$.
 *  \end{itemize*}
 *  In the last case, if a corner $i$ is crossed, this is treated as happening on side $(i, i+1)$.
 *  The points are returned in the same order as the line hits the polygon.
 * Time: O(\log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template <class P> int extrVertex(vector<P> &poly, function<P(P)> dir) {
	int n = sz(poly), lo = 0, hi = n;
	auto cmp = [&](int i, int j) {return sgn(dir(poly[i%n]).cross(poly[i % n] - poly[j % n]));};
	auto extr = [&](int i) {return  cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0;};
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
} //also, use extrVertex<P>(poly, [&](P) {return v.perp();}) for vector v
// to get the first ccw point of a hull with the max projection onto v

#define cmpL(i) sgn(a.cross(poly[i], b))
template <class P> array<int, 2> lineHull(P a, P b, vector<P> &poly) {
	int endA = extrVertex<P>(poly, [&](P) {return b - a;});
	int endB = extrVertex<P>(poly, [&](P) {return a - b;});
	if (cmpL(endA) < 0 || cmpL(endB) > 0)  return {-1, -1};
	array<int, 2> res;
	rep(i,2) {
		int lo = endB, hi = endA, n = sz(poly);
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}

template<class P> pii getTangentPointOrSide(vector<P>& poly, P p, bool left) {
	int n = sz(poly); //left tangent is earlier on hull
	int i = extrVertex<P>(poly, [&](P q) {return left ? p-q : q-p;});
	return p.cross(poly[i], poly[(i+1)%n]) ? pii(i,i) : pii(i, (i+1)%n);
}
