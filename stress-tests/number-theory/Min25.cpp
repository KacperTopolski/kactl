#include "../utilities/template.h"

#include "../../content/number-theory/Min25.h"

namespace phi {
#include "../../content/number-theory/phiFunction.h"
}

const ll mod = phi::MOD;
struct Mod {
    ll x;
    Mod() : x(0) {}
    Mod(ll xx) : x((xx + mod) % mod) {}
    static Mod unsafe(ll x) {
        Mod m;
        m.x = x;
        return m;
    }
    static Mod c2(ll x) {
        (x %= mod) += mod;
        return (x & 1) ? unsafe(x) * unsafe((x-1)/2) : unsafe(x/2) * unsafe(x-1);
    }
    Mod operator+(Mod b) { return unsafe(x + b.x < mod ? x + b.x : x + b.x - mod); }
    Mod operator-(Mod b) { return unsafe(x - b.x < 0 ? x - b.x + mod : x - b.x); }
    Mod operator*(Mod b) { return Mod(x * b.x); }
};

vector<ll> prefCnt, prefSum, prefPhi;

void init() {
    phi::calcPhiSum();
    const int M = 2e7;
    prefCnt.resize(M);
    prefSum.resize(M);
    prefPhi.resize(M);
    iota(all(prefPhi), 0);

    fwd(i, 2, M) {
        if (prefPhi[i] == i) {
            global_primes.push_back(i);
            prefCnt[i] = 1;
            prefSum[i] = i;
            for (int j = i; j < M; j += i)
                prefPhi[j] -= prefPhi[j] / i;
        }
        (prefCnt[i] += prefCnt[i - 1]) %= mod;
        (prefSum[i] += prefSum[i - 1]) %= mod;
        (prefPhi[i] += prefPhi[i - 1]) %= mod;
    }
}

void test(ll N) {
    Min25<Mod> min25(N);
    auto primeCnt = min25.overPrimes([](ll x){return Mod(x); });
    auto primeSum = min25.overPrimes([](ll x){return Mod::c2(x+1); });
    vector<Mod> phi;
    rep(i, sz(min25.keys))
        phi.push_back(primeSum[i] - primeCnt[i]);
    min25.fullSum(phi, [](ll p, ll k, ll pk){return (void)k, Mod(pk - pk / p); });

    assert(min25.keys.front() == 1);
    assert(min25.keys.back() == N);
    rep(i, sz(min25.keys))
        assert(i == min25.id(min25.keys[i]));

    for (ll x : min25.keys) {
        if (x < sz(prefCnt)) {
            assert(prefCnt[x] == primeCnt[min25.id(x)].x);
            assert(prefSum[x] == primeSum[min25.id(x)].x);
            assert(prefPhi[x] == phi[min25.id(x)].x);
        }
        assert(phi::getPhiSum(x + 1) == phi[min25.id(x)].x);
    }
}

int main() {
    init();
    vector<ll> testdata = {(ll) 1e11};
    mt19937_64 rnd;
    rep(_, 5) {
        testdata.push_back(1 + rnd() % (ll)(1e1));
        testdata.push_back(1 + rnd() % (ll)(1e2));
        testdata.push_back(1 + rnd() % (ll)(1e3));
        testdata.push_back(1 + rnd() % (ll)(1e4));
        testdata.push_back(1 + rnd() % (ll)(1e5));
        testdata.push_back(1 + rnd() % (ll)(1e6));
        testdata.push_back(1 + rnd() % (ll)(1e7));
        testdata.push_back(1 + rnd() % (ll)(1e8));
        testdata.push_back(1 + rnd() % (ll)(1e9));
        testdata.push_back(1 + rnd() % (ll)(1e10));
        testdata.push_back(1 + rnd() % (ll)(1e11));
    }
    for (ll x : testdata)
        test(x);

    cout<<"Tests passed!"<<endl;
}
