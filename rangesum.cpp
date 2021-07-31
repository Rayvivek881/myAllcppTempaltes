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
const ll inf = INT32_MAX, MOD = 1e9 + 7, N = 1e5;
int Tree[4 * N], lst[N];
void buildTree(int ind, int l, int r)
{
    if (l == r)
    {
        Tree[ind] = lst[l];
        return ;
    }
    int mid = (l + r) >> 1;
    buildTree(2 * ind, l, mid);
    buildTree(2 * ind + 1, mid + 1, r);
    Tree[ind] = (Tree[2 * ind] + Tree[2 * ind + 1]);
}
void update(int ind, int l, int r, int pos, int val)
{
    if (l == r)
    {
        lst[pos] = val;
        Tree[ind] = val;
        return ;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(2 * ind, l, mid, pos, val);
    else update(2 * ind + 1, mid + 1, r, pos, val);
    Tree[ind] = (Tree[2 * ind] + Tree[2 * ind + 1]);
}
int quary(int ind, int l, int r, int start, int end)
{
    if (l >= start && r <= end)
        return Tree[ind];
    int mid = (l + r) >> 1;
    if (start > mid) return quary(2 * ind + 1, mid + 1, r, start, end);
    else if (end <= mid) return quary(2 * ind, l, mid, start, end);
    else
    {
        int a = quary(2 * ind + 1, mid + 1, r, mid + 1, end);
        int b = quary(2 * ind, l, mid, start, mid);
        return a + b;
    }
}
int main(int argc, char const *argv[])
{
    boost;
    int n, q; input(n, q);
    inputlst(lst, 0, n);
    buildTree(1, 0, n - 1);
    while(q--)
    {
        int f, pos, val, l, r;
        input(f);
        if (f == 1)
        {
            input(pos, val);
            update(1, 0, n - 1, pos, val);
        }
        else
        {
            input(l, r);
            cout << quary(1, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
