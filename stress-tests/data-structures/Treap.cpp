#include "../utilities/template.h"

#include "../../content/data-structures/Treap.h"

void compare(vi &vec, Treap &tr, int root) {
	const int n = sz(vec);

	assert(tr.size(root) == n);
	rep(i, n) {
		assert(tr.root(i) == root);
		assert(tr.find(root, i) == vec[i]);
		assert(tr.index(vec[i]) == i);
	}
}

int main() {
	rep(it, 3) for (int n : {1, 10, 100, 1000}) {
		mt19937 rnd{(long unsigned int)it};

		vi vec(n);
		iota(all(vec), 0);
		shuffle(all(vec), rnd);

		Treap tr(n);
		int root = -1;
		for (int i : vec) root = tr.join(root, i);

		compare(vec, tr, root);
		rep(_, 1000) {
			int l = int(rnd() % (n+1)), r = int(rnd() % (n+1));
			if (l > r) swap(l, r);

			reverse(vec.begin() + l, vec.begin() + r);
			root = tr.reverse(root, l, r);

			compare(vec, tr, root);
		}
	}

	cout<<"Tests passed!"<<endl;
}
