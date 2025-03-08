#include "../utilities/template.h"

#include "../../content/number-theory/GF2k.h"

template <typename T>
auto &operator<<(auto &os, GF<T> g) {
	return os << ll(g.x);
}

template <typename BaseT>
bool test() {
	using T = GF<BaseT>;

	mt19937_64 rnd{37};
	rep(_, 10000) {
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
	return true;
}

int main() {
	assert(test<unsigned char>());
	assert(test<unsigned short>());
	assert(test<unsigned>());
	assert(test<unsigned long long>());
	assert(test<__uint128_t>());

	cout<<"Tests passed!"<<endl;
}
