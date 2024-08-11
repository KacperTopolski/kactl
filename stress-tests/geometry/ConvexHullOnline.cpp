#include "../utilities/template.h"

#include "../../content/geometry/ConvexHullOnline.h"

namespace ch {
#include "../../content/geometry/ConvexHull.h"
}

namespace uw {
using LL = ll;
// https://github.com/tonowak/acmlib/blob/master/code/geo/convex-hull-online/main.cpp
using P = pair<int, int>;
LL operator*(P l, P r) {
	return l.first * LL(r.second) - l.second * LL(r.first);
}
P operator-(P l, P r) {
	return {l.first - r.first, l.second - r.second};
}
int sign(LL x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}
int dir(P a, P b, P c) {
	return sign((b - a) * (c - b));
}
struct UpperConvexHull {
	set<P> hull;
	void add_point(P p) {
		if(hull.empty()) {
			hull = {p};
			return;
		}
		auto it = hull.lower_bound(p);
		if(*hull.begin() < p and p < *prev(hull.end())) {
			assert(it != hull.end() and it != hull.begin());
			if(dir(*prev(it), p, *it) >= 0)
				return;
		}
		it = hull.emplace(p).first;
		auto have_to_rm = [&](auto iter) {
			if(iter == hull.end() or next(iter) == hull.end() or iter == hull.begin())
				return false;
			return dir(*prev(iter), *iter, *next(iter)) >= 0;
		};
		while(have_to_rm(next(it)))
			it = prev(hull.erase(next(it)));
		while(it != hull.begin() and have_to_rm(prev(it)))
			it = hull.erase(prev(it));
	}
};
}

bool check_eq(UpperHull &uj_hull, uw::UpperConvexHull &uw_hull) {
	if (sz(uj_hull) != sz(uw_hull.hull))
		return false;
	auto it = uw_hull.hull.begin();
	for (P p : uj_hull) {
		if (p.x != it->first) return false;
		if (p.y != it->second) return false;
		++it;
	}
	return true;
}

void test_online(vector<P> pts) {
	UpperHull uj;
	uw::UpperConvexHull uw;

	for (auto p : pts) {
		uj.add(p);
		uw.add_point({p.x, p.y});
		if (!check_eq(uj, uw)) {
			deb(uj);
			deb(uw.hull);
			assert(false);
		}
	}
}

void test_offline(vector<P> pts) {
	vector<P> should_be = ch::convexHull(pts);
	reverse(all(should_be));
	rotate(should_be.begin(), should_be.end() - 1, should_be.end());
	UpperHull up_online, down_online;
	for (auto [x, y] : pts) {
		up_online.add(P{x, y});
		down_online.add(P{-x, -y});
	}
	vector<P> up(all(up_online)), down(all(down_online));
	for (auto &[x, y] : down)
		x = -x, y = -y;

	up.pop_back();
	if (sz(down) > 1)
		down.pop_back();

	up.insert(up.end(), all(down));
	if (up != should_be) {
		deb(pts);
		deb(should_be);
		assert(false);
	}
}

int main() {
	mt19937_64 rnd;
	for (int range : vi{5, 15, 250, (int)1e5, (int)1e9}) rep(neg, 2) {
		for (int n : vi{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 50, 100, 200, 500, 1000, 2000}) rep(_, 1+100/n) {
			uniform_int_distribution dist(-range*neg, range);
			vector<P> pts;
			rep(_, n) {
				pts.emplace_back(dist(rnd), dist(rnd));
				test_offline(pts);
			}
			test_online(pts);
		}
	}
	cout<<"Tests passed!"<<endl;
}
