/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: N/A
 * Source: https://codeforces.com/blog/entry/92339?#comment-810242
 * Description: Matching for general graphs using Blossom algorithm.
 * Time: O(NM, fast in practice)
 * Status: tested on library-checker
 */
int blossom(vector<vi>& G, vi& match) {
	int n = sz(G), cnt = -1, ans = 0;match.assign(n, -1);
	vi lab(n), par(n), orig(n), aux(n, -1), q;
	auto blos = [&](int v, int w, int a) {
		while (orig[v] != a) {
			par[v] = w; w = match[v];
			if (lab[w] == 1) lab[w] = 0, q.pb(w);
			orig[v] = orig[w] = a; v = par[w];
		}
	};
	rep(i, n) if (match[i] == -1)
		for (auto e : G[i]) if (match[e] == -1) {
			match[match[e] = i] = e; ans++; break;
		}
	rep(root, n) if (match[root] == -1) {
		fill(all(lab), -1);
		iota(all(orig), 0);
		lab[root] = 0;
		q = {root};
		rep(i, sz(q)) {
			int v = q[i];
			for (auto x : G[v]) if (lab[x] == -1) {
				lab[x] = 1; par[x] = v;
				if (match[x] == -1) {
					for (int y = x; y+1;) {
						int p = par[y], w = match[p];
						match[match[p] = y] = p; y = w;
					}
					ans++;
					goto nxt;
				}
				lab[match[x]] = 0; q.pb(match[x]);
			} else if (lab[x] == 0 && orig[v]!=orig[x]) {
				int a = orig[v], b = orig[x];
				for (cnt++;; swap(a, b)) if (a+1) {
					if (aux[a] == cnt) break;
					aux[a] = cnt;
					a = (match[a]+1 ?
						orig[par[match[a]]] : -1);
				}
				blos(x, v, a); blos(v, x, a);
			}
		}
		nxt:;
	}
	return ans; }