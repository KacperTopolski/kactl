#include "../utilities/template.h"
#include "../../content/graph/Shapes.h"

namespace UW { // RIP if UW Triangles doesn't work :')
	#define LL ll
	#define REP rep
	struct Triangles {
	int triangles3 = 0;
	LL stars3 = 0, paths3 = 0;
	LL ps4 = 0, rectangles4 = 0, paths4 = 0;
	__int128_t ys4 = 0, stars4 = 0;
	Triangles(vector<vector<int>> &graph) {
		int n = ssize(graph);
		vector<pair<int, int>> sorted_deg(n);
		REP(i, n)
			sorted_deg[i] = {ssize(graph[i]), i};
		sort(sorted_deg.begin(), sorted_deg.end());
		vector<int> id(n);
		REP(i, n)
			id[sorted_deg[i].second] = i;
		vector<int> cnt(n);
		REP(v, n) {
			for(int u : graph[v]) if(id[v] > id[u])
				cnt[u] = 1;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u]) if(id[w] > id[u] and cnt[w]) {
				++triangles3;
				for(int x : {v, u, w})
					ps4 += ssize(graph[x]) - 2;
			}
			for(int u : graph[v]) if(id[v] > id[u])
				cnt[u] = 0;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u]) if(id[v] > id[w])
				rectangles4 += cnt[w]++;
			for(int u : graph[v]) if(id[v] > id[u]) for(int w : graph[u])
				cnt[w] = 0;
		}
		paths3 = -3 * triangles3;
		REP(v, n) for(int u : graph[v]) if(v < u)
			paths3 += (ssize(graph[v]) - 1) * LL(ssize(graph[u]) - 1);
		ys4 = -2 * ps4;
		auto choose2 = [&](int x) { return x * LL(x - 1) / 2; };
		REP(v, n) for(int u : graph[v])
			ys4 += (ssize(graph[v]) - 1) * choose2(ssize(graph[u]) - 1);
		paths4 = -(4 * rectangles4 + 2 * ps4 + 3 * triangles3);
		REP(v, n) {
			int x = 0;
			for(int u : graph[v]) {
				x += ssize(graph[u]) - 1;
				paths4 -= choose2(ssize(graph[u]) - 1);
			}
			paths4 += choose2(x);
		}
		REP(v, n) {
			int s = ssize(graph[v]);
			stars3 += s * LL(s - 1) * LL(s - 2);
			stars4 += s * LL(s - 1) * LL(s - 2) * LL(s - 3);
		}
		stars3 /= 6;
		stars4 /= 24;
	}
};
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

void random_graph(const int n, const int m) {
	vector<vi> g(n);
	set<pii> e;
	while (sz(e) != m) {
		int v = int(rand(0, n - 1));
		int u = int(rand(0, n - 1));
		if (v == u) continue;
		if (v > u) swap(v, u);
		if (e.find({v, u}) != end(e)) continue;
		e.insert({v, u});
		g[v].push_back(u);
		g[u].push_back(v);
	}
	UW::Triangles tri(g);
	Shapes shp(g);
	if (shp.tri != tri.triangles3) {
		fail("number of triangles differs");
	}
	if (shp.rect != tri.rectangles4) {
		fail("number of rectangles differs");
	}
	if (shp.path3 != tri.paths3) {
		fail("number of paths of length 3 differs");
	}
	if (shp.path4 != tri.paths4) {
		fail("number of paths of length4 differs");
	}
	if (shp.star3 != tri.stars3) {
		fail("number of stars with 3 neighbors differs");
	}
	if (shp.star4 != tri.stars4) {
		fail("number of stars with 4 neighbors differs");
	}
	if (shp.p != tri.ps4) {
		fail("number of P-shapes differs");
	}
	if (shp.y != tri.ys4) {
		fail("number of Y-shapes differs");
	}
}

void random_graph_testset(const string testset_name, const int minN, const int maxN, const int IT) {
	rep(it, IT) {
		fwd(n, minN, maxN + 1) {
			fwd(m, 0, n * (n - 1) / 2) {
				random_graph(n, m);
			}
		}
		cout << testset_name << " test pack #" << it + 1 << "/" << IT << " passed!\n";
	}
	cout << testset_name << " tests passed!\n";
}

void stress_tests() {
	random_graph_testset("Tiny", 1, 10, 100);
	//random_large_graph_testset("Medium", 1, 1000, 0, 500 * 1000);
	//random_large_graph_testset("Large", 1, 10 * 1000, 0, 500 * 1000);
	//random_large_graph_testset("Huge", 1, 100 * 1000, 0, 500 * 1000);
	cout << "Tests passed!" << endl;
}

int main() {
	stress_tests();
	return 0;
}