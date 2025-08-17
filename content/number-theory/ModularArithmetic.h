/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "euclid.h"

const ll mod = 998244353; // change to something else
struct Mod {
	ll x;
	Mod(ll xx = 0) : x((xx % mod + mod) % mod) {}
	Mod operator+(Mod b) const { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) const { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) const { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) const { return *this * b.inv(); }
	Mod operator-() const { return Mod(-x); }
	Mod& operator+=(Mod b) { return *this = *this + b; }
	Mod& operator-=(Mod b) { return *this = *this - b; }
	Mod& operator*=(Mod b) { return *this = *this * b; }
	Mod& operator/=(Mod b) { return *this = *this / b; }
	Mod inv() const {
		ll s, t, g = euclid(x, mod, s, t);
		assert(g == 1);
		return Mod(s);
	}
	Mod pow(ll e) const {
		Mod r(1), a(x);
		while (e) {
			if (e & 1)
				r *= a;
			a *= a;
			e /= 2;
		}
		return r;
	}
};
