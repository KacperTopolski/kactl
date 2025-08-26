#include <bits/stdc++.h>
auto &operator<<(auto &os, __uint128_t x) {
	return os << (long long)(x);
}
#include "../utilities/template.h"

#include "../../content/number-theory/GF2k.h"

template <typename T>
auto &operator<<(auto &os, GF<T> g) {
	return os << ll(g.x);
}

template <typename BaseT>
bool is_gen(GF<BaseT> x) {
	vector<BaseT> divs = {BaseT(3), BaseT(5), BaseT(17), BaseT(257), BaseT(65537), BaseT(641),
						  BaseT(6700417), BaseT(274177), BaseT(67280421310721)};
	BaseT prod(1);
	int szdivs = 0;
	while (prod != BaseT(-1))
		prod *= divs[szdivs++];
	divs.resize(szdivs);

	assert(x.pow(-1).x == 1);
	for (auto div : divs)
		if (x.pow(BaseT(BaseT(-1)/div)).x == BaseT(1))
			return false;
	return true;
}


template <typename BaseT>
bool test() {
	using T = GF<BaseT>;

	mt19937_64 rnd{37};
	rep(_, 1000) {
		T x{(BaseT)rnd()};

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

	assert(is_gen(T(1).generator()));

	return true;
}

int main() {
	assert(test<unsigned char>());
	assert(test<unsigned short>());
	assert(test<unsigned>());
	assert(test<unsigned long long>());
	assert(test<__uint128_t>());

	// for (int i = 1; i < 100; ++i) {
	// 	if (!is_gen(GF<unsigned char>(-i))) continue;
	// 	if (!is_gen(GF<unsigned short>(-i))) continue;
	// 	if (!is_gen(GF<unsigned>(-i))) continue;
	// 	if (!is_gen(GF<unsigned long long>(-i))) continue;
	// 	if (!is_gen(GF<__uint128_t>(-i))) continue;
	// 	deb(i);
	// }

	cout<<"Tests passed!"<<endl;
}
