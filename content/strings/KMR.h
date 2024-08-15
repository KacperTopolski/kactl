/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: N / A
 * Description: KMR algorithm for lexical string comparison. Niby nlog^2 ale to nie takie uczciwe nlog2 tylko z estede sortem.
 */
struct KMR {
	vector<vi> ids; KMR() {}
	// You can change str type to vi freely.
	KMR(const string& str) {
		ids.clear(); ids.pb(vi(all(str)));
		for (int h = 1; h <= sz(str); h *= 2) {
			vector<pair<pii, int>> tmp;
			rep(j, sz(str)) {
				int a = ids.back()[j], b = -1; 
				if (j+h < sz(str)) b = ids.back()[j+h];
				tmp.pb({ {a, b}, j });
			}
			sort(all(tmp));
			ids.emplace_back(sz(tmp));
			int n = 0;
			rep(j, sz(tmp)) {
				if (j > 0 && tmp[j-1].st != tmp[j].st)
					n++;
				ids.back()[tmp[j].nd] = n;
			}
		}
	} // Get representative of [begin;end); O(1)
	pii get(int begin, int end) {
		if (begin >= end) return {0, 0};
		int k = __lg(end-begin);
		return {ids[k][begin], ids[k][end-(1<<k)]};
	} // Compare [b1;e1) with [b2;e2); O(1)
	// Returns -1 if <, 0 if ==, 1 if >
	int cmp(int b1, int e1, int b2, int e2) {
		int l1 = e1-b1, l2 = e2-b2;
		int l = min(l1, l2);
		pii x = get(b1, b1+l), y = get(b2, b2+l);
		if (x == y) return (l1 > l2) - (l1 < l2);
		return (x > y) - (x < y);
	} // Compute suffix array of string; O(n)
	vi sufArray() {
		vi sufs(sz(ids.back()));
		rep(i, sz(ids.back()))
			sufs[ids.back()[i]] = i;
		return sufs; } };