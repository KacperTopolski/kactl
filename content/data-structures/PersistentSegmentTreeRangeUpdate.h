/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * range updates and point queries. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested on https://codeforces.com/contest/1887/problem/D
 */

struct PSegmentTree { // default: update add, query val
	typedef int val;
	val idnt = 0; // neutral value
	val f(val a, val b) {
		return a + b; // implement this!
	}
	struct node {
		int l = 0, r = 0;
		val x;
		node(val x) : x(x) {
		}
	};
	int N;
	vector<node> t;
	PSegmentTree(int N) : N(N) {
		t.push_back(node(idnt)); // 0th node is the root of an empty tree
	} // t.reserve() in case of memory issues
	int cpy(int v) {
		t.push_back(t[v]);
		return sz(t) - 1;
	}
	// creates 4 * lgN +- eps new nodes
	int upd(int v, int l, int r, val x, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (l > b || r < a)
			return v;
		int u = cpy(v);
		if (a >= l && b <= r) {
			t[u].x = f(t[u].x, x);
			return u;
		}
		int c = (a + b) / 2;
		t[u].l = upd(t[v].l, l, r, x, a, c);
		t[u].r = upd(t[v].r, l, r, x, c + 1, b);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int p, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (a == b)
			return t[v].x;
		int c = (a + b) / 2;
		if (p <= c)
			return f(t[v].x, get(t[v].l, p, a, c));
		return f(t[v].x, get(t[v].r, p, c + 1, b));
	}
};
