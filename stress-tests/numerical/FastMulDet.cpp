#include "../utilities/template.h"

template<int MOD, int mod=MOD>
struct Tester {
#include "../../content/numerical/FastMulDet.h"

struct brute {
#include "../../content/numerical/IntDeterminant.h"
ll detNoDestroy(vector<vector<ll>> m) {
	return det(m);
}
};
brute Brute;

vector<ll> mulMatVec(vector<vector<ll>> m, vector<ll> v) {
	assert(sz(m[0]) == sz(v));
	vector<ll> r(sz(m));
	rep(i, sz(m)) rep(j, sz(v))
		(r[i] += m[i][j] * v[j]) %= MOD;
	return r;
}

ll fakeUseDet(vector<vector<ll>> m) {
	return det(sz(m), [&](vector<ll> v){
		return mulMatVec(m, v);
	});
}

void check(vector<vector<ll>> m, string err = "") {
	for (auto &r : m) for (ll &x : r)
		x = (x % MOD + MOD) % MOD;
	ll ex = Brute.detNoDestroy(m);
	ll has = fakeUseDet(m);
	if (ex != has) {
		rep(i, sz(m))
			deb(i, m[i]);
		deb(ex, has);
		if (sz(err)) deb(err);
		assert(false);
	}
}
void iden(int n) {
	ll has = det(n, [](auto x){ return x; });
	if (has != 1) {
		deb(n, has);
		assert(false);
	}
}
void idenA(int n) {
	ll has = det(n, [](auto x){
		fwd(i, 1, sz(x))
			x[i] = (x[i] + x[i-1]) % MOD;
		return x;
	});
	if (has != 1) {
		deb(n, has);
		assert(false);
	}
}
void idenB(int n) {
	ll has = det(n, [](auto x){
		fwd(i, 1, sz(x))
			x[i-1] = (x[i] + x[i-1]) % MOD;
		return x;
	});
	if (has != 1) {
		deb(n, has);
		assert(false);
	}
}


void allnxn(int n, int l, int r) {
	vector<vector<ll>> m(n, vector<ll>(n));
	auto rec = [&](auto self, int id) {
		if (id == n * n) {
			check(m);
			return;
		}
		ll &ref = m[id / n][id % n];
		for (ref = l; ref <= r; ++ref) self(self, id + 1);
	};
	rec(rec, 0);
}
void allndiag(int n, int l, int r) {
	vector<vector<ll>> m(n, vector<ll>(n));
	auto rec = [&](auto self, int id) {
		if (id == n) {
			check(m);
			return;
		}
		ll &ref = m[id][id];
		for (ref = l; ref <= r; ++ref) self(self, id + 1);
	};
	rec(rec, 0);
}
void id(int l, int r) {
	fwd(n, l, r+1) {
		vector<vector<ll>> m(n, vector<ll>(n));
		rep(i, n) m[i][i] = 1;
		check(m);
	}
}
Tester() {
	allnxn(1, -10, 10);
	allnxn(2, -2, 2);
	allnxn(3, -1, 1);
	allnxn(4, 0, 1);
	allndiag(1, -10, 10);
	allndiag(2, -10, 10);
	allndiag(3, -8, 8);
	allndiag(4, -6, 6);
	allndiag(5, -4, 4);
	allndiag(6, -3, 3);
	fwd(i, 1, 666) {
		iden(i);
		idenA(i);
		idenB(i);
	};
	rep(_, 2000)
		iden(2000);
}
};

int main() {
	Tester<998244353>{};
	cout<<"Tests passed!"<<endl;
}
