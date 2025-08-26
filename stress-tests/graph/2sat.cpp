#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/2Sat.h"

int main1() {
	const int N = 100000, M = 10000000;
	// Random constraints, unsolvable
	{
		SAT2 ts(N);
		rep(i,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a ^ (s&1 ? 0 : -1), b ^ (s&2 ? 0 : -1));
		}
		assert(ts.solve() == 0);
	}
	// Random solvable instance
	{
		vector<bool> v(N);
		rep(i,N) v[i] = rand() & (1 << 20);
		SAT2 ts(N);
		rep(i,M) {
			int r = rand();
			int s = r;
			r >>= 2;
			int a = r % N;
			r >>= 5;
			int b = r % N;
			if (a == b) continue;
			ts.either(a ^ (v[a] ? 0 : -1), b ^ (s&1 ? 0 : -1));
		}
		assert(ts.solve() == 1);
	}
	return 0;
}

int main2() {
	int N = 4;
	SAT2 ts(N);
	ts.either(0,1);
	ts.either(0,~1);
	ts.either(~2,~3);
	assert(ts.solve()==1);
	assert(ts == vi({1, 1, 0, 0}));
	return 0;
}

int ra() {
	static unsigned X;
	X *= 1283611;
	X += 123;
	return X >> 1;
}

// Test at_most_one
int main() {
	main1();
	main2();
	const int N = 100, M = 400;
	fwd(it,0,100) {
		vector<bool> v(N);
		rep(i,N) v[i] = ra() & (1 << 20);
		SAT2 ts(N);
		vector<vi> atm;
		vi r;
		rep(i,M) {
			if (ra()%100 < 5) {
				int ri = ra();
				int s = ri;
				ri >>= 2;
				int a = ri % N;
				ri >>= 5;
				int b = ri % N;
				if (a == b) continue;
				ts.either(v[a] ? a : ~a, (s&1) ? b : ~b);
			} else {
				int k = ra() % 4 + 1;
				r.clear();
				fwd(ki,0,k-1) {
					int a = ra() % N;
					r.push_back(v[a] ? ~a : a);
				}
				r.push_back(ra() % (2*N) - N);
				shuffle_vec(r);
				ts.atMostOneTrue(r);
				atm.push_back(r);
			}
		}
		assert(ts.solve());
		int to = 0;
		rep(i,N) to += (ts[i] == v[i]);
		for(auto &ri: atm) {
			int co = 0;
			for(auto &x: ri) co += (ts[max(x, ~x)] == (x >= 0));
			assert(co <= 1);
		}
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}
