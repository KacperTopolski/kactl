#include "../utilities/template.h"

#define main main2
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#include "../../content/strings/Hashing-codeforces.h"
#pragma GCC diagnostic pop
#undef main

#include <sys/time.h>
int main() {
	timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec;
	assert((ull)(H(1)*2+1-3) == 0);

	fwd(it,0,10000) {
		int n = rand() % 10;
		int alpha = rand() % 10 + 1;
		string s;
		rep(i,n) s += (char)('a' + rand() % alpha);
		HashInterval hi(s);
		set<string> strs;
		set<ull> hashes;

		// HashInterval
		rep(i,n+1) fwd(j,i,n+1) {
			string sub = s.substr(i, j - i);
			ull hash = (ull) hashString(sub);
			assert((ull) hi.hashInterval(i, j) == hash);
			hashes.insert(hash);
			strs.insert(sub);
		}

		// getHashes
		fwd(le,1,n+1) {
			auto ve = getHashes(s, le);
			assert(sz(ve) == n-le+1);
			rep(i,n-le+1) {
				assert((ull) ve[i] == (ull) hi.hashInterval(i, i + le));
			}
		}

		// No collisions
		assert(sz(strs) == sz(hashes));
	}
	cout<<"Tests passed!"<<endl;
}
