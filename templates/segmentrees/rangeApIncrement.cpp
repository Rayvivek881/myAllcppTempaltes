#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
template <typename T, class func = function<T(const T &, const T &)>>
class rangeTree {
public:
    T *Tree, d;
    pair<T, T> *lazy;
    int n;
    func myfunc;
    vector<T> lst;
    rangeTree(int size, vector<T> & arr, const func & F, T d) : lst(arr), n(size), myfunc(F), d(d) { 
        Tree = new T[4 * size];
        lazy = new pair<T, T>[4 * size];
        BuildTree(1, 0, size - 1);
    }
    void BuildTree(int ind, int l, int r) {
        lazy[ind] = {0, 0};
        if (l == r) {
            Tree[ind] = lst[l];
            return;
        }
        int mid = (l + r) >> 1;
        BuildTree(2 * ind, l, mid);
        BuildTree(2 * ind + 1, mid + 1, r);
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    ll helper(ll a, ll len, ll d) {
        ll ans = (len * ((2 * a) + (len - 1) * d)) / 2;
        return ans;
    }
    void updateUtil(int ind, int l, int r, int start, int end, T val) {
        if (l >= start && r <= end) {
            lazy[ind].first += val;
            lazy[ind].second += d;
        }
        int mid = (l + r) >> 1;
        if (lazy[ind].first != 0) { // 75 -> 81 28
            Tree[ind] += helper(lazy[ind].first, r - l + 1, lazy[ind].second);
            if (l != r) { // 79 -> 81 57
                lazy[2 * ind].first += lazy[ind].first,
                lazy[2 * ind].second += lazy[ind].second,
                lazy[2 * ind + 1].first += (lazy[ind].first + lazy[ind].second * (mid - l + 1));
                lazy[2 * ind + 1].second += lazy[ind].second;
            }
            lazy[ind] = {0, 0};
        }
        if ((l >= start && r <= end) || l > end || r < start)
            return ;
        if (mid >= end || mid < start) {
            updateUtil(2 * ind, l, mid, start, end, val);
            updateUtil(2 * ind + 1, mid + 1, r, start, end, val);
        } else {
            updateUtil(2 * ind, l, mid, start, mid, val);
            updateUtil(2 * ind + 1, mid + 1, r, mid + 1, end, val + (mid - start + 1));
        }
        Tree[ind] = myfunc(Tree[2 * ind], Tree[(2 * ind) + 1]);
    }
    T queryUtil(int ind, int l, int r, int start, int end) {
        int mid = (l + r) >> 1;
        if (lazy[ind].first != 0) {
            Tree[ind] += helper(lazy[ind].first, r - l + 1, lazy[ind].second);
            if (l != r) {
                lazy[2 * ind].first += lazy[ind].first,
                lazy[2 * ind].second += lazy[ind].second,
                lazy[2 * ind + 1].first += (lazy[ind].first + lazy[ind].second * (mid - l + 1));
                lazy[2 * ind + 1].second += lazy[ind].second;
            }
            lazy[ind] = {0, 0};
        }
        if (l >= start && r <= end)
            return Tree[ind];
        if (mid >= end) 
            return queryUtil(2 * ind, l, mid, start, end);
        else if (mid < start)
            return queryUtil(2 * ind + 1, mid + 1, r, start, end);
        else {
            T a = queryUtil(2 * ind, l, mid, start, mid);
            T b = queryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
            return myfunc(a, b);
        }
    }
    void update(int l, int r, T val) {
        updateUtil(1, 0, n - 1, l, r, val);
        return ;
    }
    T query(int l, int r) {
        T temp = queryUtil(1, 0, n - 1, l, r);
        return temp;
    }
};
int main(int argc, char const *argv[])
{
    boost;
    ll n, q; cin >> n >> q;
    vector<ll> lst(n, 0);
    for (int i = 0; i < n; i++) cin >> lst[i];
    rangeTree<ll> segmentTree(n, lst, [&](ll a, ll b) {return a + b; });
    while (q--)
    {
        ll flage, l, r, k; cin >> flage;
        if (flage == 1)
        {
            cin >> l >> r;
            l--, r--;
            segmentTree.update(l, r, 1);
        }
        else
        {
            cin >> l >> r;
            cout << segmentTree.query(l - 1, r - 1) << "\n";
        }
    }
    return 0;
}
