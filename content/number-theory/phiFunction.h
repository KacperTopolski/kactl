/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: \emph{Euler's $\phi$} function is defined as $\phi(n):=\#$ of positive integers $\leq n$ that are coprime with $n$.
 * $\phi(1)=1$, $p$ prime $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$, $m,n$ coprime $\Rightarrow \phi(mn)=\phi(m)\phi(n)$.
 * If $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$ then $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$.
 * $\phi(n)=n \cdot \prod_{p|n}(1-1/p)$.
 *
 * $\sum_{d|n} \phi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$
 *
 * \textbf{Euler's thm}: $a,n$ coprime $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$.
 *
 * \textbf{Fermat's little thm}: $p$ prime $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$.
 * Time:  O(n^{2/3})
 * Status: Tested
 */
#pragma once

constexpr int MOD = 998244353;

vi phi(1e7 + 1);

void calcPhi() {
	iota(all(phi), 0);
	fwd(i, 2, sz(phi)) if (phi[i] == i) for (int j = i; j < sz(phi); j += i) phi[j] = phi[j] / i * (i - 1);
}

vector<ll> phiSum; // [k] = sum from 0 to k-1
void calcPhiSum() {
	calcPhi();
	phiSum.resize(sz(phi) + 1);
	rep(i, sz(phi)) phiSum[i + 1] = (phiSum[i] + phi[i]) % MOD;
}

// Get prefix sum of phi(0) + ... + phi(n-1).
// WARNING: Call calcPhiSum first! For MOD > 4*10^9, answer will overflow.
ll getPhiSum(ll n) {
	static unordered_map<ll, ll> big;
	if (n < sz(phiSum))
		return phiSum[n];
	if (big.count(--n))
		return big[n];

	ll ret = (n % 2 ? n % MOD * ((n + 1) / 2 % MOD) : n / 2 % MOD * (n % MOD + 1)) % MOD;

	for (ll s, i = 2; i <= n; i = s + 1) {
		s = n / (n / i);
		ret -= (s - i + 1) % MOD * getPhiSum(n / i + 1) % MOD;
	}

	return big[n] = ret = (ret % MOD + MOD) % MOD;
}
