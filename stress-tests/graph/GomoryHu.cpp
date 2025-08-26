#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GlobalMinCut.h"
#include "../../content/graph/Dinic.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include "../../content/graph/GomoryHu.h"
#pragma GCC diagnostic pop

int other(Edge e, int i) {
	if (e[0] == i) return (int)e[1];
	if (e[1] == i) return (int)e[0];
	assert(false);
}

Edge lighter(Edge a, Edge b) {
	return a[2] < b[2] ? a : b;
}

struct Test {
	int n;
	vector<Edge> ed;
	vector<vector<Edge>> tree;
	vector<vector<ll>> asMatrix;

	ll acrossCut(vi cutList) {
		vi cut(n);
		for (int i : cutList) cut[i] = true;

		ll r{};
		rep(i, n) rep(j, n) if (cut[i] && !cut[j])
			r += asMatrix[i][j];
		return r;
	}

	void dfs_vis(int i, int par, vi &visList) {
		visList.pb(i);
		for (Edge e : tree[i]) {
			int j = other(e, i);
			if (j != par)
				dfs_vis(j, i, visList);
		}
	}

	void dfs_check(int s, int t, int par, Edge light) {
		for (Edge e : tree[t]) {
			int i = other(e, t);
			e = s == t ? e : lighter(light, e);
			if (i != par)
				dfs_check(s, i, t, e);
		}
		if (s == t) return;

		Dinic dinic(n);
		for (auto [x, y, w] : ed)
			dinic.addEdge((int)x, (int)y, w, w);

		ll flow = dinic.maxFlow(s, t);
		vi cutList;
		dfs_vis((int)light[0], (int)light[1], cutList);
		ll across = acrossCut(cutList);
		if (flow != light[2] || flow != across) {
			deb(flow, across, light);
			deb(cutList);
			deb(ed);
			deb(tree);
			exit(-1);
		}
	}

	Test(int n_, vector<Edge> ed_) : n(n_), ed(ed_), tree(n), asMatrix(n, vector<ll>(n)) {
		Edge lightest{-1, -1, ll(4e18)};
		for (auto e : gomoryHu(n, ed)) {
			tree[e[0]].pb(e);
			tree[e[1]].pb(e);
			lightest = lighter(lightest, e);
		}

		for (auto [x, y, w] : ed) {
			asMatrix[x][y] += w;
			asMatrix[y][x] += w;
		}

		rep(i, n)
			dfs_check(i, i, i, {});

		if (n < 2) return;
		auto [flow, cutList] = globalMinCut(asMatrix);
		ll across = acrossCut(cutList);

		if (flow != lightest[2] || flow != across) {
			deb(flow, across, lightest);
			deb(cutList);
			deb(ed);
			deb(tree);
			exit(-1);
		}
	}
};

int main() {
	for (int n : {0,1,2,3,4,5,10,15,25,50}) rep(mul, 10) for (ll bound : {2LL, 100LL, ll(1e12)}) {
		deb(n, mul, bound);

		mt19937 rnd{(long unsigned int)(bound * 156 + n * 1516 + mul * 2322)};
		vector<Edge> ed;

		rep(_, n * (mul + 1)) {
			ll i = rnd() % n, j = rnd() % n, w = rnd() % bound;
			if (i != j) ed.pb({i, j, w});
		}

		Test(n, ed);
	}

	cout<<"Tests passed!"<<endl;
}
