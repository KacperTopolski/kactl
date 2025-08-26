/**
 * Author: teapotd
 * Date: ?
 * License: Unknown
 * Description: ~5x faster on large data. Does NOT include empty suffix (different than logn version).
 * Time: O(n)
 * Status: stress-tested
 */

void countSort(vi& vec, auto key, int k) {
	static vi buf, cnt;
	vec.swap(buf);
	vec.resize(sz(buf));
	cnt.assign(k+1, 0);
	for (auto &e : buf) cnt[key(e)]++;
	fwd(i, 1, k+1) cnt[i] += cnt[i-1];
	for (int i = sz(vec)-1; i >= 0; i--)
		vec[--cnt[key(buf[i])]] = buf[i]; }

// Input values are assumed to be in [1;k]
vi sufArray(vi str, int k) {
	int n = sz(str);
	vi suf(n);
	str.resize(n+15);

	if (n < 15) {
		iota(all(suf), 0);
		rep(j, n) countSort(suf, [&](int i) { return str[i+n-j-1]; }, k);
		return suf;
	}

	vi tmp, code(n+2);
	rep(i, n) if (i % 3) tmp.pb(i);

	rep(j, 3) countSort(tmp, [&](int i) { return str[i-j+2]; }, k);

	int mc = 0, j = -1;

	for (auto &i : tmp) {
		code[i] = mc += (j == -1 ||
				str[i] != str[j] ||
				str[i+1] != str[j+1] ||
				str[i+2] != str[j+2]);
		j = i;
	}

	tmp.clear();
	for (int i=1; i < n; i += 3) tmp.pb(code[i]);
	tmp.pb(0);
	for (int i=2; i < n; i += 3) tmp.pb(code[i]);
	tmp = sufArray(move(tmp), mc);

	vi third;
	int th = (n+4) / 3;
	if (n%3 == 1) third.pb(n-1);

	fwd(i, 1, sz(tmp)) {
		int e = tmp[i];
		tmp[i-1] = (e < th ? e*3+1 : (e-th)*3+2);
		code[tmp[i-1]] = i;
		if (e < th) third.pb(e*3);
	}

	tmp.pop_back();
	countSort(third, [&](int i) { return str[i]; }, k);

	merge(all(third), all(tmp), suf.begin(),
		[&](int l, int r) {
			while (l%3 == 0 || r%3 == 0) {
				if (str[l] != str[r])
					return str[l] < str[r];
				l++; r++;
			}
			return code[l] < code[r];
		});

	return suf; }
vi sufArray(const string& str) {
	return sufArray(vi(all(str)), 255); }
