#include<bits/stdc++.h>
using namespace std;
template<typename T>
class FenwickTree {
public:
    int n; vector<int> Tree;
    FenwickTree(int size) : n(size + 2) {
        Tree.assign(size + 2, 0);
    }
    void update(int ind, int delta) {
        for (++ind; ind < n; ind += ind & -ind)
            Tree[ind] += delta;
    }
    T queryUtil(int ind, T ans = 0) {
        for (++ind; ind > 0; ind -= ind & -ind)
            ans += Tree[ind];
        return ans;
    }
    T query(int l, int r) {
        return queryUtil(r) - queryUtil(l-1);
    }
};
