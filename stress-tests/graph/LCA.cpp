#include "../utilities/template.h"

#include "../../content/graph/LCA.h"

namespace KACTL {
	template<class T>
	struct KACTL_RMQ {
		vector<vector<T>> jmp;KACTL_RMQ() {}
		KACTL_RMQ(const vector<T>& V) : jmp(1, V) {
			for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
				jmp.emplace_back(sz(V) - pw * 2 + 1);
				rep(j,sz(jmp[k]))
					jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
			}
		}
		T query(int a, int b) {
			assert(a < b); // or return inf if a == b
			int dep = 31 - __builtin_clz(b - a);
			return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
		}
	};
	struct LCA {
		int T = 0;
		vi time, path, ret;
		KACTL_RMQ<int> rmq;

		LCA(vector<vi>& C) : time(sz(C)) {
			if (sz(C) == 0) return;
			dfs(C,0,-1);
			rmq = KACTL_RMQ<int>(ret);
		}
		void dfs(vector<vi>& C, int v, int par) {
			time[v] = T++;
			for (int y : C[v]) if (y != par) {
				path.push_back(v), ret.push_back(time[v]);
				dfs(C, y, v);
			}
		}

		int lca(int a, int b) {
			if (a == b) return a;
			tie(a, b) = minmax(time[a], time[b]);
			return path[rmq.query(a, b)];
		}
		//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
	};

	typedef vector<pair<int, int>> vpi;
	vpi compressTree(LCA& lca, const vi& subset) {
		if (sz(subset) == 0) return {};
		static vi rev; rev.resize(sz(lca.time));
		vi li = subset, &T = lca.time;
		auto cmp = [&](int a, int b) { return T[a] < T[b]; };
		sort(all(li), cmp);
		int m = sz(li)-1;
		rep(i,m) {
			int a = li[i], b = li[i+1];
			li.push_back(lca.lca(a, b));
		}
		sort(all(li), cmp);
		li.erase(unique(all(li)), li.end());
		rep(i,sz(li)) rev[li[i]] = i;
		vpi ret = {pii(0, li[0])};
		rep(i,sz(li)-1) {
			int a = li[i], b = li[i+1];
			ret.emplace_back(rev[lca.lca(a, b)], b);
		}
		return ret;
	}
};

mt19937 rng(2137);

int rnd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

vi dfs(vector<vi> &g, vector<vi> &naive, int v, int p) {
	vi a = {v};
	naive[v][v] = v;
	for (auto u : g[v])
		if (u != p) {
			vi s = dfs(g, naive, u, v);
			for (auto x : s) for (auto y : a)
				naive[x][y] = naive[y][x] = v;
			a.insert(end(a), all(s));
		}
	return a;
}

void test_nq(int n, int q) {
	vector<pii> e;
	fwd(i, 1, n) e.eb(i, rnd(0, i - 1));
	vi id(n);
	iota(all(id), 0);
	shuffle(all(id), rng);
	for (auto &[v, u] : e) {
		v = id[v];
		u = id[u];
		if (rnd(0, 1)) swap(v, u);
	}
	vector<vi> g(n);
	for (auto [v, u] : e) {
		g[v].pb(u);
		g[u].pb(v);
	}
	LCA lca(g);
	KACTL::LCA kactl_lca(g);
	vector<vi> naive(n, vi(n, -1));
	dfs(g, naive, 0, -1);
	rep(i, n) rep(j, n) {
		int ujlib = lca.lca(i, j);
		assert(ujlib == naive[i][j]);
	}
	int k = min(n, 7);
	rep(m, (1 << k)) {
		vi ss;
		rep(i, k) if (m & (1 << i))
			ss.pb(i);
		vector<pii> ujlib = lca.compress(ss);
		vector<pii> kactl = KACTL::compressTree(kactl_lca, ss);
		sort(all(ujlib));
		sort(all(kactl));
		assert(ujlib == kactl);
	}
	rep(i, q) {
		int siz = rnd(0, n);
		vi zo(n);
		rep(j, siz) zo[j] = 1;
		shuffle(all(zo), rng);
		vi ss;
		rep(j, n) if (zo[j]) ss.pb(j);
		vector<pii> ujlib = lca.compress(ss);
		vector<pii> kactl = KACTL::compressTree(kactl_lca, ss);
		sort(all(ujlib));
		sort(all(kactl));
		assert(ujlib == kactl);
	}
}

int main() {
	const int IT = 100;
	const int MAXN = 50;
	const int MINQ = 20;
	rep(i, IT) {
		fwd(N, 1, MAXN + 1) {
			fwd(Q, MINQ, max(MINQ, 5 * N + 1) + 1) {
				test_nq(N, Q);
			}
			cout << "checkpoint for N = " << N << '\n';
		}
		cout << "testset #" << i + 1 / IT << " passed!\n";
	}
	cout<<"Tests passed!"<<endl;
}
