/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
#pragma once

// const ll mod = 1000000007;
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans; }

ll modpow(ll b, ll e, ll m) {			// exclude-line
	ll ans = 1;							// exclude-line
	for (; e; b = b * b % m, e /= 2)	// exclude-line
		if (e & 1) ans = ans * b % m;	// exclude-line
	return ans;	}						// exclude-line
