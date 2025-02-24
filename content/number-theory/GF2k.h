/**
 * Author: Kacper Topolski
 * Date: 2024-09-
 * License: CC0
 * Source: folklore
 * Description: Galois field of size $2^k$ for k = 8, 16, 32, 64 and 128. Set T to unsigned type of appropriate width.
 * Status: Stress-tested
 */
#pragma once

template <typename T> struct GF {
	T x = 0;
	GF operator+(GF o) { return {x ^ o.x}; }
	GF operator*(GF o) { // O(k)
		T r = 0;
		const int k = 8 * sizeof(T) - 1;
		for (int i = k; i >= 0; --i) {
			r = T(r >> k & 1 ? r << 1 ^ 30941 : r << 1);
			if (x >> i & 1) r ^= o.x;
		}
		return {r};
	}
	GF inv() { // O(k^2)
		GF r{1}, b{x};
		for (T e = -2; e; e /= 2, b = b * b) if (e & 1)
			r = r * b;
		return r;
	} };
