#include "PolynomialPotepa.h"
#pragma once

/**
 * Author: Krzysztof Potępa
 * Description: Compute k-th term of an n-order linear
 * recurrence C[i] = sum C[i-j-1]*D[j], given C[0..n-1] and D[0..n-1];
 * Time: O(n \log n \log k)
 */
Zp linearRec(const Poly &C, const Poly &D, ll k) {
	Poly f(sz(D) + 1, 1);
	rep(i, sz(D)) f[i] = -D[sz(D) - i - 1];
	f = pow({0, 1}, k, f);
	Zp ret = 0;
	rep(i, sz(f)) ret += f[i] * C[i];
	return ret;
}
