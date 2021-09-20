#include<bits/stdc++.h>
using namespace std;
template<typename T>
class FenwickTree {
public:
    T n, *Tree;
    FenwickTree(int size) : n(size + 2) {
        Tree = new T[size + 2];
        for (int i = 0; i <= size + 1; i++)
            Tree[i] = 0;
    }
    void update(int ind, int delta) {
        for (++ind; ind < n; ind += ind & -ind)
            Tree[ind] += delta;
    }
    T query(int ind) {
        T ans = 0;
        for (++ind; ind > 0; ind -= ind & -ind)
            ans += Tree[ind];
        return ans;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int kthelement(int k) {
        int l = 0, r = n - 1, ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (query(mid) >= k) {
                r = mid - 1;
                ans = mid;
            } else l = mid + 1;
        }
        return ans;
    }
};
int main(int argc, char const *argv[])
{
    int n, q; cin >> n >> q;
    FenwickTree<int> Tree(n);
    while (q--) {
        int flage; cin >> flage;
        if (flage == 1) {
            int val; cin >> val;
            Tree.update(val, 1);
        } else {
            int k; cin >> k;
            cout << Tree.kthelement(k) << endl;
        }
    }
    return 0;
}
