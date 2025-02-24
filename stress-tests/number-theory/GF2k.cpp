#include "../utilities/template.h"

#include "../../content/number-theory/GF2k.h"

using GF2_8 = GF<unsigned char>;
using GF2_16 = GF<unsigned short>;
using GF2_32 = GF<unsigned>;
using GF2_64 = GF<unsigned long long>;
using GF2_128 = GF<__uint128_t>;

template <typename T>
auto &operator<<(auto &os, GF<T> g) {
	return os << ll(g.x);
}

template <typename T>
bool test() {
	mt19937_64 rnd{37};
	rep(_, 10000) {
		T x{rnd()};

		T pl = x * T(1);
		T pr = T(1) * x;
		if (pl.x != x.x || pr.x != x.x) {
			deb(x, pl, pr);
			assert(false);
		}

		if (!x.x) continue;

		T il = x * x.inv();
		T ir = x.inv() * x;
		if (il.x != 1 || ir.x != 1) {
			deb(x, il, ir);
			// assert(false);
			return false;
		}
	}
	return true;
}

/*template <typename T>
struct dynGF {
	static T poly;
	T x = 0;
	dynGF operator+(dynGF o) { return {x ^ o.x}; }
	dynGF operator-(dynGF o) { return {x ^ o.x}; }
	dynGF operator*(dynGF o) {
		T r = 0;
		for (int i = k() - 1; i >= 0; --i) {
			r = T(r & bit(k() - 1) ? (r << 1) ^ poly : r << 1);
			if (x & bit(i)) r ^= o.x;
		}
		return {r};
	}
	dynGF operator/(dynGF o) { return *this * o.inv(); }
	dynGF pow(T e) {
		dynGF r{1}, b{x};
		while (e) {
			if (e & 1)
				r = r * b;
			b = b * b;
			e /= 2;
		}
		return r;
	}
	dynGF inv() { return pow(T(-2)); }
	static int k() { return 8 * sizeof(T); }
	static T bit(int i) { return T(1) << i; }
};
template <typename T>
T dynGF<T>::poly = 0;

template <typename T>
auto &operator<<(auto &os, dynGF<T> g) {
	return os << ll(g.x);
}*/

int main() {
	assert(test<GF2_8>());
	assert(test<GF2_16>());
	assert(test<GF2_32>());
	assert(test<GF2_64>());
	assert(test<GF2_128>());

	/*rep(i, 1e9) {
		using dGF2_8 = dynGF<unsigned char>;
		using dGF2_16 = dynGF<unsigned short>;
		using dGF2_32 = dynGF<unsigned>;
		using dGF2_64 = dynGF<unsigned long long>;
		using dGF2_128 = dynGF<__uint128_t>;
		dGF2_8::poly = i;
		dGF2_16::poly = i;
		dGF2_32::poly = i;
		dGF2_64::poly = i;
		dGF2_128::poly = i;
		deb(i);

		if (!test<dGF2_8>()) continue;
		if (!test<dGF2_16>()) continue;
		if (!test<dGF2_32>()) continue;
		if (!test<dGF2_64>()) continue;
		if (!test<dGF2_128>()) continue;

		deb(i);
		break;
	}*/

	cout<<"Tests passed!"<<endl;
}
