#include "../utilities/template.h"

using dbl = double;

bool dbl_eq(dbl v, dbl ex) {
	return abs(v-ex) / max(dbl(1), abs(ex)) < 1e-6;
}

dbl INF = 1e9;

dbl bruted(vector<vector<dbl>> g) {
	int n = sz(g);

	dbl ans = INF;

	vi path(n);
	iota(all(path), 0);
	do {
		dbl len{};
		rep(id, n) {
			if (id) {
				dbl here = g[path[id-1]][path[id]];
				if (here >= INF) break;
				len += here;
			}
			dbl here = g[path[id]][path[0]];
			if (here >= INF) continue;

			dbl avg = (here + len) / (id + 1);
			ans = min(ans, avg);
		}
	} while (next_permutation(all(path)));

	return ans;
}

dbl karp(vector<vector<dbl>> g) {
	int n = sz(g);

	vector<vector<dbl>> h(n+1, vector<dbl>(n, INF));
	h[0].assign(n, 0);

	rep(p_layer, sz(h) - 1) {
		rep(i, n) rep(j, n) if (g[i][j] < INF) {
			h[p_layer+1][j] = min(h[p_layer+1][j], h[p_layer][i] + g[i][j]);
		}
	}

	vector<dbl> ans(n, -INF);

	rep(v, n) {
		rep(k, n) {
			dbl here = (h[n][v] - h[k][v]) / (n - k);
			ans[v] = max(ans[v], here);
		}
	}
	return *min_element(all(ans));
}

mt19937 rnd;
vector<vector<dbl>> generate(int n) {
	vector<vector<dbl>> g(n, vector<dbl>(n, INF));
	rep(i, n) rep(j, n) {
		// if (i == j) continue;
		if (rnd() & 1) continue;
		g[i][j] = dbl(rnd() % 100);
	}
	return g;
}

int main() {
	fwd(n, 1, 10) rep(_, 100) {
		auto g = generate(n);
		auto br = bruted(g);
		auto kar = karp(g);

		if (!dbl_eq(kar, br) && br < INF) {
			rep(i, n) deb(i, g[i]);
			deb(br);
			deb(kar);
			assert(false);
		}
	}
	cout<<"Tests passed!"<<endl;
}
