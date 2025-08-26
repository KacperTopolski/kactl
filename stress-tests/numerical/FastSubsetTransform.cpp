#include "../utilities/template.h"

#include "../../content/numerical/FastSubsetTransform.h"

int main() {
	rep(k, 10) {
		vi a(1 << k), b = a, c = a, bruted, got;
		for(int &x : a) x = rand() % 6 - 2;
		for(int &x : b) x = rand() % 6 - 2;

		mode_global = mode_and;
		bruted.assign(1 << k, 0);
		rep(i, 1 << k) rep(j, 1 << k) bruted[i & j] += a[i] * b[j];
		got = conv(a, b);
		assert(bruted == got);

		mode_global = mode_or;
		bruted.assign(1 << k, 0);
		rep(i, 1 << k) rep(j, 1 << k) bruted[i | j] += a[i] * b[j];
		got = conv(a, b);
		assert(bruted == got);

		mode_global = mode_xor;
		bruted.assign(1 << k, 0);
		rep(i, 1 << k) rep(j, 1 << k) bruted[i ^ j] += a[i] * b[j];
		got = conv(a, b);
		assert(bruted == got);
	}
	rep(k, 10) {
		vi a(1 << k), aTr;
		for(int &x : a) x = rand() % 6 - 2;

		aTr = a;
		mode_global = mode_xor;
		FST(aTr, false);

		rep(i, 1 << k) {
			int bruted = singleST(a, i)[4];
			assert(bruted == aTr[i]);
		}
		rep(i, 1 << k) {
			int bruted = singleST(aTr, i)[5];
			assert(bruted == a[i]);
		}

		aTr = a;
		mode_global = mode_and;
		FST(aTr, false);

		rep(i, 1 << k) {
			int bruted = singleST(a, i)[0];
			assert(bruted == aTr[i]);
		}
		rep(i, 1 << k) {
			int bruted = singleST(aTr, i)[1];
			assert(bruted == a[i]);
		}

		aTr = a;
		mode_global = mode_or;
		FST(aTr, false);

		rep(i, 1 << k) {
			int bruted = singleST(a, i)[2];
			if (aTr[i] != bruted) {
				deb(a, aTr, i, bruted);
			}
			assert(bruted == aTr[i]);
		}
		rep(i, 1 << k) {
			int bruted = singleST(aTr, i)[3];
			if (a[i] != bruted) {
				deb(a, aTr, i, bruted);
			}
			assert(bruted == a[i]);
		}
	}
	cout<<"Tests passed!"<<endl;
}
