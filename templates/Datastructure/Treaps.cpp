#include<bits/stdc++.h>
using namespace std;
typedef struct Node* Pnode;
struct Node {
    int Value, cnt, prior, rev;
    struct Node *child[2];
    Node() {
        child[0] = child[1] = NULL;
        cnt = 0, rev = 0, prior = rand();
    }
};
template<typename T>
class ImplicitTreaps {
private:
    struct Node *root = NULL;
    int size(Pnode node) { return (node != NULL) ? node->cnt : 0; }
    void Update_size(Pnode node) {
        if (node == NULL) return ;
        push(node->child[0]), push(node->child[1]);
        node->cnt = 1 + size(node->child[0]) + size(node->child[1]);
    }
    void push(Pnode node) {
        if (node == NULL || node->rev == 0) return ;
        node->rev = false;
        swap(node->child[0], node->child[1]);
        if (node->child[0] != NULL)
            node->child[0]->rev ^= true;
        if (node->child[1] != NULL)
            node->child[1]->rev ^= true;
    }
    T ValueAt(Pnode node, int Key, int add) {
        push(node);
        int curkey = size(node->child[0]) + add;
        if (curkey == Key) return node->Value;
        if (Key < curkey) return ValueAt(node->child[0], Key, add);
        else return ValueAt(node->child[1], Key, curkey + 1);
    }
    void Merge(Pnode & node, Pnode left, Pnode right) {
        push(left), push(right);
        if (left == NULL || right == NULL)
            node = (left != NULL) ? left : right;
        else if (left->prior > left->prior)
            Merge(left->child[1], left->child[1], right), node = left;
        else Merge(right->child[0], left, right->child[0]), node = right;
        Update_size(node);
    }
    void Split(Pnode node, Pnode & left, Pnode & right, int key, int add = 0) {
        if (node == NULL) return void(left = right = NULL);
        push(node);
        int curr_key = add + size(node->child[0]);
        if(key <= curr_key) {
            Split(node->child[0], left, node->child[0], key, add);
            right = node;
        } else {
            Split(node->child[1], node->child[1], right, key, add + 1 + size(node->child[0]));
            left = node;
        }
        Update_size(node);
    }
    void erase(int index, Pnode & node, int add = 0) {
        if (node == NULL) return ;
        push(node);
        int curkey = size(node->child[0]) + add;
        if (curkey == index) {
            Pnode it = node;
            Merge(node, node->child[0], node->child[1]);
            delete it;
        } else if (curkey > index) {
            erase(index, node->child[0], add);
        } else erase(index, node->child[1], curkey + 1);
        Update_size(node);
    }
    void replace(int index, Pnode & node, T Value, int add = 0) {
        if (node == NULL) return ;
        push(node);
        int curkey = size(node->child[0]) + add;
        if (curkey == index) {
            node->Value = Value;
        } else if (curkey > index) {
            replace(index, node->child[0], Value, add);
        } else replace(index, node->child[1], Value, curkey + 1);
        Update_size(node);
    }
public:
    int size() { return size(root); }
    bool empty() { return size(root) == 0; }
    T operator[] (int ind) { return ValueAt(root, ind, 0); }
    void erase(int index) { return erase(index, root); }
    void repalce(int ind, T Value) { return replace(ind, root, Value); }
    void push_back(T Value) {
        Pnode temp = new struct Node();
        temp->Value = Value;
        Merge(root, root, temp);
    }
    void insert(int index, T Value) {
        Pnode temp = new struct Node();
        temp->Value = Value;
        Pnode left, right;
        Split(root, left, right, index);
        Merge(left, left, temp);
        Merge(root, left, right);
    }
    void reverse(int l, int r) {
        Pnode a, b, c;
        Split(root, a, b, l);
        Split(b, b, c, r - l + 1);
        b->rev = true;
        Merge(root, a, b);
        Merge(root, root, c);
    }
    void cycle_shift(int l, int r, int cnt = 1) {
        Pnode left, right, m, rr;
        Split(root, left, m, l);
        Split(m, m, right, r - l + 1 - cnt);
        Split(right, rr, right, cnt);
        Merge(m, m, right);
        rr->rev = true;
        Merge(rr, rr, m);
        Merge(root, left, rr);
    }
};
int main(int argc, char const *argv[])
{
    int n, q; cin >> n >> q;
    ImplicitTreaps<int> Treap;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        Treap.push_back(x);
    }
    for (int i = 0; i < Treap.size(); i++) cout << Treap[i] << ' ';
    cout << endl;
    while (q--) {
        int f; cin >> f;
        if (f == 1) {
            int x; cin >> x;
            Treap.push_back(x);
        } else if (f == 2) {
            int x, i; cin >> x >> i;
            Treap.insert(i, x);
        } else if (f == 3) {
            int i; cin >> i;
            Treap.erase(i);
        } else if (f == 4) {
            int l, r; cin >> l >> r;
            Treap.reverse(l, r);
        } else {
            int l, r, cnt; cin >> l >> r;
            Treap.cycle_shift(l, r);
        }
        for (int i = 0; i < Treap.size(); i++) cout << Treap[i] << ' ';
        cout << endl;
    }
    return 0;
}
