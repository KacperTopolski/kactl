#include "../utilities/template.h"

#include "../../content/strings/Monge.h"
#include "../../content/various/LIS.h"

mt19937 rnd;
int main() {
    rep(_, 10) {
        int n = 50;
        vi v(n);
        rep(i, n) v[i] = int(rnd() % 20);

        ALIS alis(v);

        rep(l, n) rep(r, n) if (l <= r) {
            vi hereV(v.begin() + l, v.begin() + r + 1);
            auto br = lis(hereV);
            int ans_monge = alis(l, r + 1);
            // deb(l, r, hereV, br, ans_monge);
            assert(sz(br) == ans_monge);
        }
    }
    cout<<"Tests passed!"<<endl;
}
