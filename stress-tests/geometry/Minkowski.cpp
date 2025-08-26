#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
#include "../../content/geometry/Minkowski.h"

vector<P> convexPoly() {
	static mt19937 rnd;
	vector<P> poly;
	rep(_, 300)
		poly.emplace_back(rnd() / 1000, rnd() / 1000);
	return convexHull(poly);
}

int main() {
	rep(_, 10000) {
		vector<P> a = convexPoly(), b = convexPoly(), c;
		for (auto x : a) for (auto y : b)
			c.push_back(x + y);
		vector<P> bruted = convexHull(c), minkowski = hullSum(a, b);
		rotate(minkowski.begin(), min_element(all(minkowski)), minkowski.end());
		assert(bruted == minkowski);
	}
	cerr<<"do you really need so much in Angle.h?"<<endl;
	cout<<"Tests passed!"<<endl;
}
