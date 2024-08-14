#include "../utilities/template.h"

#include "../../content/data-structures/RMQ.h"

int main() {
	clock_t start = clock();
	clock_t start_preprocessing = clock();
	mt19937 rng(2137);
	auto rnd = [&] (int l, int r) {
		return uniform_int_distribution<int>(l, r)(rng);
	};
	const int N = 2 * 1000 * 1000;
	const int Q = 10 * 1000 * 1000;
	const int THR = 64;
	vector<pii> short_queries(Q);
	vector<pii> long_queries(Q);
	auto rnd_query = [&] () {
		int l = rnd(0, N - 1);
		int r = rnd(0, N - 1);
		if (l > r) swap(l, r);
		return make_pair(l, r);
	};
	auto long_rnd_query = [&] {
		pii query = rnd_query();
		while (query.nd - query.st + 1 < THR) {
			query = rnd_query();
		}
		return query;
	};
	auto short_rnd_query = [&] () {
		int l = rnd(0, N - 1);
		int r = rnd(l, min(N - 1, l + THR - 2));
		return make_pair(l, r);
	};
	rep(i, Q) {
		short_queries[i] = short_rnd_query();
		long_queries[i] = long_rnd_query();
	}
	vi sequence(N);
	rep(i, N) {
		sequence[i] = rnd(0, N - 1);
	}
	clock_t start_rmq = clock();
	RMQ<int> rmq(sequence);
	int rmq_total = 0;
	for (auto [l, r] : long_queries) {
		rmq_total ^= rmq.get(l, r);
	}
	clock_t start_rmqf_short = clock();
	RMQF<int> rmqf_short(sequence);
	int rmqf_short_total = 0;
	for (auto [l, r] : short_queries) {
		rmqf_short_total ^= rmqf_short.get(l, r);
	}
	clock_t start_rmqf_long = clock();
	RMQF<int> rmqf_long(sequence);
	int rmqf_long_total = 0;
	for (auto [l, r] : long_queries) {
		rmqf_long_total ^= rmqf_long.get(l, r);
	}
	clock_t end = clock();
	clock_t preprocessing_time = start_rmq - start_preprocessing;
	clock_t rmq_time = start_rmqf_short - start_rmq;
	clock_t rmqf_short_time = start_rmqf_long - start_rmqf_short;
	clock_t rmqf_long_time = end - start_rmqf_long;
	clock_t total_time = end - start;
	cout << fixed << setprecision(10) << '\n';
	cout << "preprocessing time: " << 1. * preprocessing_time / CLOCKS_PER_SEC << '\n';
	cout << "rmq long time: " << 1. * rmq_time / CLOCKS_PER_SEC << ", hash: " << rmq_total << '\n';
	cout << "rmqf short time: " << 1. * rmqf_short_time / CLOCKS_PER_SEC << ", hash: " << rmqf_short_total << '\n';
	cout << "rmqf long time: " << 1. * rmqf_long_time / CLOCKS_PER_SEC << ", hash: " << rmqf_long_total << '\n';
	cout << "total time: " << 1. * total_time / CLOCKS_PER_SEC << '\n';
	
}