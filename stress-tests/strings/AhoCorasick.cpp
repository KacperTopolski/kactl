#include "../utilities/template.h"
#include "../../content/strings/AhoCorasick.h"

#define trav(a, x) for (auto& a : x)

template<class F>
void gen(string& s, int at, int alpha, F f) {
	if (at == sz(s)) f();
	else {
		rep(i,alpha) {
			s[at] = (char)('a' + i);
			gen(s, at+1, alpha, f);
		}
	}
}

void test(const string& s) {
	vector<string> pats;
	string cur;
	rep(i,sz(s)) {
		if (s[i] == 'a') {
			pats.push_back(cur);
			cur = "";
		}
		else cur += s[i];
	}

	string hay = cur;
	trav(x, pats) if (x.empty()) return;
	Aho aho;
	rep(j, sz(pats)) aho.add(pats[j], j);
	aho.build();

	vector<vi> positions(sz(hay));
	int state = 0;

	// This test does not work for empty string. Too bad.
	rep(i, sz(hay)) {
		state = aho.next(state, hay[i]);
		aho.accepted(state, [&](int j) {
			positions[i + 1 - sz(pats[j])].pb(j);
			return false;
		});
	}

	vi ord;
	rep(i,sz(hay)) {
		ord.clear();
		rep(j,sz(pats)) {
			string& pat = pats[j];
			if (hay.substr(i, pat.size()) == pat) {
				ord.push_back(j);
			}
		}
		sort(all(positions[i]));

		if (positions[i] != ord) {
			cerr << "failed!" << endl;
			cerr << hay << endl;
			trav(x, pats) cerr << x << endl;
			cerr << "failed at position " << i << endl;
			cerr << "got:" << endl;
			trav(x, positions[i]) cerr << x << ' ';
			cerr << endl;
			cerr << "expected:" << endl;
			trav(x, ord) cerr << x << ' ';
			cerr << endl;
			abort();
		}
	}
}

int main() {
	// test ~4^10 strings
	rep(n,11) {
		string s(n, 'x');
		gen(s, 0, 4, [&]() {
			test(s);
		});
	}
	// then ~5^7
	rep(n,8) {
		string s(n, 'x');
		gen(s, 0, 5, [&]() {
			test(s);
		});
	}
	cout<<"Tests passed!"<<endl;
}
