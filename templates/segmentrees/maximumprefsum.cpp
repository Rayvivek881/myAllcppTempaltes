#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = INT32_MAX, MOD = 1e9 + 7, N = 2e5 + 10;
struct element
{
    ll ans, sum;
};
ll lst[N];
struct element Tree[4 * N];
element mergeNode(element & left, element & right)
{
    element temp;
    temp.sum = (left.sum + right.sum);
    temp.ans = max(left.ans, left.sum + right.ans);
    return temp;
}
void BuildTree(int ind, int l, int r)
{
    if (l == r)
    {
        Tree[ind].sum = lst[l];
        Tree[ind].ans = max(0ll, lst[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    BuildTree(2 * ind, l, mid);
    BuildTree(2 * ind + 1, mid + 1, r);
    Tree[ind] = mergeNode(Tree[2 * ind], Tree[2 * ind + 1]);
}
void update(int ind, int l, int r, int pos, ll val)
{
    if (l == r)
    {
        lst[l] = val;
        Tree[ind].sum = lst[l];
        Tree[ind].ans = max(0ll, lst[l]);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(2 * ind, l, mid, pos, val);
    else update(2 * ind + 1, mid + 1, r, pos, val);
    Tree[ind] = mergeNode(Tree[2 * ind], Tree[2 * ind + 1]);
}
element query(int ind, int l, int r, int start, int end)
{
    if (l >= start && r <= end)
        return Tree[ind];
    int mid = (l + r) >> 1;
    if (mid < start) 
        return query(2 * ind + 1, mid + 1, r, start, end);
    else if (mid >= end) 
        return query(2 * ind, l, mid, start, end);
    else
    {
        struct element a = query(2 * ind + 1, mid + 1, r, mid + 1, end);
        struct element b = query(2 * ind, l, mid, start, mid);
        return mergeNode(b, a);
    }
}
int main(int argc, char const *argv[])
{
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> lst[i];
    BuildTree(1, 0, n - 1);
    while (q--)
    {
        ll flage, pos, val, l, r;
        cin >> flage;
        if (flage == 1)
        {
            cin >> pos >> val;
            update(1, 0, n - 1, pos - 1, val);
        }
        else
        {
            cin >> l >> r;
            l--, r--;
            cout << query(1, 0, n - 1, l, r).ans << endl;
        }
    }
    return 0;
}
