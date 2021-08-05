#include <bits/stdc++.h>
using namespace std;
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
    void update(int ind, int l, int r, int pos, T val)
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
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    T quary(int ind, int l, int r, int start, int end)
    {
        if (l >= start && r <= end)
            return Tree[ind];
        int mid = (l + r) >> 1;
        if (start > mid) return quary(2 * ind + 1, mid + 1, r, start, end);
        else if (end <= mid) return quary(2 * ind, l, mid, start, end);
        else
        {
            T a = quary(2 * ind + 1, mid + 1, r, mid + 1, end);
            T b = quary(2 * ind, l, mid, start, mid);
            return myfunc(a, b);
        }
    }
};
int main(int argc, char const *argv[])
{
    int n, q; cin >> n >> q;
    vector<int> lst(n);
    for (int i = 0; i < n; i++) cin >> lst[i];
    segmentTree<int> myTree(n, lst, [&](int a, int b) { return min(a, b);});
    while(q--)
    {
        int f, pos, val, l, r;
        cin >> f;
        if (f == 1)
        {
            cin >> pos >> val;
            myTree.update(1, 0, n - 1, pos, val);
        }
        else
        {
            cin >> l >> r;
            cout << myTree.quary(1, 0, n - 1, l, r) << endl;
        }
    }
    return 0;
}
