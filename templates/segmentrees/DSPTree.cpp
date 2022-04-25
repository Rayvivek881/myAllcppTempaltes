#include<bits/stdc++.h>
using namespace std;
template<typename T = int, class func = function<T(const T &, const T &)>>
class DSPTree {
    T n, defaultvalue;
    struct element {
        T value;
        struct element *child[2];
        element () { 
            child[0] = child[1] = NULL;
            value = 0;
        }
    };
    func myfunc;
    struct element *root = new struct element();
    void update(element * ptr, int l, int r, int pos, T value) {
        if (l == r) {
            ptr->value = value;
            return ;
        }
        T mid = (l + r) >> 1;
        if (ptr->child[0] == NULL)
            ptr->child[0] = new struct element();
        if (ptr->child[1] == NULL)
            ptr->child[1] = new struct element();
        if (pos <= mid) {
            update(ptr->child[0], l, mid, pos, value);
        } else {
            update(ptr->child[1], mid + 1, r, pos, value);
        }
        ptr->value = myfunc(ptr->child[0]->value, ptr->child[1]->value);
    }
    T query(element * ptr, int l, int r, int l1, int r1) {
        if (l >= l1 && r <= r1)
            return ptr->value;
        T mid = (l + r) >> 1;
        if (ptr->child[0] == NULL)
            ptr->child[0] = new struct element();
        if (ptr->child[1] == NULL)
            ptr->child[1] = new struct element();
        if (l1 > mid) {
            return query(ptr->child[1], mid + 1, r, l1, r1);
        } else if (r1 <= mid) {
            return query(ptr->child[0], l, mid, l1, r1);
        } else {
            T a = query(ptr->child[0], l, mid, l1, mid);
            T b = query(ptr->child[1], mid + 1, r, mid + 1, r1);
            return myfunc(a, b);
        }
    }
public:
    DSPTree(int size, T value, const func & F) : myfunc(F) {
        this->n = size, this->defaultvalue = value;
    }
    void update(int pos, T value) {
        return update(root, 0, n - 1, pos, value);
    }
    T query(int l, int r) {
        return query(root, 0, n - 1, l, r);
    }
};
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    long long n, q; cin >> n >> q;
    DSPTree<long long> Tree(n + 1, 0, [&](long long a, long long b) { return a + b; });
    for (int i = 1; i <= n; i++) {
        long long value; cin >> value;
        Tree.update(i, value);
    }
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        cout << Tree.query(l, r) << '\n';
    }
    return 0;
}
