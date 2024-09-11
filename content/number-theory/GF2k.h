/**
 * Author: Kacper Topolski
 * Date: 2024-09-
 * License: CC0
 * Source: floklore
 * Description: Galois field of size 2^k.
 * Status: Stress-tested
 */
#pragma once

template <typename T, T poly>
struct GF {
	T x = 0;
	GF operator+(GF o) { return {x ^ o.x}; }
	GF operator-(GF o) { return {x ^ o.x}; }
	GF operator*(GF o) {
		T r = 0;
		for (int i = k() - 1; i >= 0; --i) {
			r = T(r & bit(k() - 1) ? (r << 1) ^ poly : r << 1);
			if (x & bit(i)) r ^= o.x;
		}
		return {r};
	}
	GF operator/(GF o) { return *this * o.inv(); }
	GF pow(T e) {
		GF r{1}, b{x};
		while (e) {
			if (e & 1)
				r = r * b;
			b = b * b;
			e /= 2;
		}
		return r;
	}
	GF inv() { return pow(T(-2)); }
	static int k() { return 8 * sizeof(T); }
	static T bit(int i) { return T(1) << i; }
};

using GF2_8 = GF<unsigned char, 27>;
using GF2_16 = GF<unsigned short, 4107>;
using GF2_32 = GF<unsigned, 27>;
using GF2_64 = GF<unsigned long long, 27>;
