/**
 * Author: Krzysztof Potepa
 * Date: 2024
 * Description: Self balancing tree with different operations in logn expected.
 */
#pragma once
struct Treap {
	struct Node {
		// E[0] = left child, E[1] = right child
		// weight = node random weight (for treap)
		// size = subtree size, par = parent node
		int E[2] = {-1, -1}, weight = rand();
		int size = 1, par = -1;
		bool flip = 0; // Is interval reversed?
	};
	vector<Node> G;
	Treap(int n = 0) : G(n) {} // makes n disjoint nodes
	int make() { G.pb({}); return sz(G)-1; }
	int size(int x) { // subtree size of node x
		return (x >= 0 ? G[x].size : 0);
	}
	void push(int x) { // x can be -1 !!!
		if (x >= 0 && G[x].flip) {
			G[x].flip = 0;
			swap(G[x].E[0], G[x].E[1]);
			for(auto e : G[x].E) if (e>=0) G[e].flip ^= 1;
		} // + any other lazy operations
	}
	void update(int x) { // pull data up (reverse of push)
		if (x >= 0) {
			int& s = G[x].size = 1;
			G[x].par = -1;
			for (auto e : G[x].E) if (e >= 0) {
				s += G[e].size;
				G[e].par = x;
			}
		} // + any other aggregates
	}
	// Split treap x into treaps l and r
	// such that l contains first i elements
	// and r the remaining ones.
	// x, l, r can be -1; time: ~O(lg n)
	void split(int x, int& l, int& r, int i) {
		push(x); l = r = -1;
		if (x < 0) return;
		int key = size(G[x].E[0]);
		if (i <= key) {
			split(G[x].E[0], l, G[x].E[0], i);
			r = x;
		} else {
			split(G[x].E[1], G[x].E[1], r, i-key-1);
			l = x;
		}
		update(x);
	}
	// Join treaps l and r into one treap left to right
	// l, r and returned value can be -1.
	int join(int l, int r) { // time: ~O(lg n)
		push(l); push(r);
		if (l < 0 || r < 0) return max(l, r);
		if (G[l].weight < G[r].weight) {
			G[l].E[1] = join(G[l].E[1], r);
			update(l);
			return l;
		}
		G[r].E[0] = join(l, G[r].E[0]);
		update(r);
		return r;
	}
	// Find i-th node in treap x.
	// Returns its key or -1 if not found.
	// x can be -1; time: ~O(lg n)
	int find(int x, int i) {
		while (x >= 0) {
			push(x);
			int key = size(G[x].E[0]);
			if (key == i) return x;
			x = G[x].E[key < i];
			if (key < i) i -= key+1;
		}
		return -1;
	}
	// Get key of treap containing node x
	// (key of treap root). x can be -1.
	int root(int x) { // time: ~O(lg n)
		while (G[x].par >= 0) x = G[x].par;
		return x;
	}
	// Get position of node x in its treap.
	// x is assumed to NOT be -1; time: ~O(lg n)
	int index(int x) {
		int p, i = size(G[x].E[G[x].flip]);
		while ((p = G[x].par) >= 0) {
			if (G[p].E[1] == x) i+=size(G[p].E[0])+1;
			if (G[p].flip) i = G[p].size-i-1;
			x = p;
		}
		return i;
	}
	// Reverse interval [l;r) in treap x.
	// Returns new key of treap; time: ~O(lg n)
	int reverse(int x, int l, int r) {
		int a, b, c;
		split(x, b, c, r);
		split(b, a, b, l);
		if (b >= 0) G[b].flip ^= 1;
		return join(join(a, b), c); } };
