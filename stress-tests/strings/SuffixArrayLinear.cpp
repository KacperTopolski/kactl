#include "../utilities/template.h"

#include "../../content/strings/SuffixArray.h"
#include "../../content/strings/SuffixArrayLinear.h"

void compare(string s) {
	SuffixArray slow(s);
	auto sa = sufArray(s);

	slow.sa.erase(slow.sa.begin());
	if (slow.sa != sa) {
		deb(slow.sa);
		deb(sa);
		assert(false);
	}
}

mt19937_64 rnd;
string random_gen(int n, int k) {
	string out(n, 'a');
	for (char &ch : out) ch += rnd() % k;
	return out;
}

int main() {
	compare("abab");

	fwd(k, 1, 10) {
		rep(n, 1000) {
			string here = random_gen(n, k);
			compare(here);
		}
		rep(n, 10) rep(_, 10000) {
			string here = random_gen(n, k);
			compare(here);
		}
	}

	cout<<"Tests passed!"<<endl;
}
