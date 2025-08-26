#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/EdgeColoringBipartite.h"

void check_graph(int n, vector<pii> &ed) {
	vi deg(n*2);
	for (auto [x, y] : ed) ++deg[x], ++deg[y + n];
	int maxdeg = n ? *max_element(all(deg)) : 0;
	vi cols = edgeColoring(n, ed);
	assert(sz(cols) == sz(ed));
	vector<vector<bool>> usedCols(n*2, vector<bool>(maxdeg));
	rep(i,sz(cols)) {
		int col = cols[i];
		assert(cols[i] < maxdeg);
		for (int x : {ed[i].st, ed[i].nd + n}) {
			assert(!usedCols[x][col]);
			usedCols[x][col] = 1;
		}
	}
}

int main() {
	vector<pii> g;
	rep(n, 5) rep(msk, 1 << (n*n)) {
		g.clear();
		rep(i, n) rep(j, n) if (msk & (1 << (n*i+j)))
			g.eb(i, j);
		check_graph(n, g);
	}

	for (int n : {10, 100, 1000}) rep(muls, 20) {
		g.clear();
		rep(_, n * muls)
			g.eb(rand()%n, rand()%n);
		sort(all(g));
		g.erase(unique(all(g)), g.end());
		shuffle_vec(g);
		check_graph(n, g);
	}

	cout<<"Tests passed!"<<endl;
	return 0;
}
