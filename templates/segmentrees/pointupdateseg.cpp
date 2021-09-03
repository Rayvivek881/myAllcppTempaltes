#include <bits/stdc++.h>
using namespace std;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
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
int main(int argc, char const *argv[])
{
    boost;
    int n, q; cin >> n >> q;
    vector<int> lst(n), dp1(n), dp2(n);
    for (int i = 0; i < n; i++)
    {
        cin >> lst[i];
        dp1[i] = (lst[i] - i);
        dp2[i] = (lst[i] - (n - 1 - i));
    }
    segmentTree<int> myTree1(n, dp1, [&](int a, int b) { return min(a, b);});
    segmentTree<int> myTree2(n, dp2, [&](int a, int b) { return min(a, b);});
    while (q--)
    {
        int flage, k, x; cin >> flage;
        if (flage == 1)
        {
            cin >> k >> x;
            myTree1.update(k - 1, x - (k - 1));
            myTree2.update(k - 1, x - (n - 1 - (k - 1)));
        }
        else
        {
            cin >> k;
            int a = myTree1.quary(0, k - 1) + k - 1;
            int b = myTree2.quary(k - 1, n - 1) + n - 1 - (k - 1);
            cout << min(a, b) << "\n";
        }
    }
    return 0;
}
