#include<bits/stdc++.h>
using namespace std;
template <typename T, class func = function<T(const T &, const T &)>>
class DynamicSgTree {
private:
    struct Node {
        T data;
        struct Node *child[2];
    };
    T dvalue = 0, n;
    func myfunc;
    Node* getNode() {
        Node *temp = new struct Node;
        temp->data = dvalue;
        temp->child[0] = temp->child[1] = NULL;
        return temp;
    }
    void updateUtill(Node *node, int l, int r, int pos, T val) {
        if (node == NULL) node = getNode();
        if (pos < l || pos > r) return ;
        if (l == r) {
            node->data = val;
            return ;
        }
        int mid = (l + r) >> 1;
        updateUtill(node->child[0], l, mid, pos, val);
        updateUtill(node->child[1], mid + 1, r, pos, val);
        node->data = myfunc(node->child[0]->data, node->child[1]->data);
    }
    T queryUtill(Node *node, int l, int r, int l1, int r1) {
        
    }
public:
    struct Node *root = NULL;
    DynamicSgTree(int n, const func & F) : myfunc(F), n(n) {}
    void update(int pos, T val) { updateUtill(root, 0, n - 1, pos, val); }
};
