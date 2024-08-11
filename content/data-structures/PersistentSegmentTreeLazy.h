/**
 * Author: Amtek
 * Date: 2023-10-25
 * License: CC0
 * Source: folklore
 * Description: sparse (N can be up to 1e18) persistent segment tree supporting
 * lazy propagation. Ranges are inclusive
 * Time: O(\log N)
 * Status: tested a bit (not much)
 */

struct LazyPSegmentTree { // default: update +, query max
	typedef int val;
	val idntV = 0; // identity value
	val fV(val l, val r) {
		return max(l, r); // implement combining values
	}
	typedef int lazy;
	lazy idntL = 0;
	lazy fL(lazy prv, lazy nxt) {
		return prv + nxt; // implement combining lazy
	}
	val apl(val x, lazy lz) {
		return x + lz; // implement applying lazy
	}
	struct node {
		int l = 0, r = 0;
		val x;
		lazy lz;
		node(val x, lazy lz) : x(x), lz(lz) {
		}
	};
	int N;
	vector<node> t;
	LazyPSegmentTree(int N) : N(N) {
		t.pb(
			node(idntV, idntL)); // 0th node is the root of an empty tree
								 // t.reserve() in case of memory issues
	}
	int cpy(int v) {
		t.pb(t[v]);
		return sz(t) - 1;
	}
	void aplV(int v, lazy lz) {
		t[v].lz = fL(t[v].lz, lz);
		t[v].x = apl(t[v].x, lz);
	}
	// creates 4 * lgN +- eps new nodes
	int upd(int v, int l, int r, lazy lz, int a = 0, int b = -1, int u = -1) {
		if (u == -1) {
			u = cpy(v);
			b = N - 1;
		}
		if (l > b || r < a)
			return u;
		if (a >= l && b <= r) {
			aplV(u, lz);
			return u;
		}
		int c = (a + b) / 2;
		t[u].l = cpy(t[v].l);
		t[u].r = cpy(t[v].r);
		aplV(t[u].l, t[u].lz);
		aplV(t[u].r, t[u].lz);
		upd(t[v].l, l, r, lz, a, c, t[u].l);
		upd(t[v].r, l, r, lz, c + 1, b, t[u].r);
		t[u].lz = idntL;
		t[u].x = fV(t[t[u].l].x, t[t[u].r].x);
		return u;
	}
	// doesn't create new nodes
	val get(int v, int l, int r, int cl = 0, int cr = -1) {
		if (cr == -1)
			cr = N - 1;
		if (!v || l > cr || r < cl)
			return idntV;
		if (cl >= l && cr <= r)
			return t[v].x;
		int m = (cl + cr) / 2;
		return apl(
			fV(get(t[v].l, l, r, cl, m), get(t[v].r, l, r, m + 1, cr)),
			t[v].lz);
	}
};