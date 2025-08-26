#include "../utilities/template.h"

#include "../../content/graph/StronglyConnected.h"

namespace old {
vi orig, low, comp, z;
int no_vertices, no_components;
template<class G> void dfs(int j, G &g) {
	low[j] = orig[j] = no_vertices++;
	comp[j] = -2; z.push_back(j);
	for(auto &e:g[j])
		if (comp[e] == -1) {
			dfs(e, g);
			low[j] = min(low[j], low[e]);
		}
		else if (comp[e] == -2)
			low[j] = min(low[j], orig[e]);

	if (orig[j] == low[j]) {
		for (;;) {
			int x = z.back(); z.pop_back();
			comp[x] = no_components;
			if (x == j) break;
		}
		no_components++;
	}
}
template<class G> vi scc(G &g) {
	int n = sz(g);
	orig.assign(n, 0); low = orig;
	no_vertices = no_components = 0;
	comp.assign(n, -1);
	rep(i,n) if (comp[i] == -1) dfs(i, g);
	return comp;
}
}

void check_graph(vector<vi> &g) {
	old::scc(g);

	SCC scc(g);

	rep(idcomp, sz(scc.comps))
		for (int i : scc.comps[idcomp])
			assert(scc[i] == idcomp);

	rep(i, sz(g)) for (int j : g[i])
		assert(scc[i] >= scc[j]);

	assert(sz(scc.comps) == old::no_components);
}

int main() {
	vector<vi> g;
	rep(n, 5) rep(msk, 1 << (n*n)) {
		g.assign(n, vi());
		rep(i, n) rep(j, n) if (msk & (1 << (n*i+j)))
			g[i].pb(j);
		check_graph(g);
	}

	for (int n : {10, 100, 1000, 10000}) rep(muls, 20) {
		g.assign(n, vi());
		rep(_, n * muls)
			g[rand() % n].pb(rand() % n);
		check_graph(g);
	}

	cout<<"Tests passed!"<<endl;
	return 0;
}
