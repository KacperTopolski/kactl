/**
 * Author: Czajnique
 * Date: 2024
 * License: N/A
 * Description: DFS over dense graph. Suddenly DFS over N <= 1000 graph many times becomes feasible
 * Status: stress-tested
 */

// DFS over bit-packed adjacency matrix
// G = NxN adjacency matrix of graph
//     G(i,j) <=> (i,j) is edge
// V = 1xN matrix containing unvisited vertices
//     V(0,i) <=> i-th vertex is not visited
// Total DFS time: O(n^2/64)

using ull = uint64_t;

// Matrix over Z_2 (bits and xor)
// TODO: arithmetic operations //!HIDE
struct BitMatrix {
	vector<ull> M;
	int rows, cols, stride;

	// Create matrix with n rows and m columns
	BitMatrix(int n = 0, int m = 0) {
		rows = n; cols = m;
		stride = (m+63)/64;
		M.resize(n*stride);
	}

	// Get pointer to bit-packed data of i-th row
	ull* row(int i) { return &M[i*stride]; }

	// Get value in i-th row and j-th column
	bool operator()(int i, int j) {
		return (row(i)[j/64] >> (j%64)) & 1;
	}

	// Set value in i-th row and j-th column
	void set(int i, int j, bool val) {
		ull &w = row(i)[j/64], m = 1ull << (j%64);
		if (val) w |= m;
		else w &= ~m;
	}
};


struct DenseDFS {
	BitMatrix G, V; // space: O(n^2/64)

	// Initialize structure for n vertices
	DenseDFS(int n = 0) : G(n, n), V(1, n) {
		reset();
	}

	// Mark all vertices as unvisited
	void reset() { for(auto &x : V.M) x = -1; }

	// Get/set visited flag for i-th vertex
	void setVisited(int i) { V.set(0, i, 0); }
	bool isVisited(int i)  { return !V(0, i); }

	// DFS step: func is called on each unvisited
	// neighbour of i. You need to manually call
	// setVisited(child) to mark it visited
	// or this function will call the callback
	// with the same vertex again.
	void step(int i, auto func) {
		ull* E = G.row(i);
		for (int w = 0; w < G.stride;) {
			ull x = E[w] & V.row(0)[w];
			if (x) func((w<<6) | __builtin_ctzll(x));
			else   w++;
		}
	}
};