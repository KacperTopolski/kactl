/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

Tree<int> t, t2;
auto it = t.insert(10).first; // it == t.upper_bound(9);
t.order_of_key(10); // # of entries strictly smaller than key
auto it2 = t.find_by_order(7); // 0 based indexing
t.join(t2); // fast only if max(T) < min(T2) or min(T) > max(T2)
