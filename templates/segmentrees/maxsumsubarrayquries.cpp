#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = INT32_MIN, N = 2e5 + 10;
struct element
{
    ll ans = 0, pref = 0, suf = 0, sum = 0;
};
template<typename T>
class maxsumTree
{
public:
    int n;
    struct element *Tree;
    vector<T> lst;
    maxsumTree(int n, vector<T> & arr) : lst(arr), n(n)
    {
        Tree = new struct element[4 * n];
        buildTree(1, 0, n - 1);
    }
    element mergeNode(element left, element right)
    {
        struct element temp;
        temp.sum = left.sum + right.sum;
        temp.pref = max(left.pref, left.sum + right.pref);
        temp.suf = max(right.sum + left.suf, right.suf);
        temp.ans = max({left.ans, right.ans, left.suf + right.pref});
        return temp;
    }
    void buildTree(int ind, int l, int r)
    {
        if (l == r)
        {
            Tree[ind].sum = lst[l];
            if (lst[l] >= 0)
            {
                Tree[ind].ans = lst[l];
                Tree[ind].pref = lst[l];
                Tree[ind].suf = lst[l];
            }
            return ;
        }
        int mid = (l + r) >> 1;
        buildTree(2 * ind, l, mid);
        buildTree(2 * ind + 1, mid + 1, r);
        Tree[ind] = mergeNode(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    void updateUtil(int ind, int l, int r, int pos, T val)
    {
        if (l == r)
        {
            lst[l] = val;
            Tree[ind].sum = lst[l];
            if (lst[l] >= 0)
            {
                Tree[ind].ans = lst[l];
                Tree[ind].pref = lst[l];
                Tree[ind].suf = lst[l];
            }
            else
            {
                Tree[ind].ans = 0;
                Tree[ind].pref = 0;
                Tree[ind].suf = 0;
            }
            return ;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) updateUtil(2 * ind, l, mid, pos, val);
        else updateUtil(2 * ind + 1, mid + 1, r, pos, val);
        Tree[ind] = mergeNode(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    element queryUtil(int ind, int l, int r, int start, int end)
    {
        if (l >= start && r <= end)
            return Tree[ind];
        int mid = (l + r) >> 1;
        if (start > mid) return queryUtil(2 * ind + 1, mid + 1, r, start, end);
        else if (end <= mid) return queryUtil(2 * ind, l, mid, start, end);
        else
        {
            struct element a = queryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
            struct element b = queryUtil(2 * ind, l, mid, start, mid);
            return mergeNode(a, b);
        }
    }
    void update(int pos, T val)
    {
        updateUtil(1, 0, n - 1, pos, val);
        return ;
    }
    ll query(int l, int r)
    {
        struct element temp = queryUtil(1, 0, n - 1, l, r);
        return temp.ans;
    }
};
int main(int argc, char const *argv[])
{
    ll n, m;
    cin >> n >> m;
    vector<ll> lst(n);
    for (int i = 0; i < n; i++) cin >> lst[i];
    maxsumTree<ll> segmentTree(n, lst);
    while (m--)
    {
        ll pos, val;
        cin >> pos >> val;
        segmentTree.update(pos - 1, val);
        cout << segmentTree.query(0, n - 1) << endl;
    }
    return 0;
}