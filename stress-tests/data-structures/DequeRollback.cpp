#include "../utilities/template.h"

#include "../../content/data-structures/DequeRollback.h"
#include "../../content/data-structures/UnionFind.h"

int main() {
    mt19937 rnd{21};
    rep(_, 15) {
        const int n = 15, m = 25;

        DequeUndo dq;
        dq.ds.ds = RollbackUF(n);
        vector<pii> edges(m), to_test;
        for (auto &[a, b] : edges) {
            a = int(rnd() % n);
            b = int(rnd() % n);
        }

        rep(l, m) rep(r, m) if (l <= r)
            to_test.eb(l, r);
        shuffle(all(to_test), rnd);
        // deb(edges);
        // deb(to_test);

        int L = 0, R = -1;
        for (auto [l, r] : to_test) {
            while (L > l) {
                --L;
                dq.push(edges[L], 0);
            }
            while (R < r) {
                ++R;
                dq.push(edges[R], 1);
            }
            while (L < l) {
                ++L;
                dq.pop(0);
            }
            while (R > r) {
                --R;
                dq.pop(1);
            }

            UF uf(n);
            fwd(i, l, r + 1) {
                // deb(i,l,r);
                auto [a, b] = edges[i];
                uf.join(a, b);
            }

            rep(i, n) rep(j, n) {
                bool s1 = dq.ds.ds.find(i) == dq.ds.ds.find(j);
                bool s2 = uf.find(i) == uf.find(j);
                // deb(i,j,s1);
                assert(s1 == s2);
            }
            rep(i, n) {
                int s1 = dq.ds.ds.size(i);
                int s2 = uf.size(i);
                assert(s1 == s2);
            }
        }
    }

	cout<<"Tests passed!"<<endl;
}
