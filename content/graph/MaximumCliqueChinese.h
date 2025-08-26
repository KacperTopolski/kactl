/**
 * Author: ???
 * Date: 2024-03-24
 * License: N/A
 * Source: https://codeforces.com/contest/1949/submission/253084155
 * Description: Chinese max clique heuristic, good for geometric packing problems. Vertices should be ordered by (X, Y) (not shuffled!).
 * Status: not tested
 */
#pragma once

constexpr int N = 405;
struct MaxClique {
	bool g[N][N];
	int n, dp[N], st[N][N], ans, res[N], stk[N];
	void init(int n_) {
		n = n_; memset(g, 0, sizeof(g));
	}
	void addEdge(int u, int v, int w) {
		g[u][v] = w;
	}
	bool dfs(int siz, int num) {
		if (siz == 0) {
			if (num > ans) {
				ans = num;
				copy(stk+1, stk+1+num, res+1);
				return 1;
			}
			return 0;
		}
		rep(i, siz) {
			if (siz-i+num <= ans) return 0;
			int u = st[num][i];
			if (dp[u]+num <= ans) return 0;
			int cnt = 0;
			fwd(j, i+1, siz) if (g[u][st[num][j]])
				st[num+1][cnt++] = st[num][j];
			stk[num+1] = u;
			if (dfs(cnt, num + 1)) return 1;
		}
		return 0;
	}
	int solve() {
		ans = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = n; i >= 1; i--) {
			int cnt = 0;
			fwd(j, i+1, n+1)
				if (g[i][j]) st[1][cnt++] = j;
			stk[1] = i;
			dfs(cnt, 1);
			dp[i] = ans;
		}
		return ans;
	}
};
