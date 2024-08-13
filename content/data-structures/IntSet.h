/**
 * Author: Czaj Nik
 * Date: ????
 * License: N/A
 * Description: bitset with fast predecessor and successor queries. Assumes x86 shift overflows. Extremely fast (50-200mln operations in 1 second).
 * Status: Tested on yosupo judge
 */
template<int N>
struct IntSet {
	static constexpr int B = 64;
	uint64_t V[N / B + 1] = {};
	IntSet<(N < B + 1 ? 0 : N / B + 1)> up;
	bool has(int i) { return (V[i / B] >> i) & 1; }
	void add(int i) { 
		if (!V[i / B]) up.add(i / B);
		V[i / B] |= 1ull << i;
	}
	void del(int i) {
		if (!(V[i / B] &= ~(1ull << i))) up.del(i / B);
	}
	int next(int i) { // j > i such that j inside or -1
		auto x = V[i / B] >> i;
		if (x &= ~1) return i + __builtin_ctzll(x);
		return (i = up.next(i / B)) < 0 ? i :
			i * B + __builtin_ctzll(V[i]);
	}
	int prev(int i) { // j < i such that j inside or -1
		auto x = V[i / B] << (B - i - 1);
		if (x &= INT64_MAX)
			return i-__builtin_clzll(x);
		return (i = up.prev(i / B)) < 0 ? i :
			i * B + B - 1 - __builtin_clzll(V[i]);
	}
};
template<>
struct IntSet<0> {
	void add(int) {} void del(int) {}
	int next(int) { return -1; }
	int prev(int) { return -1; } };