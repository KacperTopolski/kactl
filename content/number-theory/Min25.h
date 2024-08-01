/**
 * Author: Kacper Topolski
 * Date: 2024-07-31
 * License: N/A
 * Source: https://codeforces.com/blog/entry/92703
 * Description: Calculates prefsums of multiplicative function at each floor(N/i). id(N/i) returns index of N/i in keys[].
 * Remember about overflows. See example below.
 * Time: O(\frac{n^{3/4}}{\log n})
 * Status: Stress-tested
 */
#pragma once

vector<ll> global_primes; // global_primes.back() > sqrt(N); use e.g. sieve of Eratosthenes

template<typename T>
struct Min25 {
    ll N;
    vector<ll> keys, primes;
    Min25(ll N_) : N(N_) {
        for (ll l = 1; l <= N; ++l)
            keys.push_back(l = N / (N / l));
        for (int i = 0; global_primes[i] * global_primes[i] <= N; ++i)
            primes.push_back(global_primes[i]);
    }
    ll id(ll x) {
        ll id = x < N / x ? x - 1 : sz(keys) - N / x;
        assert(keys[id] == x);
        return id;
    }
    // f has to be TOTALLY multiplicative, pref(x) is regular prefix sum function of f
    vector<T> overPrimes(auto pref) {
        vector<T> dp(sz(keys));
        rep(i, sz(keys))
            dp[i] = pref(keys[i]) - T(1);
        for (ll p : primes) {
            auto fp = dp[p - 1] - dp[p - 2];
            for (int i = sz(keys) - 1; i >= 0 && p * p <= keys[i]; --i)
                dp[i] = dp[i] - (dp[id(keys[i] / p)] - dp[p - 2]) * fp;
        }
        return dp;
    }
    // dp are prefix sums of f over primes, f(prime, power, prime**power) calculates f on primes powers
    void fullSum(vector<T> &dp, auto f) {
        for (ll p : primes | views::reverse) {
            for (int i = sz(keys) - 1; i >= 0 && p * p <= keys[i]; --i) {
                for (ll k = 1, q = p; q * p <= keys[i]; ++k, q *= p)
                    dp[i] = dp[i] + f(p, k + 1, q * p) + f(p, k, q) * (dp[id(keys[i] / q)] - dp[p - 1]);
            }
        }
        for (auto &v : dp) v = v + T(1);
    }
};

/*vector<ll> example(Min25<ll> &min25) {
    auto primeCnt = min25.overPrimes([](ll x){return x; }); // f(x)=1 over primes
    auto primeSum = min25.overPrimes([](ll x){return x*(x+1)/2; }); // f(x)=x over primes
    vector<ll> phi;
    rep(i, sz(min25.keys))
        phi.push_back(primeSum[i] - primeCnt[i]); // f(x)=x-1 over primes i.e. phi(x)=f(x)
    min25.fullSum(phi, [](int p, int k, ll pk){return pk - pk / p; }); // f(x)=phi(x) over all numbers
    return phi;
}*/
