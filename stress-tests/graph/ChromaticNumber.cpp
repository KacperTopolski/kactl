#include "../utilities/template.h"

#include "../../content/graph/ChromaticNumber.h"

namespace ChromaticBrute {
int brute(vi g) { // g[i] is a mask of neighbours
	const int n = sz(g);
	if (!n) return 0;
	vi dp(1 << n, 1);

	rep(msk, sz(dp)) {
		rep(i, n) if (((1 << i) & msk) && (g[i] & msk))
			dp[msk] = 420;
		for (int s = msk; s; s = (s-1) & msk)
			dp[msk] = min(dp[msk], dp[s] + dp[msk ^ s]);
	}

	return dp.back();
}
}

void check(vi g) {
	int br = ChromaticBrute::brute(g);
	int cp = chromaticNumber(g);

	if (br != cp) {
		deb(g, br, cp);
		assert(false);
	}
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
	fwd(n, 0, 15) {
		rep(seed, n < 10 ? 200 : 3)
			check_sz(n, seed);
	}

	assert(chromaticNumber({6, 5, 3}) == 3);

	cout<<"Tests passed!"<<endl;
}
