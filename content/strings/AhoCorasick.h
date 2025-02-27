/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: N / A
 * Description: Aho-Corasick algorithm for linear-time multipattern matching. Self explanatory. Call Build after adding all patterns.
 * Time: $O(26n) build$
 */
#pragma once
constexpr char AMIN = 'a'; // Smallest letter
constexpr int ALPHA = 26;  // Alphabet size
struct Aho {
	vector<array<int, ALPHA>> nxt{1};
	vi suf = {-1}, accLink = {-1};
	vector<vi> accept{1};
	// Add string with given ID to structure
	// Returns index of accepting node
	int add(const string& str, int id) {
		int i = 0;
		for (auto c : str) {
			if (!nxt[i][c-AMIN]) {
				nxt[i][c-AMIN] = sz(nxt);
				nxt.pb({}); suf.pb(-1);
				accLink.pb(1); accept.pb({});
			} // creates new node above
			i = nxt[i][c-AMIN];
		}
		accept[i].pb(id);
		return i;
	} // Build automata; time: O(V*ALPHA)
	void build() {
		static queue<int> que;
		for (auto e : nxt[0]) if (e) {
			suf[e] = 0; que.push(e);
		}
		while (!que.empty()) {
			int i = que.front(), s = suf[i], j = 0;
			que.pop();
			for (auto &e : nxt[i]) {
				if (e) que.push(e);
				(e ? suf[e] : e) = nxt[s][j++];
			}
			accLink[i] = (accept[s].empty() ?
					accLink[s] : s);
		} // propagate link information above
	} // Append `c` to state `i`
	int next(int i, char c) {
		return nxt[i][c-AMIN];
	} // Call `f` for each pattern accepted
	  // when in state `i` with its ID as argument.
	  // Return true from `f` to terminate early.
	  // Calls are in descreasing length order.
	void accepted(int i, auto f) {
		while (i != -1) {
			for (auto a : accept[i]) if (f(a)) return;
			i = accLink[i]; } } };
