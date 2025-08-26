#include "../utilities/template.h"

const int mod = 7; // 4

#include "../../content/numerical/IntDeterminant.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"
#include "../../content/numerical/Determinant.h"
#pragma GCC diagnostic pop

ll idet(vector<vector<ll>>& a) { // integer determinant
	int n = sz(a); ll ans = 1;
	rep(i,n) {
		fwd(j,i+1,n) {
			while (a[j][i] != 0) { // gcd step
				ll t = a[i][i] / a[j][i]; // can take mod-inv if mod p
				fwd(k,i,n) a[i][k] -= a[j][k] * t;
				swap(a[i], a[j]);
				ans *= -1;
			}
		}
		if (!a[i][i]) return 0;
		ans *= a[i][i];
	}
	return ans;
}

template<class F>
void rec(int i, int j, vector<vector<ll>>& A, F f) {
	if (i == sz(A)) {
		f();
	}
	else if (j == sz(A[i])) {
		rec(i+1, 0, A, f);
	}
	else {
		rep(v,mod) {
			A[i][j] = v;
			rec(i, j+1, A, f);
		}
	}
}

template<class F>
void rec2(int i, vector<ll>& A, F f) {
	if (i == sz(A)) f();
	else {
		rep(v,mod) {
			A[i] = v;
			rec2(i+1, A, f);
		}
	}
}

int main() {
	rep(n,4) {
		vector<vector<ll>> mat(n, vector<ll>(n, 0)), mat2;
		vector<vector<double>> mat3(n, vector<double>(n, 0));
		rec(0,0,mat,[&]() {
			rep(i,n) rep(j,n) mat3[i][j] = (double)mat[i][j];
			// mat2 = mat; ll a = det(mat2);
			int a = (int)round(det(mat3)) % mod;
			mat2 = mat; ll b = idet(mat2) % mod;
			if (a < 0) a += mod;
			if (b < 0) b += mod;
			if (a != b) {
				rep(i,n) {
					rep(j,n) cout << mat[i][j];
					cout << endl;
				}
				cout << a << ' ' << b << endl;
				assert(a == b);
			}
		});
	}
	cout<<"Tests passed!"<<endl;
}
