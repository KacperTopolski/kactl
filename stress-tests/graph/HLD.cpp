#include "../utilities/template.h"
#include "../utilities/genTree.h"

const int INF = 1e9;
struct LazyTree {
	int n = 1;
	vector<int> lazy, val;
	LazyTree(int k) {
		while (n < k) n *= 2;
		lazy.resize(2 * n);
		val.resize(2 * n);
	}
	void push(int node) {
		if (!lazy[node] || node >= n) return;
		rep(i, 2) {
			val[node * 2 + i] += lazy[node];
			lazy[node * 2 + i] += lazy[node];
		}
		lazy[node] = 0;
	}
	void add(int l, int r, int v, int node = 1, int nl = 0, int nr = -1) {
		if (nr < 0) nr = n - 1;
		if (l > nr || nl > r) return;
		if (l <= nl && nr <= r) {
			val[node] += v;
			lazy[node] += v;
			return;
		}
		push(node);
		int mid = (nl+nr)/2;
		add(l,r,v,node*2,nl,mid);
		add(l,r,v,node*2+1,mid+1,nr);
		val[node] = max(val[node*2], val[node*2+1]);
	}
	int query(int l, int r, int node = 1, int nl = 0, int nr = -1) {
		if (nr < 0) nr = n - 1;
		if (l > nr || nl > r) return -INF;
		if (l <= nl && nr <= r)
			return val[node];
		push(node);
		int mid = (nl+nr)/2;
		return max(
			query(l,r,node*2,nl,mid),
			query(l,r,node*2+1,mid+1,nr)
		);
	}
};

#include "../../content/graph/HLD.h"

namespace old {
#include "oldHLD.h"
}
struct bruteforce { // values in nodes
	vector<vector<int>> tree;
	vector<int> vals;
	vector<int> pars;
	int unit = -1e9;
	int f(int a, int b) { return max(a, b); }
	void root(int cur, int p = -1) {
		pars[cur] = p;
		for (auto i: tree[cur]) {
			if (i != p) root(i, cur);
		}
	}
	bruteforce(vector<vector<int>> _tree): tree(_tree), vals(sz(tree)), pars(sz(tree)) {
		root(0);
	}
	bool dfsModify(int cur, int target, int val, int p=-1) {
		if (cur == target) {
			vals[cur] += val;
			return true;
		}
		bool alongPath = false;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			alongPath |= dfsModify(i, target, val, cur);
		}
		if (alongPath) vals[cur] += val;
		return alongPath;
	}
	void modifyPath(int a, int b, int val) {
		dfsModify(a, b, val);
	}

	int dfsQuery(int cur, int target, int p = -1) {
		if (cur == target) {
			return vals[cur];
		}
		int res = unit;
		for (auto i: tree[cur]) {
			if (i == p) continue;
			res = f(res, dfsQuery(i, target, cur));
		}
		if (res != unit) {
			return f(res, vals[cur]);
		}
		return res;
	}
	int queryPath(int a, int b) {
		return dfsQuery(a, b);
	}
	int dfsSubtree(int cur, int p) {
		int res = vals[cur];
		for (auto i: tree[cur]) {
			if (i != p)
				res = f(res, dfsSubtree(i, cur));
		}
		return res;
	}
	int querySubtree(int a) {
		return dfsSubtree(a, pars[a]);
	}
};

void testAgainstOld(int n, int iters, int queries) {
	for (int trees = 0; trees < iters; trees++) {
		auto graph = genRandomTree(n);
		vector<vector<int>> tree1(n);
		vector<vector<pair<int, int>>> tree2(n);
		for (auto i : graph) {
			tree1[i.first].push_back(i.second);
			tree1[i.second].push_back(i.first);
		}
		for (int i = 0; i < sz(tree1); i++) {
			for (auto j : tree1[i]) {
				tree2[i].push_back({j, 0});
			}
		}
		HLD<false> hld(tree1);
		old::HLD hld2(tree2);
		for (int itr = 0; itr < queries; itr++) {
			if (rand() % 2) {
				int node = rand() % n;
				int val = rand() % 10;
				hld2.update(node, val);
				hld.modifyPath(node, node, val - hld.queryPath(node, node));
			} else {
				int a = rand() % n;
				int b = rand() % n;
				assert(hld.queryPath(a, b) == hld2.query2(a, b).first);
			}
		}
	}
}
void testAgainstBrute(int n, int iters, int queries) {
	for (int trees = 0; trees < iters; trees++) {
		auto graph = genRandomTree(n);
		vector<vector<int>> tree1(n);
		for (auto i : graph) {
			tree1[i.first].push_back(i.second);
			tree1[i.second].push_back(i.first);
		}
		HLD<false> hld(tree1);
		bruteforce hld2(tree1);
		for (int itr = 0; itr < queries; itr++) {
			int rng = rand() % 3;
			if (rng == 0) {
				int a = rand() % n;
				int b = rand() % n;
				int val = rand() % 10;
				hld.modifyPath(a, b, val);
				hld2.modifyPath(a, b, val);
			} else if (rng == 1){
				int a = rand() % n;
				int b = rand() % n;
				hld.queryPath(a, b);
				hld2.queryPath(a, b);
				assert(hld.queryPath(a, b) == hld2.queryPath(a, b));
			} else if (rng == 2) {
				int a = rand() % n;
				assert(hld.querySubtree(a) == hld2.querySubtree(a));
			}
		}
	}

}
int main() {
	srand(2);
	testAgainstBrute(5, 1000, 10000);
	testAgainstBrute(1000, 100, 100);
	testAgainstOld(5, 1000, 100);
	testAgainstOld(10000, 100, 1000);
	cout<<"Tests passed!"<<endl;
	return 0;
}
