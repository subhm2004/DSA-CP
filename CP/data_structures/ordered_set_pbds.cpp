/*
 * ============================================================================
 * TOPIC    : PBDS — Policy Based Data Structure
 * FILE     : ordered_set_pbds.cpp
 * PROBLEM  : Order statistics — k-th element, rank, order_of_key
 * LEETCODE : — (GNU extension, not on LC)
 * APPROACH : GNU pbds tree with order_statistics_node_update
 * NOTE     : GNU libstdc++ only. macOS: brew install gcc → g++-14 file.cpp
 * COMPLEX  : O(log n) insert/erase/find_by_order/order_of_key
 * ============================================================================
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ordered_set<int> os;
    for (int x : {10, 20, 30, 40, 50}) os.insert(x);
    cout << "order_of_key(25) = " << os.order_of_key(25) << endl;
    cout << "find_by_order(2) = " << *os.find_by_order(2) << endl;
    return 0;
}
