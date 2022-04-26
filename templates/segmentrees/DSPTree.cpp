#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct element {
    T value;
    struct element *child[2];
};
template<typename T = int, class func = function<T(const T &, const T &)>>
class DSPTree {
    T n, defaultvalue;
    element<T> *getNode() {
        struct element<T> *node = new struct element<T>();
        node->child[0] = node->child[1] = NULL;
        node->value = 0;
        return node;
    }
    func myfunc;
    struct element<T> *root = getNode();
    void helperLazy(element<T> * ptr, T size) {
        if (ptr->child[0] == NULL)
            ptr->child[0] = getNode();
        if (ptr->child[1] == NULL)
            ptr->child[1] = getNode();
    }
    void update(element<T> * ptr, T l, T r, T pos, T value) {
        if (l == r) {
            ptr->value = value;
            return ;
        }
        T mid = (l + r) >> 1;
        helperLazy(ptr, r - l + 1);
        if (pos <= mid) {
            update(ptr->child[0], l, mid, pos, value);
        } else {
            update(ptr->child[1], mid + 1, r, pos, value);
        }
        ptr->value = myfunc(ptr->child[0]->value, ptr->child[1]->value);
    }
    T query(element<T> * ptr, T l, T r, T l1, T r1) {
        if (l >= l1 && r <= r1)
            return ptr->value;
        T mid = (l + r) >> 1;
        helperLazy(ptr, r - l + 1);
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
    DSPTree(T size, T value, const func & F) : myfunc(F) {
        this->n = size, this->defaultvalue = value;
    }
    void update(T pos, T value) {
        return update(root, 0, n - 1, pos, value);
    }
    T query(T l, T r) {
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
