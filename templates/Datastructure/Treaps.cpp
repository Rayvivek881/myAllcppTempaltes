#include<bits/stdc++.h>
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;
typedef struct element* pelement;
struct element {
    int value, cnt, prior, rev; 
    struct element *left, *right;
    element() {
        left = NULL, right = NULL;
        cnt = 0, rev = 0;
        prior = rand();
    }
};
template #include<bits/stdc++.h>
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;
typedef struct element* pelement;
struct element {
    int cnt, prior, rev, value; 
    struct element *left, *right;
    element() {
        left = NULL, right = NULL;
        cnt = 0, rev = 0;
        prior = rand();
    }
};
template <typename T>
class ImplicitTreaps {
public:
    pelement root = NULL;
    int size() {
        return size(root);
    }
    int size(pelement Node) {
        return (Node != NULL) ? Node->cnt : 0;
    }
    void Update_size (pelement Node) {
        if (Node == NULL) return ;
        push(Node->left), push(Node->right);
        Node->cnt = 1 + size(Node->left) + size(Node->right);
    }
    bool empty() { return size(root) == 0; }
    void push_back(T val) {
        pelement temp = new struct element();
        temp->value = val;
        Merge(root, root, temp);
    }
    T operator[] (int ind) { return valueAt(root, ind, 0); }
    T valueAt(pelement Node, int key, int add) {
		push(Node);
		int curkey = size(Node->left) + add;
		if(key == curkey) return Node->value;
		if(key < curkey) return valueAt(Node->left, key, add);
		return valueAt(Node->right, key, curkey + 1);
	}
    void insertAt(int index, T val) {
        pelement temp = new struct element();
        temp->value = val;
        pelement left, right;
        Split(root, left, right, index);
        Merge(left, left, temp);
        Merge(root, left, right);
    }
    void erase(int index) { erase(index, root); }
    void erase(int index, pelement & Node, int add = 0) {
		if(Node == NULL) return ;
		push(Node);
		int curkey = size(Node->left) + add;
		if(curkey == index){
			pelement it = Node;
			Merge(Node, Node->left, Node->right);
			delete it;
		}
		else if(curkey > index) erase(index, Node->left, add);
		else erase(index, Node->right, curkey + 1);
		Update_size(Node);
	}
    void push(pelement Node) {
        if (Node && Node->rev) {
            Node->rev = false;
            swap(Node->left, Node->right);
            if (Node->left) Node->left->rev ^= true;
            if (Node->right) Node->right->rev ^= true;
        }
    }
    void Merge(pelement & Node, pelement left, pelement right) {
        push(left), push(right);
        if (!left || !right)
            Node = left != NULL ? left : right;
        else if (left->prior > right->prior)
            Merge(left->right, left->right, right), Node = left;
        else Merge(right->left, left, right->left), Node = right;
        Update_size(Node);
    }
    void Split(pelement Node, pelement & left, pelement & right, int key, int add = 0) {
        if (Node == NULL) return void(left = right = NULL);
        push(Node);
        int curr_key = add + size(Node->left);
        if (key <= curr_key)
            Split(Node->left, left, Node->left, key, add),  right = Node;
        else {
            Split(Node->right, Node->right, right, key, add + 1 + size(Node->left));
            left = Node;
        }
        Update_size(Node);
    }
    void reverse(int l, int r) {
        pelement a, b, c;
        Split(root, a, b, l);
        Split(b, b, c, r - l + 1);
        b->rev = true;
        Merge(root, a, b);
        Merge(root, root, c);
    }
    void cycle_shift(int l, int r) {
        pelement left, right, m, rr;
        Split(root, left, m, l);
        Split(m, m, right, r - l);
		Split(right, rr, right, 1);
		Merge(m, m, right);
		Merge(rr, rr, m);
		Merge(root, left, rr);
    }
};
int main(int argc, char const *argv[])
{
    boost;
    int n, q, m; cin >> n >> q >> m;
    ImplicitTreaps<int> Treap;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        Treap.insert(x);
    }
    while (q--) {
        int flage, l, r; cin >> flage >> l >> r;
        if (l == r) continue;
        if (flage == 1) Treap.cycle_shift(l - 1, r - 1);
        else Treap.reverse(l - 1, r - 1);
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        cout << Treap[x - 1] << ' ';
    }
    return 0;
}
