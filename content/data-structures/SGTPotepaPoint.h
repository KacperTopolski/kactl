/**
 * Author: Krzysztof Potepa
 * Date: 2024
 * Description: Segment tree point.
 */

// Point-interval segment tree
// - T - stored data type
// - ID - neutral element for query operation
// - f(a, b) - associative aggregate function
struct SegTree {
	using T = int;
	static constexpr T ID = INT_MIN;
	T f(T a, T b) { return max(a, b); }

	vector<T> V;
	int len = 1;

	SegTree(int n = 0, T def = 0) {
		while (len < n) len *= 2;
		V.resize(len+n, def);
		V.resize(len*2, ID);
		for (int i = len; --i;)
			V[i] = f(V[i*2], V[i*2+1]);
	}

	void set(int i, T val) {
		V[i += len] = val;
		while (i /= 2) V[i] = f(V[i*2], V[i*2+1]);
	}

	// Query interval [b;e); time: O(lg n)
	T query(int b, int e) {
		T x = ID, y = ID;
		b += len;
		for (e += len; b < e; b /= 2, e /= 2) {
			if (b % 2) x = f(x, V[b++]);
			if (e % 2) y = f(V[--e], y);
		}
		return f(x, y);
	}

	// Find smallest `j` such that
	// g(aggregate of [0,j)) is true; O(lg n)
	// The predicate `g` must be monotonic.
	// Returns -1 if no such prefix exists.
	int lowerBound(auto g) {
		if (!g(V[1])) return -1;
		T s, x = ID;
		int j = 1;
		while (j < len)
			if (!g(s = f(x, V[j *= 2]))) x = s, j++;
		return j - len + !g(x);
	}
};
