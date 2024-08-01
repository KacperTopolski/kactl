#include "../utilities/template.h"

#include "../../content/geometry/Point.h"

namespace new_int {
using T = ll; //comparing slopes etc
using P = Point<T>; //only cross needed
using SuperT = __int128_t; //computing intersections
const SuperT EPS = 1e-12; //|pts| <= 10^6 for floats, |pts| <= 10^9 for ll

struct Line { //coords <= 10^9 for abc constructor and <= 10^6 for p,q
	T a,b,c;
	Line(T a_=0, T b_=0, T c_=0): a(a_), b(b_), c(c_) {} //ax + by + c >= 0
	Line(P p, P q): a(p.y-q.y), b(q.x-p.x), c(p.cross(q)) {} //p->q ccw
	Line operator- () const {return Line(-a, -b, -c); }
	bool up() const { return a?(a<0):(b>0);}
	P v() const {return P(a,b);}
	P vx() {return P(b,c);} P vy() {return P(a,c);}
	T wek(Line p) const {return v().cross(p.v());}
	bool operator<(Line b) const {
		if (up() != b.up()) return up() > b.up();
		return wek(b) > 0;
	}
};
bool parallel(Line a, Line b) {return !a.wek(b);}
bool same(Line a, Line b) {
	return parallel(a,b) && !a.vy().cross(b.vy()) && !a.vx().cross(b.vx());
}
T weaker (Line a, Line b) {
	if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) - b.c*abs(a.a);
	return a.c*abs(b.b) - b.c*abs(a.b);
}
array<SuperT, 3> intersect(Line a, Line b) {
	SuperT det = a.wek(b);
	SuperT x = a.vx().cross(b.vx());
	SuperT y = a.vy().cross(b.vy());
	// if (T is floating point) return {x / det, -y / det, 1.0};
	if (det > 0) return {x, -y, det};
	return {-x, y, -det};
}
struct HPI {
	bool empty=0, pek=0;
	set<Line> s;
	typedef set<Line>::iterator iter;
	iter next(iter it){return ++it == s.end() ? s.begin() : it;}
	iter prev(iter it){return it == s.begin() ? --s.end() : --it;}
	bool hide(Line a, Line b, Line c) { // do a,b hide c?
		if (parallel(a,b)) {
			if (weaker(a, -b) < 0) empty = 1;
			return 0;
		}
		if (a.wek(b) < 0) swap(a,b);
		auto [rx, ry, rdet] = intersect(a,b);
		auto v = rx*c.a + ry*c.b + rdet*c.c;
		if (a.wek(c) >=0  && c.wek(b) >=0 && v >= -EPS) return 1;
		if (a.wek(c) < 0  && c.wek(b) < 0) {
			if (v < -EPS) empty = 1;
			else if (v <= EPS) pek = 1;
		}
		return 0;
	}
	void delAndMove(iter& i, int nxt) {
		iter j = i;
		if(nxt==1) i = next(i);
		else i = prev(i);
		s.erase(j);
	}
	void add(Line l) {
		if (empty) return;
		if (l.a == 0 && l.b == 0) {
			if (l.c < 0) empty = 1;
			return;
		}
		iter it = s.lower_bound(l);  //parallel
		if(it != s.end() && parallel(*it, l) && it->up() == l.up()) {
			if (weaker(l, *it)>=0) return;
			delAndMove(it,1);
		}
		if(it == s.end()) it = s.begin(); //*it>p
		while(sz(s) >= 2 && hide(l, *next(it), *it))
			delAndMove(it,1);
		if(sz(s)) it = prev(it); //*it<p
		while(sz(s) >= 2 && hide(l, *prev(it), *it))
			delAndMove(it,0);
		if(sz(s) < 2 || !hide(*it, *next(it), l)) s.insert(l);
	}
	int type() { //0 = empty, 1=point, 2=segment, 3=halfline
		if(empty) return 0; //4=line, 5=polygon or unbounded
		if(sz(s) <= 4){
			vector<Line> r(all(s));
			if(sz(r) == 2 && parallel(r[0], r[1]) && weaker(r[0],-r[1])<0)
				return 0;
			rep(i, sz(r)) rep(j, i) if(same(r[i], r[j])) {
				if(sz(r) == 2) return 4;	if(sz(r) == 3) return 3;
				if(sz(r) == 4 && same(r[0], r[2]) && same(r[1], r[3])) return 1;
				return 2;
			}
			if(sz(r) == 3 && pek) return 1;
		}
		return 5;
	}
};
}
namespace new_dbl {
using T = double; //comparing slopes etc
using P = Point<T>; //only cross needed
using SuperT = long double; //computing intersections
const SuperT EPS = 1e-12; //|pts| <= 10^6 for floats, |pts| <= 10^9 for ll

struct Line { //coords <= 10^9 for abc constructor and <= 10^6 for p,q
	T a,b,c;
	Line(T a_=0, T b_=0, T c_=0): a(a_), b(b_), c(c_) {} //ax + by + c >= 0
	Line(P p, P q): a(p.y-q.y), b(q.x-p.x), c(p.cross(q)) {} //p->q ccw
	Line operator- () const {return Line(-a, -b, -c); }
	bool up() const { return a?(a<0):(b>0);}
	P v() const {return P(a,b);}
	P vx() {return P(b,c);} P vy() {return P(a,c);}
	T wek(Line p) const {return v().cross(p.v());}
	bool operator<(Line b) const {
		if (up() != b.up()) return up() > b.up();
		return wek(b) > 0;
	}
};
bool parallel(Line a, Line b) {return !a.wek(b);}
bool same(Line a, Line b) {
	return parallel(a,b) && !a.vy().cross(b.vy()) && !a.vx().cross(b.vx());
}
T weaker (Line a, Line b) {
	if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) - b.c*abs(a.a);
	return a.c*abs(b.b) - b.c*abs(a.b);
}
array<SuperT, 3> intersect(Line a, Line b) {
	SuperT det = a.wek(b);
	SuperT x = a.vx().cross(b.vx());
	SuperT y = a.vy().cross(b.vy());
	return {x / det, -y / det, 1.0};
	if (det > 0) return {x, -y, det};
	return {-x, y, -det};
}
struct HPI {
	bool empty=0, pek=0;
	set<Line> s;
	typedef set<Line>::iterator iter;
	iter next(iter it){return ++it == s.end() ? s.begin() : it;}
	iter prev(iter it){return it == s.begin() ? --s.end() : --it;}
	bool hide(Line a, Line b, Line c) { // do a,b hide c?
		if (parallel(a,b)) {
			if (weaker(a, -b) < 0) empty = 1;
			return 0;
		}
		if (a.wek(b) < 0) swap(a,b);
		auto [rx, ry, rdet] = intersect(a,b);
		auto v = rx*c.a + ry*c.b + rdet*c.c;
		if (a.wek(c) >=0  && c.wek(b) >=0 && v >= -EPS) return 1;
		if (a.wek(c) < 0  && c.wek(b) < 0) {
			if (v < -EPS) empty = 1;
			else if (v <= EPS) pek = 1;
		}
		return 0;
	}
	void delAndMove(iter& i, int nxt) {
		iter j = i;
		if(nxt==1) i = next(i);
		else i = prev(i);
		s.erase(j);
	}
	void add(Line l) {
		if (empty) return;
		if (l.a == 0 && l.b == 0) {
			if (l.c < 0) empty = 1;
			return;
		}
		iter it = s.lower_bound(l);  //parallel
		if(it != s.end() && parallel(*it, l) && it->up() == l.up()) {
			if (weaker(l, *it)>=0) return;
			delAndMove(it,1);
		}
		if(it == s.end()) it = s.begin(); //*it>p
		while(sz(s) >= 2 && hide(l, *next(it), *it))
			delAndMove(it,1);
		if(sz(s)) it = prev(it); //*it<p
		while(sz(s) >= 2 && hide(l, *prev(it), *it))
			delAndMove(it,0);
		if(sz(s) < 2 || !hide(*it, *next(it), l)) s.insert(l);
	}
	int type() { //0 = empty, 1=point, 2=segment, 3=halfline
		if(empty) return 0; //4=line, 5=polygon or unbounded
		if(sz(s) <= 4){
			vector<Line> r(all(s));
			if(sz(r) == 2 && parallel(r[0], r[1]) && weaker(r[0],-r[1])<0)
				return 0;
			rep(i, sz(r)) rep(j, i) if(same(r[i], r[j])) {
				if(sz(r) == 2) return 4;	if(sz(r) == 3) return 3;
				if(sz(r) == 4 && same(r[0], r[2]) && same(r[1], r[3])) return 1;
				return 2;
			}
			if(sz(r) == 3 && pek) return 1;
		}
		return 5;
	}
};
}
namespace old_int {
typedef long long T; //comparing slopes etc
typedef Point<T> P; //only cross needed
typedef long double ld; // computing intersections
const ld EPS = 1e-12; //works for |pts| <= 10^6

struct Line { //coords <= 10^9 for abc constructor and <= 10^6 for p,q
	T a,b,c;
	Line(T a_=0, T b_=0, T c_=0): a(a_), b(b_), c(c_) {} //ax + by + c >= 0
	Line(P p, P q): a(p.y-q.y), b(q.x-p.x), c(p.cross(q)) {} //p->q ccw
	Line operator- () const {return Line(-a, -b, -c); }
	bool up() const { return a?(a<0):(b>0);}
	P v() const {return P(a,b);}
	P vx() {return P(b,c);} P vy() {return P(a,c);}
	T wek(Line p) const {return v().cross(p.v());}
	bool operator<(Line b) const {
		if (up() != b.up()) return up() > b.up();
		return wek(b) > 0;
	}
};
bool parallel(Line a, Line b) {return !a.wek(b);}
bool same(Line a, Line b) {
	return parallel(a,b) && !a.vy().cross(b.vy()) && !a.vx().cross(b.vx());
}
T weaker (Line a, Line b) {
	if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) - b.c*abs(a.a);
	return a.c*abs(b.b) - b.c*abs(a.b);
}
Point<ld> intersect(Line a, Line b) {
	ld det = a.wek(b);
	T x = a.vx().cross(b.vx());
	T y = a.vy().cross(b.vy());
	return Point<ld>(x/det,-y/det);
}
struct HPI {
	bool empty=0, pek=0;
	set<Line> s;
	typedef set<Line>::iterator iter;
	iter next(iter it){return ++it == s.end() ? s.begin() : it;}
	iter prev(iter it){return it == s.begin() ? --s.end() : --it;}
	bool hide(Line a, Line b, Line c) { // do a,b hide c?
		if (parallel(a,b)) {
			if (weaker(a, -b) < 0) empty = 1;
			return 0;
		}
		if (a.wek(b) < 0) swap(a,b);
		auto r = intersect(a,b);
		ld v = r.x*c.a + r.y*c.b + c.c;
		if (a.wek(c) >=0  && c.wek(b) >=0 && v > -EPS) return 1;
		if (a.wek(c) < 0  && c.wek(b) < 0) {
			if (v < -EPS) empty = 1;
			else if (v < EPS) pek = 1;
		}
		return 0;
	}
	void delAndMove(iter& i, int nxt) {
		iter j = i;
		if(nxt==1) i = next(i);
		else i = prev(i);
		s.erase(j);
	}
	void add(Line l) {
		if (empty) return;
		if (l.a == 0 && l.b == 0) {
			if (l.c < 0) empty = 1;
			return;
		}
		iter it = s.lower_bound(l);  //parallel
		if(it != s.end() && parallel(*it, l) && it->up() == l.up()) {
			if (weaker(l, *it)>=0) return;
			delAndMove(it,1);
		}
		if(it == s.end()) it = s.begin(); //*it>p
		while(sz(s) >= 2 && hide(l, *next(it), *it))
			delAndMove(it,1);
		if(sz(s)) it = prev(it); //*it<p
		while(sz(s) >= 2 && hide(l, *prev(it), *it))
			delAndMove(it,0);
		if(sz(s) < 2 || !hide(*it, *next(it), l)) s.insert(l);
	}
	int type() { //0 = empty, 1=point, 2=segment, 3=halfline
		if(empty) return 0; //4=line, 5=polygon or unbounded
		if(sz(s) <= 4){
			vector<Line> r(all(s));
			if(sz(r) == 2 && parallel(r[0], r[1]) && weaker(r[0],-r[1])<0)
				return 0;
			rep(i, sz(r)) rep(j, i) if(same(r[i], r[j])) {
				if(sz(r) == 2) return 4;	if(sz(r) == 3) return 3;
				if(sz(r) == 4 && same(r[0], r[2]) && same(r[1], r[3])) return 1;
				return 2;
			}
			if(sz(r) == 3 && pek) return 1;
		}
		return 5;
	}
};
}
namespace old_dbl {
typedef double T; //comparing slopes etc
typedef Point<T> P; //only cross needed
typedef long double ld; // computing intersections
const ld EPS = 1e-12; //works for |pts| <= 10^6

struct Line { //coords <= 10^9 for abc constructor and <= 10^6 for p,q
	T a,b,c;
	Line(T a_=0, T b_=0, T c_=0): a(a_), b(b_), c(c_) {} //ax + by + c >= 0
	Line(P p, P q): a(p.y-q.y), b(q.x-p.x), c(p.cross(q)) {} //p->q ccw
	Line operator- () const {return Line(-a, -b, -c); }
	bool up() const { return a?(a<0):(b>0);}
	P v() const {return P(a,b);}
	P vx() {return P(b,c);} P vy() {return P(a,c);}
	T wek(Line p) const {return v().cross(p.v());}
	bool operator<(Line b) const {
		if (up() != b.up()) return up() > b.up();
		return wek(b) > 0;
	}
};
bool parallel(Line a, Line b) {return !a.wek(b);}
bool same(Line a, Line b) {
	return parallel(a,b) && !a.vy().cross(b.vy()) && !a.vx().cross(b.vx());
}
T weaker (Line a, Line b) {
	if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) - b.c*abs(a.a);
	return a.c*abs(b.b) - b.c*abs(a.b);
}
Point<ld> intersect(Line a, Line b) {
	ld det = a.wek(b);
	T x = a.vx().cross(b.vx());
	T y = a.vy().cross(b.vy());
	return Point<ld>(x/det,-y/det);
}
struct HPI {
	bool empty=0, pek=0;
	set<Line> s;
	typedef set<Line>::iterator iter;
	iter next(iter it){return ++it == s.end() ? s.begin() : it;}
	iter prev(iter it){return it == s.begin() ? --s.end() : --it;}
	bool hide(Line a, Line b, Line c) { // do a,b hide c?
		if (parallel(a,b)) {
			if (weaker(a, -b) < 0) empty = 1;
			return 0;
		}
		if (a.wek(b) < 0) swap(a,b);
		auto r = intersect(a,b);
		ld v = r.x*c.a + r.y*c.b + c.c;
		if (a.wek(c) >=0  && c.wek(b) >=0 && v > -EPS) return 1;
		if (a.wek(c) < 0  && c.wek(b) < 0) {
			if (v < -EPS) empty = 1;
			else if (v < EPS) pek = 1;
		}
		return 0;
	}
	void delAndMove(iter& i, int nxt) {
		iter j = i;
		if(nxt==1) i = next(i);
		else i = prev(i);
		s.erase(j);
	}
	void add(Line l) {
		if (empty) return;
		if (l.a == 0 && l.b == 0) {
			if (l.c < 0) empty = 1;
			return;
		}
		iter it = s.lower_bound(l);  //parallel
		if(it != s.end() && parallel(*it, l) && it->up() == l.up()) {
			if (weaker(l, *it)>=0) return;
			delAndMove(it,1);
		}
		if(it == s.end()) it = s.begin(); //*it>p
		while(sz(s) >= 2 && hide(l, *next(it), *it))
			delAndMove(it,1);
		if(sz(s)) it = prev(it); //*it<p
		while(sz(s) >= 2 && hide(l, *prev(it), *it))
			delAndMove(it,0);
		if(sz(s) < 2 || !hide(*it, *next(it), l)) s.insert(l);
	}
	int type() { //0 = empty, 1=point, 2=segment, 3=halfline
		if(empty) return 0; //4=line, 5=polygon or unbounded
		if(sz(s) <= 4){
			vector<Line> r(all(s));
			if(sz(r) == 2 && parallel(r[0], r[1]) && weaker(r[0],-r[1])<0)
				return 0;
			rep(i, sz(r)) rep(j, i) if(same(r[i], r[j])) {
				if(sz(r) == 2) return 4;	if(sz(r) == 3) return 3;
				if(sz(r) == 4 && same(r[0], r[2]) && same(r[1], r[3])) return 1;
				return 2;
			}
			if(sz(r) == 3 && pek) return 1;
		}
		return 5;
	}
};
}

struct HPI {
    bool useInt;
    HPI(bool u) : useInt(u) {}
    new_int::HPI hpi1;
    old_int::HPI hpi2;
    new_dbl::HPI hpi3;
    old_dbl::HPI hpi4;

    void add(double a, double b, double c) {
        if (useInt) {
            hpi1.add(new_int::Line(a, b, c));
            hpi2.add(old_int::Line(a, b, c));
        }
        hpi3.add(new_dbl::Line(a, b, c));
        hpi4.add(old_dbl::Line(a, b, c));
    }

    int uniq(vector<int> v) {
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        return sz(v);
    }

    int type(bool &ok) {
        vector<int> types, sides, empty;
        if (useInt) {
            types.push_back(hpi1.type());
            types.push_back(hpi2.type());
            sides.push_back(sz(hpi1.s));
            sides.push_back(sz(hpi2.s));
        }
        types.push_back(hpi3.type());
        types.push_back(hpi4.type());
        sides.push_back(sz(hpi3.s));
        sides.push_back(sz(hpi4.s));
        for (int i : types)
            empty.push_back(!i);
        // debug(types, sides, empty);
        ok &= uniq(empty) == 1;
        // ok &= uniq(types) == 1;
        // ok &= uniq(sides) == 1;
        return *types.begin();
    }
};

void test_special() {
    for (int i = 0; 20*i < int(1e5); ++i) {
        bool test_ok = true;
        HPI hpi(true);
        hpi.add(17*i, -11*i, -5*i);
        hpi.add(-18*i, 12*i, -10*i);
        hpi.add(-16*i, 10*i, 20*i);
        hpi.type(test_ok);
        if (!test_ok) {
            debug(i, 20*i);
            assert(false);
        }
    }
}

void test_int() {
    vector<pii> params;
    for (int dist : {2, 5, 10})
        for (int range : {500, 1000, 2000, 5000, 10000, 100000})
            if (range % dist == 0)
                params.emplace_back(dist, range*10);

    rep(seed, 1e6) {
        auto [dist, range] = params[seed % sz(params)];
        mt19937_64 rnd(seed);
        uniform_int_distribution<int> unif(-dist, dist);
        auto gen = [&]() {return unif(rnd) * range / dist; };

        bool test_ok = true;
        HPI hpi(true);
        while (hpi.type(test_ok) && test_ok) {
            int a = gen(), b = gen(), c = gen();
            hpi.add(a, b, c);
        }
        if (!test_ok) {
            debug(seed, dist, range);
            assert(false);
        }
    }
}
void test_float() {
    rep(seed, 1e6) {
        mt19937_64 rnd(seed);
        uniform_real_distribution<double> unif(-1e6, 1e6);
        auto gen = [&](){return unif(rnd); };

        bool test_ok = true;
        HPI hpi(false);
        while (hpi.type(test_ok) && test_ok) {
            double a = gen(), b = gen(), c = gen();
            hpi.add(a, b, c);
        }
        if (!test_ok) {
            debug(seed);
            assert(false);
        }
    }
}

int main() {
    test_special();
    test_int();
    test_float();
    cout<<"Tests passed!"<<endl;
}
