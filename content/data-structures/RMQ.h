/**
 * Author: Antoni Długosz
 * Date: 2024
 * License: N / A
 * Description: RMQ on intervals [l, r]. Second one has 2-3x less memory and is 2-3x faster Size of array CANNOT be zero.
 * Status: stress-tested
 */
#pragma once
template<class T>
struct RMQ { // #define / undef min func for different merging
	vector<vector<T> > s; RMQ(){} // only if needed
	RMQ(vector<T>& a) : s(1, a) {
		if (!sz(a)) return;
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