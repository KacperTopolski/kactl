#include "../utilities/template.h"

using edges = vector<pair<int, ll>>;
#include "../../content/graph/CycleGCD.h"

namespace druzyna {
#define int long long
#undef sz
#define sz(x) ll(x.size())
int g = 0;

const int MAXN = 5005;
typedef bitset<MAXN> B;

vector<pii> G[MAXN];
int depth[MAXN];
bool vis[MAXN];
B dzieci[MAXN];
int LCA[MAXN][MAXN];
set<pair<pii, int>> poz;

void dfs(int x, int dpth, int p = -1) {
	depth[x] = dpth;
	dzieci[x][x] = true;
	vis[x] = true;
	LCA[x][x] = x;
	for (auto [y, c] : G[x])
		if (y != p) {
			if (vis[y]) {
				pii T = minmax<int>({x, y});
				poz.insert({T, c});
			} else {
				dfs(y, dpth + c, x);

				for (int i = dzieci[x]._Find_first(); i < MAXN - 1; i = dzieci[x]._Find_next(i))
					for (int j = dzieci[y]._Find_first(); j < MAXN - 1; j = dzieci[y]._Find_next(j))
						LCA[i][j] = LCA[j][i] = x;
				dzieci[x] |= dzieci[y];
			}
		}
}

pii norm(pii a) {
	if (depth[a.st] > depth[a.nd])
		return {a.nd, a.st};
	return {a.st, a.nd};
}

int lca(int a, int b) { return LCA[a][b]; }

void jazda(pair<pii, int> a, pair<pii, int> b) {
	auto [a1, a2] = a.st;
	auto [b1, b2] = b.st;
	if (dzieci[a1][b1] and dzieci[b1][a2]) {
		int T = b.nd + a.nd + abs(depth[a1] - depth[b1]) + abs(depth[b2] + depth[a2] - 2 * depth[lca(a2, b2)]);
		g = gcd(T, g);
	}
}

void jazda(pair<pii, int> a) {
	auto [a1, a2] = a.st;
	int T = a.nd + abs(depth[a1] - depth[a2]);

	g = gcd(T, g);
}

int sol(const vector<edges> &ed) {
	int n = sz(ed);
	assert(n);
	rep(i, n) {
		g = 0;
		G[i].clear();
		depth[i] = 0;
		vis[i] = 0;
		dzieci[i].reset();
		rep(j, n)
			LCA[i][j] = 0;
		poz.clear();
	}
	rep(i, n) {
		for (auto [j, w] : ed[i])
			G[i].eb(j, w);
	}
	rep(i, n) if (!vis[i]) { dfs(i, 0); }

	vector<pair<pii, int>> nied(all(poz));
	for (auto &p : nied)
		p.st = norm(p.st);
	for (auto p : nied)
		jazda(p);
	rep(i, sz(nied)) rep(j, sz(nied)) if (i > j) {
		jazda(nied[i], nied[j]);
		jazda(nied[j], nied[i]);
	}
	return g;
}
#undef int
}

vector<edges> generate(int seed, bool print_pafos = false) {
	mt19937_64 rnd(seed);
	int n = uniform_int_distribution(4, 5)(rnd);
	int m = uniform_int_distribution(n, n+2)(rnd);
	m = min(m, n*(n-1)/2);

	map<pii, ll> e;
	while (sz(e) < m) {
		int a = uniform_int_distribution(0, n-1)(rnd);
		int b = uniform_int_distribution(0, n-1)(rnd);
		int w = uniform_int_distribution(1, 50)(rnd);
		if (a > b) swap(a, b);
		if (a == b) continue;
		e[{a, b}] = w;
	}
	vector<pair<pii, ll>> evec(all(e));
	shuffle(all(evec), rnd);

	if (print_pafos)
		cerr << n << ' ' << m << '\n';

	vector<edges> g(n);
	for (auto [ab, w] : evec) {
		auto [a, b] = ab;
		g[a].eb(b, w);
		g[b].eb(a, w);
		if (print_pafos)
			cerr << a+1 << ' ' << b+1 << ' ' << w << '\n';
	}
	return g;
}

int main() {
	rep(seed, 1e6) {
		seed = 93715;
		auto G = generate(seed);
		auto g1 = CycleGCD(G).MOD;
		auto g2 = druzyna::sol(G);

		if (seed == 31575)
			deb(G);

		if (g1 != g2) {
			deb(seed, g1, g2);
			rep(i, sz(G))
				deb(i, G[i]);
			generate(seed, true);
			assert(false);
		}
		// if (g1 > 1)
		// 	deb("oktest", seed, sz(G), g1);
	}
	cout<<"Tests passed!"<<endl;
}
