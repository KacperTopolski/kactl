#include "../utilities/template.h"

#include "../../content/combinatorial/DeBruijn.h"

int main() {
    fwd(k, 1, 6) fwd(n, 1, 6) {
        int k_pow_n = int(0.5 + pow(k, n));

        // deb(k,n,k_pow_n);
        vi word = dseq(k, n);
        assert(sz(word) == k_pow_n);

        rep(i, n) word.pb(word[i]);
        set<vi> substrs;

        rep(i, k_pow_n) {
            vi here{word.begin() + i, word.begin() + i + n};
            substrs.insert(here);
        }

        assert(sz(substrs) == k_pow_n);
    }
	cout<<"Tests passed!"<<endl;
}
