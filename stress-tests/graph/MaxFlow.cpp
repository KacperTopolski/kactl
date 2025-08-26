#include "../utilities/template.h"
#include "../utilities/random.h"

namespace PushRelabel {
#include "../../content/graph/PushRelabel.h"
}
namespace PushRelabelKactl {
#include "../../content/graph/PushRelabelKactl.h"
}
namespace Dinic {
#include "../../content/graph/Dinic.h"
}
namespace EdmondsKarp {
#include "../../content/graph/EdmondsKarp.h"
}

template <typename MaxFlow>
ll test(int n, int s, int t, vector<array<ll, 4>> eds) {
	MaxFlow net(n);
	for (auto [x, y, f, rf] : eds) {
		net.addEdge((int)x, (int)y, f, rf);
	}
	ll flo = net.maxFlow(s, t), acrossCut = 0;

	for (auto [x, y, f, rf] : eds) rep(_, 2) {
		if (net.leftOfMinCut((int)x) && !net.leftOfMinCut((int)y))
			acrossCut += f;

		swap(x, y);
		swap(f, rf);
	}

	assert(flo == acrossCut);
	return flo;
}

const ll MX = 1e10;

int main() {
	rep(it, 10) fwd(n, 2, 150) rep(mul, 10) rep(hasrf, 2) {
		mt19937 rnd{(long unsigned int)(it * 156 + n * 1516 + mul * 2322)};

		auto rand_pair = [&]() -> pii {
			int x = 0, y = 0;
			while (x == y) tie(x, y) = pii{rnd() % n, rnd() % n};
			return {x, y};
		};

		auto [s, t] = rand_pair();
		vector<array<ll, 4>> eds((mul + 1) * n);
		for (auto &[x, y, f, rf] : eds) {
			tie(x, y) = rand_pair();
			f = rnd() % MX;
			if (hasrf) rf = rnd() % MX;
		}

		auto x1 = test<PushRelabel::PushRelabel>(n, s, t, eds);
		auto x2 = test<PushRelabelKactl::PushRelabel>(n, s, t, eds);
		auto x3 = test<Dinic::Dinic>(n, s, t, eds);
		auto x4 = test<EdmondsKarp::EdmondsKarp>(n, s, t, eds);

		if (x1 != x2 || x2 != x3 || x3 != x4) {
			deb(x1, x2, x3, x4);
			exit(-1);
		}
	}

	cerr << "todo testy dla demandsów" << endl;
	cout << "Tests passed!" << endl;
}
