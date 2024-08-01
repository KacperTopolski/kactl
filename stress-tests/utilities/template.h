#include <bits/stdc++.h>
using namespace std;

#define fwd(i, from, to) for (int i = (from); i < (to); ++i)
#define rep(i,n) fwd(i,0,n)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define st first
#define nd second

auto &operator<<(auto &out, pair<auto, auto> a) { return out << "(" << a.st << ", " << a.nd << ")"; }
auto &operator<<(auto &out, auto a) {
   out << "{";
   for (auto b : a)
      out << b << ", ";
   return out << "}";
}
void dump(auto... x) { ((cerr << x << ", "), ...) << '\n'; }
#define debug(x...) cerr << __LINE__ << " [" #x "]: ", dump(x)
