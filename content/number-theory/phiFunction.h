/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: Inclusive prefix sums of \emph{Euler's $\phi$}. For $\text{MOD} > 4\cdot 10^9$, answer will overflow.
 * Time:  O(n^{2/3})
 * Status: Stress tested
 */
#pragma once

constexpr int MOD = 998244353;

vector<ll> pSum; // [k] = phi sum from 0 to k
void calcPhiSum() {
	pSum.resize(1e7 + 7);
	iota(all(pSum), 0);
	fwd(i, 2, sz(pSum)) {
		if (pSum[i] == i) for (int j = i; j < sz(pSum); j += i) pSum[j] = pSum[j] / i * (i - 1);
		pSum[i] = (pSum[i] + pSum[i-1]) % MOD;
	}
}

ll getPhiSum(ll n) { // phi(0) + ... + phi(n)
	static unordered_map<ll, ll> big;
	if (!sz(pSum))
		calcPhiSum();
	if (n < sz(pSum))
		return pSum[n];
	if (big.count(n))
		return big[n];
	ll ret = (n % 2 ? n % MOD * ((n + 1) / 2 % MOD) : n / 2 % MOD * (n % MOD + 1)) % MOD;
	for (ll s, i = 2; i <= n; i = s + 1) {
		s = n / (n / i);
		ret -= (s - i + 1) % MOD * getPhiSum(n / i) % MOD;
	}
	return big[n] = (ret % MOD + MOD) % MOD;
}
