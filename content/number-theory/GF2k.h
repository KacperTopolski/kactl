/**
 * Author: Kacper Topolski
 * Date: 2024-09-
 * License: CC0
 * Source: floklore
 * Description: Galois field of size 2^k for k = 8, 16, 32, 64 and 128.
 * Status: Stress-tested
 */
#pragma once

template <typename T>
struct GF {
	T x = 0;
	GF operator+(GF o) { return {x ^ o.x}; }
	GF operator-(GF o) { return {x ^ o.x}; }
	GF operator*(GF o) {
		T r = 0;
		const int k = 8 * sizeof(T) - 1;
		for (int i = k; i >= 0; --i) {
			r = T(r >> k & 1 ? r << 1 ^ 30941 : r << 1);
			if (x >> i & 1) r ^= o.x;
		}
		return {r};
	}
	GF operator/(GF o) { return *this * o.inv(); }
	GF inv() {
		GF r{1}, b{x};
		for (T e = -2; e; e /= 2, b = b * b) if (e & 1)
			r = r * b;
		return r;
	}
};

using GF2_8 = GF<unsigned char>;
using GF2_16 = GF<unsigned short>;
using GF2_32 = GF<unsigned>;
using GF2_64 = GF<unsigned long long>;
using GF2_128 = GF<__uint128_t>;
