#pragma once
#include "NumberTheoreticTransform.h"

/**
 * Author: teapotd
 * License: N / A
 * Description: Online convolution helper. Ensures that: out[m] = sum { f(i)*g(m-i) : 1 <= i <= m-1 }
 * Time: O(N \log^2 N)
 * Status: compiles
 */

void onlineConv(vector<ll>& out, int m, auto f, auto g) {
	int len = m & ~(m-1), b = m-len;
	int e = min(m+len, sz(out));
	auto apply = [&](auto r, auto s) {
		vector<ll> P(m-b+1), Q(min(e-b, m));
		fwd(i, max(b, 1), m) P[i-b] = r(i);
		fwd(i, 1, sz(Q)) Q[i] = s(i);
		P = conv(P, Q);
		fwd(i, m, e) (out[i] += P[i-b]) %= mod;
	}; // ^ optimize this % to if statement
	apply(f, g);
	if (b) apply(g, f);
}

// h[m] = 1 + sum h(i)*i * h(m-i)/(m-i)
auto example(int n) {
	vector<ll> h(n);
	for (int m = 1; m < n; m++) {
		onlineConv(h, m,
			[&](int i) { return h[i] * i % mod; },
			[&](int i) { return h[i] * modpow(i, mod-2) % mod; });
		(h[m] += 1) %= mod;
	} return h; }
