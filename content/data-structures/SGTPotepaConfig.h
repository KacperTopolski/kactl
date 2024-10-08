/**
 * Author: Krzysztof Potepa
 * Date: 2024
 * Description: Segment tree config.
 */

// Segment tree configurations to be used
// in general_fixed and general_persistent.
// See comments in TREE_PLUS version
// to understand how to create custom ones.
// Capabilities notation: (update; query)

#if TREE_PLUS // (+; sum, max, max count)
	// time: O(lg n)
	using T = int; // Data type for update
	               // operations (lazy tag)
	static constexpr T ID = 0; // Neutral value
	               // for updates and lazy tags

	// This structure keeps aggregated data
	struct Agg {
		// Aggregated data: sum, max, max count
		// Default values should be neutral
		// values, i.e. "aggregate over empty set"
		T sum = 0, vMax = INT_MIN, nMax = 0;
		int cnt = 0; // And node count.

		// Initialize as leaf (single value)
		void leaf() { sum=vMax=0; nMax=cnt=1; }

		// Combine data with aggregated data
		// from node to the right
		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
			sum += r.sum;
			cnt += r.cnt;
		}

		// Apply update provided in `x`:
		// - update aggregated data and `lazy` tag
		// - return 0 if update should branch
		//   (can be used in "segment tree beats")
		// - if you change value of `x` it will be
		//   passed to next node to the right
		//   during updates
		bool apply(T& lazy, T& x) {
			lazy += x;
			sum += x*cnt;
			vMax += x;
			return 1;
		}
	};
#elif TREE_MAX // (max; max, max count)
	// time: O(lg n)
	using T = int;
	static constexpr T ID = INT_MIN;

	struct Agg {
		// Aggregated data: max value, max count
		T vMax = INT_MIN, nMax = 0, cnt = 0;
		void leaf() { vMax = 0; nMax = cnt = 1; }

		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
			cnt += r.cnt;
		}

		bool apply(T& lazy, T& x) {
			if (vMax <= x) nMax = cnt;
			lazy = max(lazy, x);
			vMax = max(vMax, x);
			return 1;
		}
	};
#elif TREE_SET // (=; sum, max, max count)
	// time: O(lg n)
	// Set ID to some unused value.
	using T = int;
	static constexpr T ID = INT_MIN;

	struct Agg {
		// Aggregated data: sum, max, max count
		T sum = 0, vMax = INT_MIN, nMax = 0, cnt=0;
		void leaf() { sum=vMax=0; nMax=cnt=1; }

		void merge(const Agg& r) {
			if (vMax < r.vMax) nMax = r.nMax;
			else if (vMax == r.vMax) nMax += r.nMax;
			vMax = max(vMax, r.vMax);
			sum += r.sum;
			cnt += r.cnt;
		}

		bool apply(T& lazy, T& x) {
			if (x != ID) {
				lazy = x;
				sum = x*cnt;
				vMax = x;
				nMax = cnt;
			}
			return 1;
		}
	};
#elif TREE_BEATS // (+, min; sum, max)
	// time: amortized O(lg n) if not using +
	//       amortized O(lg^2 n) if using +
	// Lazy tag is pair (add, min).
	// To add x: run update with {x, INT_MAX},
	// to min x: run update with {0, x}.
	// If both parts are provided, addition
	// is applied first, then minimum.
	using T = pii;
	static constexpr T ID = {0, INT_MAX};

	struct Agg {
		// Aggregated data: max value, max count,
		//                  second max value, sum
		int vMax = INT_MIN, nMax = 0;
		int max2 = INT_MIN, sum = 0, cnt = 0;
		void leaf() { sum=vMax=0; nMax=cnt=1; }

		void merge(const Agg& r) {
			if (r.vMax > vMax) {
				max2 = vMax;
				vMax = r.vMax;
				nMax = r.nMax;
			} else if (r.vMax == vMax) {
				nMax += r.nMax;
			} else if (r.vMax > max2) {
				max2 = r.vMax;
			}
			max2 = max(max2, r.max2);
			sum += r.sum;
			cnt += r.cnt;
		}

		bool apply(T& lazy, T& x) {
			if (max2 != INT_MIN && max2+x.x >= x.y)
				return 0;
			lazy.x += x.x;
			sum += x.x*cnt;
			vMax += x.x;
			if (max2 != INT_MIN) max2 += x.x;
			if (x.y < vMax) {
				sum -= (vMax-x.y) * nMax;
				vMax = x.y;
			}
			lazy.y = vMax;
			return 1;
		}
	};
#endif