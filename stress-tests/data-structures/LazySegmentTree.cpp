#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/LazySegmentTree.h"

volatile int res;
int main() {
	int N = 10;
	vi v(N);
	iota(all(v), 0);
	shuffle_vec(v);
	Node* tr = new Node(v,0,N);
	rep(i,N) rep(j,N) if (i <= j) {
		int ma = -inf;
		fwd(k,i,j) ma = max(ma, v[k]);
		assert(ma == tr->query(i,j));
	}
	fwd(it,0,1000000) {
		int i = rand() % (N+1), j = rand() % (N+1);
		if (i > j) swap(i, j);
		int x = (rand() % 10) - 5;

		int r = rand() % 100;
		if (r < 30) {
			::res = tr->query(i, j);
			int ma = -inf;
			fwd(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr->add(i, j, x);
			fwd(k,i,j) v[k] += x;
		}
		else {
			tr->set(i, j, x);
			fwd(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
