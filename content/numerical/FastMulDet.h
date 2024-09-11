/**
 * Author: Kacper Topolski
 * Date: 2024-08-20
 * Source: https://sio2.mimuw.edu.pl/c/pa-2022-1/forum/187/36749/
 * Description: Given a matrix M, s.t. we can quickly compute f(v) = Mv for any vector v, computes det(M). Single iteration fails on identity matrix with probability around $n^2 / mod$. For small mod you can modify this to use a field extension.
 * Time: 4n calls to f
 * Status: Stress tested
 */
#pragma once

#include "BerlekampMassey.h"

mt19937_64 rnd{2137};
vector<ll> rndVec(int n) {
	vector<ll> r(n);
	rep(i, n) r[i] = rnd() % mod;
	return r;
}
ll dot(vector<ll> &a, vector<ll> &b) {
	ll r = 0;
	rep(i, sz(a)) r += a[i] * b[i] % mod;
	return r % mod;
}
void pointwise(vector<ll> &a, vector<ll> &b) {
	rep(i, sz(a)) a[i] = a[i] * b[i] % mod;
}
ll detOnce(int n, auto f) {
	auto v = rndVec(n), r = rndVec(n), a = rndVec(n);
	vector<ll> vals;
	rep(_, n*2) {
		pointwise(a, r);
		vals.pb(dot(v, a = f(a)));
	}
	auto ber = berlekampMassey(vals);
	if (sz(ber) != n) return 0;
	ll prod = 1;
	for (ll x : r) prod = prod * x % mod;
	int sg = n % 2 ? 1 : -1;
	return (mod + ber[n-1] * sg) * modpow(prod, mod-2) % mod;
}
ll det(int n, auto f) {
	return detOnce(n, f) ?: detOnce(n, f); }
