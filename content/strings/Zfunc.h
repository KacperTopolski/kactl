/**
 * Author: chilli
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s, except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string &S, bool z0n = false) {
	vi z(sz(S));
	int l = -1, r = -1;
	fwd(i, 1, sz(S)) { // from below l is a small L
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
			z[i]++;
		if (i + z[i] > r)
			l = i, r = i + z[i];
	}
	if (z0n && sz(S))
		z[0] = sz(S);
	return z;
}
