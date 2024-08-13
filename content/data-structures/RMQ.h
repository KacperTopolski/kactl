/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N / A
 * Description: RMQ on intervals [l, r]. Second one has linear memory and considerably faster preprocessing, but slower queries (preprocessing is usually the bottleneck). Size of array CANNOT be zero.
 * Status: stress-tested
 */
#pragma once
template<class T>
struct RMQ { // #define / undef min func for different merging
	vector<vector<T> > s; RMQ() {} // need for RMQF
	RMQ(vector<T>& a) : s(1, a) {
		rep(d, __lg(sz(a))) {
			s.eb(sz(a) - (1 << d) * 2 + 1);
			rep(j, sz(s[d + 1]))
				s[d + 1][j] = min(s[d][j], s[d][j + (1 << d)]);
		}
	}
	T get(int l, int r) {
		int d = __lg(r - l + 1);
		return min(s[d][l], s[d][r - (1 << d) + 1]);
	}
};
template<class T>
struct RMQF {
	static constexpr int B = 64; // not larger!
	RMQ<T> s;
	vector<uint64_t> m;
	vector<T> a;
	RMQF(vector<T>& A) : a(A) {
		m.resize(sz(a));
		vector<T> b(sz(a) / B + 1);
		uint64_t mi = 0;
		rep(i, sz(a)) {
			b[i / B] = (i % B ? min(b[i / B], a[i]) : a[i]);
			mi <<= 1;
			while (mi && a[i] < a[i - __builtin_ctzll(mi)])
				mi ^= (1ull << __builtin_ctzll(mi));
			m[i] = mi ^= 1;
		}
		s = RMQ(b);
	}
	T get(int l, int r) {
		if (r - l + 1 < B)
			return a[r - __lg(m[r] & ((1ull << (r - l + 1)) - 1))];
		T k = min(a[r - __lg(m[r])], a[l + B - 1 - __lg(m[l + B - 1])]);
		l = ((l + B - 1) / B), r = r / B - 1;
		if (l <= r) k = min(k, s.get(l, r));
		return k; } };