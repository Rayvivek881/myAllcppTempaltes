#include <bits/stdc++.h>
using namespace std;
template <typename T>
class BinaryIndexTree {
public:
    T *Tree1, *Tree2, n;
    BinaryIndexTree(int n) : n(n + 5) {
        Tree1 = new T[n + 5];
        Tree2 = new T[n + 5];
        for(int i = 0; i < n + 5; i++)
            Tree1[i] = Tree2[i] = 0;
    }
    void updateUtill(int i, T mul, T add) {
        while (i < n) {
            Tree1[i] += mul, Tree2[i] += add;
            i |= (i + 1);
        }
    }
    void update(int l, int r, T x) {
        updateUtill(l, x, -x * (l - 1));
        updateUtill(r, -x, x * r);
    }
    T query(int i) {
        T mul = 0, add = 0, st = i;
        while (i >= 0) {
            mul += Tree1[i], add += Tree2[i];
            i = (i & (i + 1)) - 1;
        }
        return (mul * st + add);
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
int main(int argc, char const *argv[])
{
    BinaryIndexTree<int> Tree(10);
    Tree.update(0, 7, 5);
    cout << Tree.query(2, 9);
    return 0;
}
