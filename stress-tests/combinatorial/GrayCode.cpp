#include "../utilities/template.h"

#include "../../content/combinatorial/GrayCode.h"

int main() {
	mt19937_64 rnd;
	rep(_, 1e5) {
		ull x = rnd();
		assert(gray(invg(x)) == x);
		assert(invg(gray(x)) == x);
	}
	set<ull> st, nd;
	rep(i, 1e5) {
		st.insert(gray(i));
		nd.insert(invg(i));
		assert(sz(st) == i+1);
		assert(sz(nd) == i+1);
		if (__builtin_popcount(i+1) == 1) {
			assert(*st.begin() == 0);
			assert(*st.rbegin() == (ull)i);
			assert(*nd.begin() == 0);
			assert(*nd.rbegin() == (ull)i);
		}
	}
	cout<<"Tests passed!"<<endl;
}
