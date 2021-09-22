#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#else
#include <bits/stdc++.h>
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
    { for(int i = x ; i < y; i++ ) cout << lst[i] << " "[i > y - 1]; wrt(); }
// template<typename T> using indexed_set = 
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename T> using indexed_multiset = 
//     tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template<typename Key, typename T> using indexed_map =
//     tree<Key, T, less<Key>, rb_tree_tag, tree_order_statistics_node_update>;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define precision(n) cout.precision(n);
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
const ll inf = INT32_MAX, MOD = 1e9 + 7, N = 2e5 + 10;
template <typename T, class func = function<T(const T &, const T &)>>
class segmentTree
{
public:
    T *Tree;
    int n;
    func myfunc;
    vector<T> lst;
    segmentTree(int n, vector<T> & arr, const func & F) : lst(arr), n(n), myfunc(F)
    { 
        Tree = new T[4 * n];
        buildTree(1, 0, n - 1);
    };
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
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    void updateUtil(int ind, int l, int r, int pos, T val)
    {
        if (l == r)
        {
            lst[pos] = val;
            Tree[ind] = val;
            return ;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) updateUtil(2 * ind, l, mid, pos, val);
        else updateUtil(2 * ind + 1, mid + 1, r, pos, val);
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    T quaryUtil(int ind, int l, int r, int start, int end)
    {
        if (l >= start && r <= end)
            return Tree[ind];
        int mid = (l + r) >> 1;
        if (start > mid) return quaryUtil(2 * ind + 1, mid + 1, r, start, end);
        else if (end <= mid) return quaryUtil(2 * ind, l, mid, start, end);
        else
        {
            T a = quaryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
            T b = quaryUtil(2 * ind, l, mid, start, mid);
            return myfunc(a, b);
        }
    }
    void update(int pos, T val)
    {
        updateUtil(1, 0, n - 1, pos, val);
        return ;
    }
    T quary(int l, int r)
    {
        T ans = quaryUtil(1, 0, n - 1, l, r);
        return ans;
    }
};
vector<int> Tree[N], lst(N);
int inTime[N], outTime[N], Time = -1;
void EularTour(int node, int par = 0) {
    lst[++Time] = node;
    inTime[node] = Time;
    for (int child : Tree[node]) {
        if (child != par) EularTour(child, node);
    }
    outTime[node] = Time;
}
int main(int argc, char const *argv[])
{
    boost;
    int n, q; cin >> n >> q;
    vector<ll> arr(n), temp(n);
    inputlst(temp, 0, n);
    fora(i, 0, n - 1) {
        int u, v; cin >> u >> v;
        Tree[u].push_back(v);
        Tree[v].push_back(u);
    }
    EularTour(1, 0);
    fora(i, 0, n) arr[i] = temp[lst[i] - 1];
    segmentTree<ll> mtree(n, arr, [&] (ll a, ll b) { return a + b; });
    while (q--) {
        ll flage, a, b; cin >> flage;
        if (flage == 2) {
            cin >> a;
            wrt(mtree.quary(inTime[a], outTime[a]));
        } else {
            cin >> a >> b;
            mtree.update(inTime[a], b);
        }
    }
    return 0;
}
