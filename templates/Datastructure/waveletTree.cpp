#include <bits/stdc++.h>
using namespace std;
// https://github.com/ShahjalalShohag/code-library/blob/master/Data%20Structures/Wavelet%20Tree.cpp
const int MAXN = (int)3e5 + 9;
const int MAXV = (int)1e9 + 9; //maximum value of any element in array
struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    int *b, *c, bsz = 0, csz = 0;
    wavelet_tree() {
        lo = 1, hi = 0, bsz = 0;
        csz = 0, l = NULL, r = NULL;
    }
    void init(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (from >= to) return;
        int mid = (lo + hi) >> 1;
        auto f = [mid](int x) {
            return x <= mid;
        };
        b = (int *) malloc((to - from + 2) * sizeof(int));
        bsz = 0;
        b[bsz++] = 0;
        c = (int *) malloc((to - from + 2) * sizeof(int));
        csz = 0;
        c[csz++] = 0;
        for (auto it = from; it != to; it++) {
            b[bsz] = (b[bsz - 1] + f(*it));
            c[csz] = (c[csz - 1] + (*it));
            bsz++, csz++;
        }
        if (hi == lo) return;
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree();
        l->init(from, pivot, lo, mid);
        r = new wavelet_tree();
        r->init(pivot, to, mid + 1, hi);
    }
    int kthSmallest(int l, int r, int k) { // kth smallest element in [l, r]
        if (l > r) return 0;
        if (lo == hi) return lo;
        int inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
        if (k <= inLeft)
            return this->l->kthSmallest(lb + 1, rb, k);
        return this->r->kthSmallest(l - lb, r - rb, k - inLeft);
    }
    int cntLessEqualK(int l, int r, int k) { // count of numbers in [l, r] Less than or equal to k
        if (l > r || k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->cntLessEqualK(lb + 1, rb, k) + this->r->cntLessEqualK(l - lb, r - rb, k);
    }
    int count(int l, int r, int k) { // count of numbers in [l, r] equal to k
        if (l > r || k < lo || k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        int mid = (lo + hi) >> 1;
        if (k <= mid)
            return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    int sum(int l, int r, int k) { // sum of numbers in [l ,r] less than or equal to k
        if (l > r or k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
    }
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};
wavelet_tree t; // 1 based indexing
int a[MAXN];
int main()
{
    int i, j, k, n, m, q, l, r;
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> a[i];
    t.init(a + 1, a + n + 1, -MAXV, MAXV);
    cin >> q;
    while (q--) {
        int x; cin >> x;
        cin >> l >> r >> k;
        if (x == 0)
            cout << t.kthSmallest(l, r, k) << endl;
        else if (x == 1)
            cout << t.cntLessEqualK(l, r, k) << endl;
        else if (x == 2)
            cout << t.count(l, r, k) << endl;
        if (x == 3)
            cout << t.sum(l, r, k) << endl;
    }
    return 0;
}
