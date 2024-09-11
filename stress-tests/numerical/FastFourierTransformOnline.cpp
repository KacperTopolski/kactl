#include "../utilities/template.h"

#include "../../content/numerical/FastFourierTransformOnline.h"

int main() {
	const int n = 10000;
	auto h = example(n);

	fwd(i, 1, n) {
		ll x = 1;
		fwd(j, 1, i)
			x += h[j] * j % mod * h[i-j] % mod * modpow(i-j, mod-2) % mod;
		assert(h[i] == x % mod);
	}

	cout<<"Tests passed!"<<endl;
}
