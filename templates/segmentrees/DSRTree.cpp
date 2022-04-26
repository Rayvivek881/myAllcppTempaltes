#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct element {
    T value, lazy;
    struct element *child[2];
};
template<typename T, class func = function<T(const T &, const T &)>>
class DSRTree {
    T n, temp = 0;
    element<T> *getNode() {
        struct element<T> *node = new struct element<T>();
        node->lazy = node->value = 0;
        node->child[0] = node->child[1] = NULL;
        return node;
    }
    func myfunc;
    struct element<T> *root = getNode();
    void helperLazy(element<T> * ptr, T size) {
        if (ptr->child[0] == NULL)
            ptr->child[0] = getNode();
        if (ptr->child[1] == NULL)
            ptr->child[1] = getNode();
        ptr->value += ptr->lazy * size;
        ptr->child[0]->lazy += ptr->lazy;
        ptr->child[1]->lazy += ptr->lazy;
        ptr->lazy = 0;
    }
    void update(element<T> * ptr, T l, T r, T l1, T r1, T value) {
        if (l >= l1 && r <= r1)
            ptr->lazy += value;
        helperLazy(ptr, r - l + 1);
        if ((l >= l1 && r <= r1) || r < l1 || l > r1 || l >= r)
            return;
        T mid = (l + r) >> 1;
        update(ptr->child[0], l, mid, l1, r1, value);
        update(ptr->child[1], mid + 1, r, l1, r1, value);
        ptr->value = myfunc(ptr->child[0]->value, ptr->child[1]->value);
    }
    T query(element<T> * ptr, T l, T r, T l1, T r1) {
        helperLazy(ptr, r - l + 1);
        if (l >= l1 && r <= r1) 
            return ptr->value;
        T mid = (l + r) >> 1;
        if (mid >= r1) {
            return query(ptr->child[0], l, mid, l1, r1);
        } else if (mid < l1) {
            return query(ptr->child[1], mid + 1, r, l1, r1);
        } else {
            T a = query(ptr->child[0], l, mid, l1, mid);
            T b = query(ptr->child[1], mid + 1, r, mid + 1, r1);
            return myfunc(a, b);
        }
    }
public:
    DSRTree(T size, T value, const func & F) : myfunc(F), n(size) { }
    void update(T l, T r, T value) {
        return update(root, 0, n - 1, l, r, value);
    }
    T query(T l, T r) {
        return query(root, 0, n - 1, l, r);
    }
};
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    long long n, q; cin >> n >> q;
    DSRTree<long long> Tree(n + 1, 0, [&](long long a, long long b) { return a + b; });
    for (int i = 0; i < q; i++) {
        long long l, r; cin >> l >> r;
        Tree.update(l, r, 1);
        cin >> l >> r;
        cout << Tree.query(l, r) << endl;
    }
    return 0;
}
