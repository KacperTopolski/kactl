/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N / A
 * Description: RMQ on intervals [l, r]. Second one has 2-3x less memory and is 2-3x faster Size of array CANNOT be zero.
 * Status: stress-tested
 */
#pragma once
template<class T>
struct RMQF {
	static constexpr int B = 32; // not larger!
	RMQ<T> s;
	vector<uint32_t> m;
	vector<T> a, c; RMQF(){} // only if needed
	RMQF(vector<T>& A) : m(sz(A)), a(A), c(sz(A)) {
		vector<T> b(sz(a) / B + 1);
		uint32_t mi = 0;
		rep(i, sz(a)) {
			b[i / B] = (i % B ? min(b[i / B], a[i]) : a[i]);
			mi <<= 1;
			while (mi && a[i] < a[i - __builtin_ctz(mi)])
				mi ^= (1u << __builtin_ctz(mi));
			m[i] = mi ^= 1; c[i] = a[i - __lg(m[i])];
		}
		s = RMQ(b);
	}
	T get(int l, int r) {
		if (r - l + 1 < B)
			return a[r - __lg(m[r] & ((1u << (r - l + 1)) - 1))];
		T k = min(c[r], c[l + B - 1]);
		l = (l + B - 1) / B, r = r / B - 1;
		if (l <= r) k = min(k, s.get(l, r));
		return k; } };