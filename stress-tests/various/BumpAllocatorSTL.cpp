#include "../utilities/template.h"

#include "../../content/various/BumpAllocatorSTL.h"

int main() {
	rep(_, 3) rep(n, 1000) rep(mul, 10) {
		buf_ind = sizeof buf;
		vector<vector<int, small<int>>> g;
		// vector<vector<int>> g;
		g.resize(n);
		rep(__, n * mul)
			g[rand() % n].pb(1);
	}
	cout<<"Tests passed!"<<endl;
}
