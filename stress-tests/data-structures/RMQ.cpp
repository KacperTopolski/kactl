#include "../utilities/template.h"

#include "../../content/data-structures/RMQ.h"
#include "../../content/data-structures/RMQF.h"

int main() {
	mt19937 rng(2137);
	auto rnd = [&] (int l, int r) {
		return uniform_int_distribution<int>(l, r)(rng);
	};
	const int MAXIT = 100;
	const int MAXN = 500;
	rep(IT, MAXIT) {
		rep(N, MAXN) {
			vi v(N);
			rep(i,N) v[i] = rnd(0, N);
			shuffle(all(v), rng);
			RMQ<int> rmq(v);
			RMQF<int> rmqf(v);
			rep(i,N) {
				int n = 1 << 29;
				fwd(j,i,N) {
					int m = rmq.get(i, j);
					int mf = rmqf.get(i, j);
					n = min(n, v[j]);
					assert(n == m);
					assert(n == mf);
				}
			}
		}
		// cout << "Passed testset#" << IT + 1 << "/" << MAXIT << '\n';
	}
	cout<<"Tests passed!"<<endl;
}
