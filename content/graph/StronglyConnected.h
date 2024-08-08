/**
 * Author: Krzysztof Potępa
 * Date: 2024
 * License: CC0
 * Description: SCC scc(graph),
 * scc[v] = index of SCC of vertex v,
 * scc.comps[i] = vertices of i-th scc,
 * components in reverse topological order
 * Time: O(|E| + |V|)
 */
#pragma once
struct SCC : vi {
	vector<vi> comps; vi S; SCC() {}
	SCC(vector<vi>& G) : vi(sz(G),-1), S(sz(G))
	{ rep(i, sz(G)) if (!S[i]) dfs(G, i); }
	int dfs(vector<vi>& G, int v) {
		int low = S[v] = sz(S); S.push_back(v);
		for (auto e : G[v]) if (at(e) < 0)
			low = min(low, S[e] ?: dfs(G, e));
		if (low == S[v]) {
			comps.push_back({});
			fwd(i, S[v], sz(S)) {
				at(S[i]) = sz(comps)-1;
				comps.back().push_back(S[i]);
			}
			S.resize(S[v]);
		}
		return low; } };