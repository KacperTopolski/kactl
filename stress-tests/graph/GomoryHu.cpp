#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GlobalMinCut.h"
#include "../../content/graph/Dinic.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#include "../../content/graph/GomoryHu.h"
#pragma GCC diagnostic pop

void test(int N, ll mxFlow, int iters) {
	static mt19937 rnd;
	rep(it,iters) {
		int n = int(rnd()%N+1);
		int m = int(rnd()%(N*N));
		vector<array<ll, 3>> edges;
		vector<vector<ll>> mat(n, vector<ll>(n));
		rep(ite,m) {
			int i = int(rnd() % n);
			int j = int(rnd() % n);
			if (i == j) continue;
			ll w = rnd() % mxFlow;
			edges.push_back({i, j, w});
			mat[i][j] += w;
			mat[j][i] += w;
		}
		auto calc = [&](int s, int t) {
			Dinic flow(n);
			for (auto e : edges) {
				flow.addEdge((int)e[0], (int)e[1], e[2], e[2]);
			}
			return flow.maxFlow(s, t);
		};
		vector<Edge> gomoryHuTree = gomoryHu(n, edges);
		vector<vector<array<ll, 2>>> adj(n);
		for (auto e : gomoryHuTree) {
			adj[e[0]].push_back({e[1], e[2]});
			adj[e[1]].push_back({e[0], e[2]});
		}
		auto dfs = make_y_combinator([&](auto f, int start, int cur, int p, ll mn) -> void {
			if (start != cur) {
				assert(mn == calc(start, cur));
			}
			for (auto i : adj[cur]) {
				if (i[0] != p)
					f(start, (int)i[0], cur, min(mn, i[1]));
			}
		});
		dfs(0, 0, -1, INF);

		// Check that the lightest edge agrees with GlobalMinCut.
		if (n >= 2) {
			ll minCut = INF;
			for (auto e : gomoryHuTree) {
				minCut = min(minCut, e[2]);
			}
			auto mat2 = mat;
			auto pa = globalMinCut(mat2);
			assert(pa.first == minCut);
			vi inCut(n);
			assert(sz(pa.second) != 0);
			assert(sz(pa.second) != n);
			for (int x : pa.second) {
				assert(0 <= x && x < n);
				assert(!inCut[x]);
				inCut[x] = 1;
			}
			ll cutw = 0;
			rep(i,n) rep(j,n) if (inCut[i] && !inCut[j]) {
				cutw += mat[i][j];
			}
			assert(pa.first == cutw);
		}
	}
}
int main() {
	test(25, 5, 200);
	test(100, 1000, 5);
	test(100, 1, 20);
	test(5, 5, 20000);

	const ll MX = 1e12;
	test(5, MX, 2000);
	test(25, MX, 200);
	test(125, MX, 20);

	cerr<<"todo https://github.com/kth-competitive-programming/kactl/issues/292"<<endl;
	cout<<"Tests passed!"<<endl;
}
