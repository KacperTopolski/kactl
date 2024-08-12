#include "../utilities/template.h"
#include "../../content/graph/BellmanFord.h"

namespace KACTL { // RIP if kactl bellman doesn't work :')
	const ll inf = LLONG_MAX;
	struct Ed { int a, b, w, s() { return a < b ? a : -a; }};
	struct Node { ll dist = inf; int prev = -1; };

	void bellmanFord(vector<Node>& nodes, vector<Ed>& eds, int s) {
		nodes[s].dist = 0;
		sort(all(eds), [](Ed a, Ed b) { return a.s() < b.s(); });

		int lim = sz(nodes) / 2 + 2; // /3+100 with shuffled vertices
		rep(i,lim) for (Ed ed : eds) {
			Node cur = nodes[ed.a], &dest = nodes[ed.b];
			if (abs(cur.dist) == inf) continue;
			ll d = cur.dist + ed.w;
			if (d < dest.dist) {
				dest.prev = ed.a;
				dest.dist = (i < lim-1 ? d : -inf);
			}
		}
		rep(i,lim) for (Ed e : eds) {
			if (nodes[e.a].dist == -inf)
				nodes[e.b].dist = -inf;
		}
	}
};

mt19937_64 rng(2137);

#define rand __rand

ll rand(const ll l, const ll r) {
	return uniform_int_distribution<ll>(l, r)(rng);
}

void fail(const string reason) {
	cout << "Tests failed! Reason: " << reason << endl;
	exit(1);
}

ll random_graph(const int n, const int m, const ll min_w, const ll max_w) {
	vector<Edge> ujlib_edges;
	vector<KACTL::Ed> kactl_edges;
	rep(_, m) {
		int v = int(rand(0, n - 1));
		int u = int(rand(0, n - 1));
		ll w = rand(min_w, max_w);
		ujlib_edges.push_back({v, u, w});
		kactl_edges.push_back({v, u, int(w)});
	}
	int s = int(rand(0, n - 1));
	BF bellman(ujlib_edges, n, s);
	vector<KACTL::Node> nodes(n);
	KACTL::bellmanFord(nodes, kactl_edges, s);
	rep(i, n) {
		if (nodes[i].dist != bellman[i]) {
			fail("wrong distances calculated");
		}
	}
	ll min_dist = *min_element(all(bellman));
	if (min_dist == -INF) {
		ll cycle_weight = 0;
		rep(j, sz(bellman.cyc)) {
			int v = bellman.cyc[j];
			int u = bellman.cyc[(j + 1) % sz(bellman.cyc)];
			ll w = INF;
			for (auto [V, U, W] : ujlib_edges) {
				if (V == v && U == u) {
					w = min(w, W);
				}
			}
			if (w == INF) {
				fail("cycle doesn't exist");
			}
			cycle_weight += w;
		}
		if (cycle_weight >= 0) {
			fail("cycle is not negative");
		}
	}
	return min_dist;
}

void random_graph_testset(const string testset_name, const int minN, const int maxN, const int minM, const int maxM, const ll minW, const ll maxW, const int IT) {
	rep(it, IT) {
		int negative_cycles = 0, tests = 0;
		fwd(n, minN, maxN + 1) {
			fwd(m, minM, maxM + 1) {
				if (random_graph(n, m, minW, maxW) < 0) {
					negative_cycles += 1;
				}
				tests += 1;
			}
		}
		cout << testset_name << " test pack #" << it + 1 << "/" << IT << " passed! with " << negative_cycles << "/" << tests << " tests having negative cycles!\n";
	}
	cout << testset_name << " tests passed!\n";
}

void stress_tests() {
	random_graph_testset("Tiny", 1, 10, 0, 100, -10, 100, 100);
	cout << "Tests passed!" << endl;
}

int main() {
	stress_tests();
	return 0;
}