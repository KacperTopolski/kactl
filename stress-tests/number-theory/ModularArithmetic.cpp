#include "../utilities/template.h"

#include "../../content/number-theory/ModularArithmetic.h"

int main() {
	rep(a,mod) fwd(b,1,mod) {
		Mod ma(a);
		Mod mb(b);
		Mod mc = ma / mb;
		assert((mc * mb).x == a);
	}
	Mod a = 2;
	ll cur=1;
	rep(i, 17) {
		assert((a.pow(i)).x == cur);
		cur = (cur * 2) % mod;
	}
	cout<<"Tests passed!"<<endl;
}
