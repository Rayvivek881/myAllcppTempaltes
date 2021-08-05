#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#else
#include "myheader.h"
#endif
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/pb_ds/detail/standard_policies.hpp>
// using namespace __gnu_pbds;
using namespace std;
void input() {return;}
template<typename T1, typename... T2>
	void input(T1 & x, T2&... args){((cin >> x), input(args...));}
void wrt() { cout << "\n"; return;}
template<typename T1, typename... T2>
	void wrt(T1 x, T2... args){((cout << x << ' '), wrt(args...));}
template<typename T> void inputlst(T & lst, int x, int y)
	{ for(int i = x ; i < y; i++ ) cin >> lst[i]; }
template<typename T> void printlst(T & lst, int x, int y)
	{ for(int i = x ; i < y; i++ ) cout << lst[i] << ' '; wrt(); }
// template<typename T> using indexed_set = 
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename T> using indexed_multiset = 
//     tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename Key, typename T> using indexed_map =
//     tree<Key, T, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define ll long long
#define pb push_back
#define fi first
#define se second
#define tests int test; cin >> test; while(test--)
#define fora(i, x, y) for (ll i = x; i < y; ++i)
#define ford(i, x, y) for (ll i = x; i >= y; --i)
#define all(lst) lst.begin(), lst.end()
#define rall(lst) lst.rbegin(), lst.rend()
#define ceil(a, b) ((a + b - 1) / (b))
#define sum(lst) accumulate(all(lst), 0ll)
#define countval(lst, val) count(all(lst), val)
#define lcn(lst, val) find(all(lst), val) - lst.begin()
#define sortlst(lst) sort(all(lst))
#define sorted(lst) is_sorted(all(lst))
#define rsortlst(lst) sort(rall(lst))
#define setbits(n) __builtin_popcount(n)
#define sortarr(x, n) sort(x, x + n)
#define sz(lst) (int)lst.size()
typedef priority_queue<ll, vector<ll>, greater<ll>> pques;
typedef priority_queue<ll> pqueg;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef vector<vl> vovl;
typedef vector<vi> vovi;
typedef vector<string> vs;
typedef map<int, int> mi;
typedef map<ll, ll> ml;
typedef set<ll> sl;
typedef set<int> si;
const ll inf = INT32_MAX, MOD = 1e9 + 7, N = 1e5;
int main(int argc, char const *argv[])
{
	boost;
	
	return 0;
}
