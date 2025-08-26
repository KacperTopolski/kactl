/**
 *
 * Author: Krzysztof Potępa
 * Description: Poynomials. Implement Zp.
 * Time: see below
 */
#pragma once

#include "../number-theory/ModularArithmetic.h" 					/// exclude-line
using Zp = Mod;														/// exclude-line

using Poly = vector<Zp>; // Zp should have .x member and implicit constructor

#include "../number-theory/ModSqrt.h" // sqrt only

void norm(Poly &P) {
	while (!P.empty() && !P.back().x)
		P.pop_back();
}

// Evaluate polynomial at x; time: O(n)
Zp eval(const Poly &P, Zp x) {
	Zp n = 0, y = 1;
	for (auto &a : P) n += a * y, y *= x;
	return n;
}

Poly &operator+=(Poly &l, const Poly &r) {
	l.resize(max(sz(l), sz(r)));
	rep(i, sz(r)) l[i] += r[i];
	norm(l);
	return l;
}
Poly operator+(Poly l, const Poly &r) { return l += r; }

Poly &operator-=(Poly &l, const Poly &r) {
	l.resize(max(sz(l), sz(r)));
	rep(i, sz(r)) l[i] -= r[i];
	norm(l);
	return l;
}
Poly operator-(Poly l, const Poly &r) { return l -= r; }

Poly &operator*=(Poly &l, const Poly &r) {
	if (min(sz(l), sz(r)) < 50) {
		// Naive multiplication
		Poly p(sz(l) + sz(r));
		rep(i, sz(l)) rep(j, sz(r)) p[i + j] += l[i] * r[j];
		l.swap(p);
	} else { /* FFT multiplication*/ }
	norm(l);
	return l;
}
Poly operator*(Poly l, const Poly &r) { return l *= r; }

// Compute inverse series mod x^n; O(n lg n) Requires P(0) != 0.
Poly invert(const Poly &P, int n) {
	assert(!P.empty() && P[0].x);
	Poly tmp{P[0]}, ret = {P[0].inv()};
	for (int i = 1; i < n; i *= 2) {
		fwd(j, i, min(i * 2, sz(P))) tmp.pb(P[j]);
		(ret *= Poly{2} - tmp * ret).resize(i * 2);
	}
	ret.resize(n);
	return ret;
}

// Floor division by polynomial; O(n lg n)
Poly &operator/=(Poly &l, Poly r) {
	norm(l);
	norm(r);
	int d = sz(l) - sz(r) + 1;
	if (d <= 0)
		return l.clear(), l;
	reverse(all(l));
	reverse(all(r));
	l.resize(d);
	l *= invert(r, d);
	l.resize(d);
	reverse(all(l));
	return l;
}
Poly operator/(Poly l, const Poly &r) { return l /= r; }

// Remainder modulo a polynomial; O(n lg n)
Poly operator%(const Poly &l, const Poly &r) { return l - r * (l / r); }
Poly &operator%=(Poly &l, const Poly &r) { return l -= r * (l / r); }

// Compute a^e mod x^n, where a is polynomial;
// time: O(n log n log e)
Poly pow(Poly a, ll e, int n) {
	Poly t = {1};
	while (e) {
		if (e % 2)
			(t *= a).resize(n);
		e /= 2;
		(a *= a).resize(n);
	}
	norm(t);
	return t;
}

// Compute a^e mod m, where a and m are
// polynomials; time: O(|m| log |m| log e)
Poly pow(Poly a, ll e, const Poly &m) {
	Poly t = {1};
	while (e) {
		if (e % 2)
			t = t * a % m;
		e /= 2;
		a = a * a % m;
	}
	return t;
}

Poly derivate(Poly P) {
	if (!P.empty()) {
		fwd(i, 1, sz(P)) P[i - 1] = P[i] * i;
		P.pop_back();
	}
	return P;
}

Poly integrate(Poly P) {
	if (!P.empty()) {
		P.pb(0);
		for (int i = sz(P); --i;)
			P[i] = P[i - 1] / i;
		P[0] = 0;
	}
	return P;
}

// Compute ln(P) mod x^n; time: O(n log n)
Poly log(const Poly &P, int n) {
	Poly a = integrate(derivate(P) * invert(P, n));
	a.resize(n);
	return a;
}

// Compute exp(P) mod x^n; time: O(n lg n)  Requires P(0) = 0.
Poly exp(Poly P, int n) {
	assert(P.empty() || !P[0].x);
	Poly tmp{P[0] + 1}, ret = {1};
	for (int i = 1; i < n; i *= 2) {
		fwd(j, i, min(i * 2, sz(P))) tmp.pb(P[j]);
		(ret *= (tmp - log(ret, i * 2))).resize(i * 2);
	}
	ret.resize(n);
	return ret;
}

// Compute sqrt(P) mod x^n; Requiers ModSqrt.h time: O(n log n)
bool sqrt(Poly &P, int n) {
	norm(P);
	if (P.empty())
		return P.resize(n), 1;

	int tail = 0;
	while (!P[tail].x)
		tail++;
	if (tail % 2)
		return 0;

	ll sq = modSqrt(P[tail].x, mod);
	if (sq == -1)
		return 0;

	Poly tmp{P[tail]}, ret = {sq};
	for (int i = 1; i < n - tail / 2; i *= 2) {
		fwd(j, i, min(i * 2, sz(P) - tail)) tmp.pb(P[tail + j]);
		(ret += tmp * invert(ret, i * 2)).resize(i * 2);
		for (auto &e : ret) e /= 2;
	}

	P.resize(tail / 2);
	P.insert(P.end(), all(ret));
	P.resize(n);
	return 1;
}

// Compute polynomial P(x+c); time: O(n lg n)
Poly shift(Poly P, Zp c) {
	int n = sz(P);
	Poly Q(n, 1);
	Zp fac = 1;
	fwd(i, 1, n) {
		P[i] *= (fac *= i);
		Q[n - i - 1] = Q[n - i] * c / i;
	}
	P *= Q;
	if (sz(P) < n)
		return {};
	P.erase(P.begin(), P.begin() + n - 1);
	fac = 1;
	fwd(i, 1, n) P[i] /= (fac *= i);
	return P;
}

// Compute values P(x^0), ..., P(x^{n-1}); time: O(n lg n)
Poly chirpz(Poly P, Zp x, int n) {
	int k = sz(P);
	Poly Q(n + k);
	rep(i, n + k) Q[i] = x.pow(i * (i - 1) / 2);
	rep(i, k) P[i] /= Q[i];
	reverse(all(P));
	P *= Q;
	rep(i, n) P[i] = P[k + i - 1] / Q[i];
	P.resize(n);
	return P;
}

// Evaluate polynomial P in given points; time: O(n lg^2 n)
Poly eval(const Poly &P, Poly points) {
	int len = 1;
	while (len < sz(points))
		len *= 2;

	vector<Poly> tree(len * 2, {1});
	rep(i, sz(points)) tree[len + i] = {-points[i], 1};

	for (int i = len; --i;)
		tree[i] = tree[i * 2] * tree[i * 2 + 1];

	tree[0] = P;
	fwd(i, 1, len * 2) tree[i] = tree[i / 2] % tree[i];

	rep(i, sz(points)) {
		auto &vec = tree[len + i];
		points[i] = vec.empty() ? 0 : vec[0];
	}
	return points;
}

// Given n points (x, f(x)) compute n-1-degree polynomial f that
// passes through them; time: O(n lg^2 n)
Poly interpolate(const vector<pair<Zp, Zp>> &P) {
	int len = 1;
	while (len < sz(P))
		len *= 2;

	vector<Poly> mult(len * 2, {1}), tree(len * 2);
	rep(i, sz(P)) mult[len + i] = {-P[i].st, 1};

	for (int i = len; --i;)
		mult[i] = mult[i * 2] * mult[i * 2 + 1];

	tree[0] = derivate(mult[1]);
	fwd(i, 1, len * 2) tree[i] = tree[i / 2] % mult[i];

	rep(i, sz(P)) tree[len + i][0] = P[i].nd / tree[len + i][0];

	for (int i = len; --i;)
		tree[i] = tree[i * 2] * mult[i * 2 + 1] + mult[i * 2] * tree[i * 2 + 1];
	return tree[1];
}


// Count number of possible subsets that sum
// to t for each t = 1, ..., n; O(n log n)
// Input elements are given by frequency array,
// i.e. counts[x] = how many times elements x
// is contained in the multiset.
// Requires counts[0] == 0.
//! Source: https://arxiv.org/pdf/1807.11597.pdf
Poly subsetSum(Poly counts, int n) {
	assert(counts[0].x == 0);
	Poly mul(n);
	rep(i, n)
		mul[i] = Zp(i).inv() * (i%2 ? 1 : -1);
	counts.resize(n);
	for (int i = n-2; i > 0; i--)
		for (int j = 2; i*j < n; j++)
			counts[i*j] += mul[j] * counts[i];
	return exp(counts, n);
}
