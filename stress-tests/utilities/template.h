#include <bits/stdc++.h>
using namespace std;
#define fwd(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) fwd(i, 0, n)
#define all(X) X.begin(), X.end()
#define sz(X) int(ssize(X))
#define pb push_back
#define eb emplace_back
#define st first
#define nd second
using pii = pair<int, int>; using vi = vector<int>;
using ll = long long; using ld = long double;
#ifdef LOC
auto SS = signal(6, [](int) { *(int *)0 = 0; });
#define DTP(x, y) auto operator << (auto &o, auto a) -> decltype(y, o) { o << "("; x; return o << ")"; }
DTP(o << a.st << ", " << a.nd, a.nd);
DTP(for (auto i : a) o << i << ", ", all(a));
void dump(auto... x) { (( cerr << x << ", " ), ...) << '\n'; }
#define deb(x...) cerr << setw(4) << __LINE__ << ":[" #x "]: ", dump(x)
#else
#define deb(...) 0
#endif

// for old tests
#define debug(x...) deb(x)

// WSL1 is broken, remove once nobody in the team uses WSL1
#if __has_include (<fpu_control.h>)
#include <fpu_control.h>
namespace wsl {
auto is_wsl = [](){
	ifstream stream("/proc/version");
	string str;
	getline(stream, str);
	for (char &ch : str)
		ch = (char) tolower((unsigned char) ch);
	if (str.find("microsoft") == string::npos)
		return false;
	unsigned short Cw = 0x37f;
	_FPU_SETCW(Cw);
	return true;
}();
}
#endif
