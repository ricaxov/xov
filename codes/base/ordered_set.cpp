#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class X> using ordered_set = tree<X, null_type, less<X>, rb_tree_tag, tree_order_statistics_node_update>;