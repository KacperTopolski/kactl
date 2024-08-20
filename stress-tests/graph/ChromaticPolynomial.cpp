#include "../utilities/template.h"
// https://github.com/ShahjalalShohag/code-library/blob/main/Graph%20Theory/Chromatic%20Polynoimial.cpp

namespace ChromaticPolyBrute {
vi brutePoly(vi g) {
	const int n = sz(g);
	vi ways(n + 1);
	fwd(cols, 1, n+1) {
		vi col(n, -1);
		auto rec = [&](int i, auto _rec) {
			if (i == n) {
				++ways[cols];
				return;
			}
			for (col[i] = 0; col[i] < cols; ++col[i]) {
				bool ok = true;
				rep(j, i) if ((g[i] & (1 << j)) && col[j] == col[i])
					ok = false;
				if (ok)
					_rec(i+1, _rec);
			}
		};
		rec(0, rec);
	}
	return ways;
}
}

void check(vi g) {

}

void check_sz(int n, int seed) {
	mt19937 rnd(seed);
	vector<pii> e;
	rep(i, n) rep(j, i) e.eb(i, j);
	shuffle(all(e), rnd);

	vi g(n);
	check(g);
	for (auto [a, b] : e) {
		g[a] |= 1 << b;
		g[b] |= 1 << a;
		check(g);
	}
}

int main() {
	fwd(n, 0, 5) {
		rep(seed, n < 10 ? 200 : 3)
			check_sz(n, seed);
	}

	cout<<"Tests passed!"<<endl;
}
