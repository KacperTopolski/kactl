/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * point updates and range queries. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested on https://codeforces.com/contest/813/problem/E
 */

struct PSegmentTree { // default: update set_pos, query sum
	typedef int val;
	val idnt = 0; // identity value
	val f(val l, val r) {
		return l + r; // implement this!
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
	// creates lgN +- eps new nodes
	int upd(int v, int p, val x, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		int u = cpy(v);
		if (a == b) {
			t[u].x = x; // change something here if not swaping values
			return u;
		}
		int c = (a + b) / 2;
		if (p <= c)
			t[u].l = upd(t[v].l, p, x, a, c);
		else
			t[u].r = upd(t[v].r, p, x, c + 1, b);
		t[u].x = f(t[t[u].l].x, t[t[u].r].x);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int l, int r, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (!v || l > b || r < a)
			return idnt;
		if (a >= l && b <= r)
			return t[v].x;
		int c = (a + b) / 2;
		return f(get(t[v].l, l, r, a, c), get(t[v].r, l, r, c + 1, b));
	}
};
