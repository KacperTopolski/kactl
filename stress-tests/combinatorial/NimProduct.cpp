#include "../utilities/template.h"
#include "../utilities/bench.h"

#include "../../content/combinatorial/NimProduct.h"

namespace NimProductOld {
/**
 * Author: Andrew He
 * Description: Nim Product.
 */
using ull = uint64_t;
ull _nimProd2[64][64];
ull nimProd2(int i, int j) {
	if (_nimProd2[i][j]) return _nimProd2[i][j];
	if ((i & j) == 0) return _nimProd2[i][j] = 1ull << (i|j);
	int a = (i&j) & -(i&j);
	return _nimProd2[i][j] = nimProd2(i ^ a, j) ^ nimProd2((i ^ a) | (a-1), (j ^ a) | (i & (a-1)));
}
ull nimProd(ull x, ull y) {
	ull res = 0;
	for (int i = 0; i < 64 && (x >> i); i++)
		if ((x >> i) & 1)
			for (int j = 0; j < 64 && (y >> j); j++)
				if ((y >> j) & 1)
					res ^= nimProd2(i, j);
	return res;
}
}

ull nimExp(ull x, ull e) {
	ull r = 1;
	while (e) {
		if (e & 1)
			r = nimMul(r, x);
		x = nimMul(x, x);
		e /= 2;
	}
	return r;
}

bool isGenerator(ull x, const vector<ull> &divs) {
	ull s = 1;
	for (ull p : divs) s *= p;
	assert(nimExp(x, s) == 1);
	for (ull p : divs)
		if (nimExp(x, s / p) == 1)
			return false;
	return true;
}

int main() {
	mt19937_64 rnd;

	const int T = 2e5;
	vector<ull> a(T), b(T), xOld(T), xNew(T);

	rep(i, T) {
		a[i] = rnd();
		b[i] = rnd();
	}
	rep(i, 100 * 100) {
		a[i] = i % 100;
		b[i] = i / 100;
	}

	{
		// timeit ti("old nim mul"); // ~440ms
		rep(i, T) xOld[i] = NimProductOld::nimProd(a[i], b[i]);
	}
	{
		// timeit ti("new nim mul"); // ~5ms
		rep(i, T) xNew[i] = nimMul(a[i], b[i]);
	}

	assert(xOld == xNew);

	/*const vector<ull> factor64 = {3, 5, 17, 257, 641, 65537, 6700417};
	const vector<ull> factor32 = {3, 5, 17, 257, 65537};
	const vector<ull> factor16 = {3, 5, 17, 257};
	const vector<ull> factor8 = {3, 5, 17};

	ull g = (1ull << 32) + 6;
	assert(isGenerator(g, factor64));

	deb(nimExp(g, 641LL * 6700417));

	rep(g, 100) {
		bool a = isGenerator((1ull << 32) + g, factor64);
		bool b = isGenerator((1ull << 16) + g, factor32);
		bool c = isGenerator((1ull << 8) + g, factor16);
		bool d = isGenerator((1ull << 4) + g, factor8);
		if (a && b && c && d)
			deb(g);
	}*/

	cout<<"Tests passed!"<<endl;
}
