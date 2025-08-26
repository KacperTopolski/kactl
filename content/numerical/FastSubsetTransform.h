/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

const int mode_and = 0, mode_or = 1, mode_xor = 2;					/// exclude-line
int mode_global;													/// exclude-line

void FST(vi& a, bool inv) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) fwd(j,i,i+step) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				mode_global == mode_and ?							/// exclude-line
				inv ? pii(v - u, u) : pii(v, u + v)  // AND
				: mode_global == mode_or ?							/// exclude-line
				inv ? pii(v, u - v) : pii(u + v, u)  // OR
				:													/// exclude-line
				pii(u + v, u - v);                   // XOR
		}
	}
	if (mode_global == mode_xor)									/// exclude-line
	if (inv) for (int& x : a) x /= sz(a); 		// XOR only
}
vi conv(vi a, vi b) {
	FST(a, 0); FST(b, 0);
	rep(i,sz(a)) a[i] *= b[i];
	FST(a, 1); return a;
}

int subs(int msk, auto f) {
	int r = 0; for (int i = msk;; i = (i-1)&msk) {
		r += f(i); if (!i) break; } return r; }
int pw(int i) { return 1&__builtin_popcount(i)?-1:1; }
array<int, 6> singleST(vi& a, int x) {
	auto f = [&](int i){return sz(a)-1-i;};
	int tand,iand,tor,ior,txor=0,ixor;
	tand= subs(x, [&](int i){return a[f(i)];});
	iand= subs(f(x),[&](int i){return a[i]*pw(f(i^x));});
	tor = subs(f(x), [&](int i){return a[i];});
	ior = subs(x, [&](int i){return a[f(i)]*pw(i^x);});
	rep(i, sz(a)) txor += a[i] * pw(i&x);
	ixor = txor / sz(a);
	return {tand, iand, tor, ior, txor, ixor};
}
