/**
 * Author: adamant
 * Date: ???
 * License: ???
 * Source: https://judge.yosupo.jp/submission/92308
 * Description: Multiplication over 64-bit nimber field. Nimbers smaller than $2^{2^k}$ form a field.
 * Use fastpow to compute inverses.
 */

using ull = uint64_t;
uint16_t npw[1<<16], nlg[1<<16];

template<int half = 32, bool prec = 0>
ull nimMul(ull a, ull b) { // to invert, use binpow
	if (a < 2 || b < 2) return a * b;
	if (!prec && half <= 8)
		return npw[(nlg[a] + nlg[b]) % 0xFFFF];

	constexpr ull tot = 1ull << half;
	ull c = a % tot, d = a >> half;
	ull e = b % tot, f = b >> half;

	ull p = nimMul<half/2, prec>(c, e);
	ull r = nimMul<half/2, prec>(d, f);
	ull s = nimMul<half/2, prec>(c^d, e^f);
	ull t = nimMul<half/2, prec>(r, tot/2);
	return p ^ t ^ (p ^ s) << half;
}

auto nimInit = [](){
	fwd(i, npw[0] = 1, 0xFFFF) {
		ull v = nimMul<16, 1>(npw[i-1], -1);
		nlg[npw[i] = uint16_t(v)] = uint16_t(i);
	}
	return 0;
}();
