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

// WSL1 is broken, remove once nobody in the team uses WSL1
#if __has_include (<fpu_control.h>)
#include <fpu_control.h>
namespace wsl {
auto is_wsl = [](){
    ifstream stream("/proc/version");
    string str;
    getline(stream, str);
    for (char &ch : str)
        ch = tolower((unsigned char) ch);
    if (str.find("microsoft") == string::npos)
        return false;
    unsigned short Cw = 0x37f;
    _FPU_SETCW(Cw);
    return true;
}();
}
#endif
