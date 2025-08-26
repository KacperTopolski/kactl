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
	GF operator+(GF o) { return {x ^ o.x}; }					/// exclude-line
	GF pow(T e) {												/// exclude-line
		GF r{1}, b{x};											/// exclude-line
		for (; e; e /= 2, b = b * b) if (e & 1)					/// exclude-line
			r = r * b;											/// exclude-line
		return r;												/// exclude-line
	}															/// exclude-line
	GF operator*(GF o) { // O(k)
		int k = 8 * sizeof(T) - 1; T r = 0;
		for (int i = k; i >= 0; --i) {
			r = T(r >> k & 1 ? r << 1 ^ 30941 : r << 1);
			if (x >> i & 1) r ^= o.x;
		} return {r}; }
	GF inv() {return pow(-2); }
	GF generator() {return {T(-19)}; } };
