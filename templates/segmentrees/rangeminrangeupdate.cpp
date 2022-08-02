template <typename T, class func = function<T(const T &, const T &)>>
class rangeTree {
    T *Tree, *lazy; 
    int n;
    func myfunc;
    vector<T> lst;
    void BuildTree(int ind, int l, int r) {
        if (l == r) {
            Tree[ind] = lst[l], lazy[ind] = 0;
            return;
        }
        int mid = (l + r) >> 1;
        BuildTree(2 * ind, l, mid);
        BuildTree(2 * ind + 1, mid + 1, r);
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
        lazy[ind] = 0;
    }
    void updateUtil(int ind, int l, int r, int start, int end, T val) {
        if (l >= start && r <= end)
            lazy[ind] += val;
        if (lazy[ind] != 0) {
            Tree[ind] += lazy[ind];
            if (l != r)
                lazy[2 * ind] += lazy[ind], lazy[2 * ind + 1] += lazy[ind];
            lazy[ind] = 0;
        }
        if ((l >= start && r <= end) || l > end || r < start)
            return ;
        int mid = (l + r) >> 1;
        if (mid >= end || mid < start) {
            updateUtil(2 * ind, l, mid, start, end, val);
            updateUtil(2 * ind + 1, mid + 1, r, start, end, val);
        }
        else {
            updateUtil(2 * ind, l, mid, start, mid, val);
            updateUtil(2 * ind + 1, mid + 1, r, mid + 1, end, val);
        }
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    T queryUtil(int ind, int l, int r, int start, int end) {
        if (lazy[ind] != 0) {
            Tree[ind] += lazy[ind];
            if (l != r)
                lazy[2 * ind] += lazy[ind], lazy[2 * ind + 1] += lazy[ind];
            lazy[ind] = 0;
        }
        if (l >= start && r <= end)
            return Tree[ind];
        int mid = (l + r) >> 1;
        if (mid >= end) 
            return queryUtil(2 * ind, l, mid, start, end);
        else if (mid < start)
            return queryUtil(2 * ind + 1, mid + 1, r, start, end);
        else {
            T a = queryUtil(2 * ind, l, mid, start, mid);
            T b = queryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
            return myfunc(a, b);
        }
    }
public:
    rangeTree(int size, vector<T> & arr, const func & F) : lst(arr), n(size), myfunc(F) {
        Tree = new T[4 * size];
        lazy = new T[4 * size];
        BuildTree(1, 0, n - 1);
    }
    void update(int l, int r, T val) {
        updateUtil(1, 0, n - 1, l, r, val);
        return ;
    }
    T query(int l, int r) {
        T temp = queryUtil(1, 0, n - 1, l, r);
        return temp;
    }
};
