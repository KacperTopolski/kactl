/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Read an integer from stdin. Usage requires your program to pipe in
 * input from file.
 * Usage: ./a.out < input.txt
 * Time: About 5x as fast as cin/scanf.
 * Status: tested on SPOJ INTEST, unit tested
 */
#pragma once

inline char gc() { // like getchar()
	static char buf[1 << 16];
	static size_t bc, be;
	if (bc >= be) {
		buf[0] = 0, bc = 0;
		be = fread(buf, 1, sizeof(buf), stdin);
	}
	return buf[bc++]; // returns 0 on EOF
}

int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}

//UWLIB Fast Input

#ifdef ONLINE_JUDGE
// write this when judge is on Windows
inline int getchar_unlocked() { return _getchar_nolock(); }
inline void putchar_unlocked(char c) { _putchar_nolock(c); }
#endif
// BEGIN HASH
int fastin() {
	int n = 0, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	while(isdigit(c)) {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return n;
} // END HASH
// BEGIN HASH
int fastin_negative() {
	int n = 0, negative = false, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	if(c == '-') {
		negative = true;
		c = getchar_unlocked();
	}
	while(isdigit(c)) {
		n = 10 * n + (c - '0');
		c = getchar_unlocked();
	}
	return negative ? -n : n;
} // END HASH
// BEGIN HASH
double fastin_double() {
	double x = 0, t = 1;
	int negative = false, c = getchar_unlocked();
	while(isspace(c))
		c = getchar_unlocked();
	if (c == '-') {
		negative = true;
		c = getchar_unlocked();
	}
	while (isdigit(c)) {
		x = x * 10 + (c - '0');
		c = getchar_unlocked();
	}
	if (c == '.') {
		c = getchar_unlocked();
		while (isdigit(c)) {
			t /= 10;
			x = x + t * (c - '0');
			c = getchar_unlocked();
		}
	}
	return negative ? -x : x;
} // END HASH
// BEGIN HASH
void fastout(int x) {
	if(x == 0) {
		putchar_unlocked('0');
		putchar_unlocked(' ');
		return;
	}
	if(x < 0) {
		putchar_unlocked('-');
		x *= -1;
	}
	static char t[10];
	int i = 0;
	while(x) {
		t[i++] = char('0' + (x % 10));
		x /= 10;
	}
	while(--i >= 0)
		putchar_unlocked(t[i]);
	putchar_unlocked(' ');
}
void nl() { putchar_unlocked('\n'); }
// END HASH
