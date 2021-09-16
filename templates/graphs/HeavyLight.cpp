#include <bits/stdc++.h>
#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
map<pair<int, int>, int> Search;
template <typename T, class func = function<T(const T &, const T &)>>
class segmentTree
{
public:
    T *Tree, *lst;
    int n;
    func myfunc;
    segmentTree(void) {};
    void proceed(int size, T arr[], const func & F) {
        myfunc = F, n = size;
        Tree = new T[4 * size];
        lst = new T[size];
        for (int i = 0; i < size; i++) lst[i] = arr[i];
        buildTree(1, 0, size - 1);
    };
    void buildTree(int ind, int l, int r) {
        if (l == r) {
            Tree[ind] = lst[l];
            return ;
        }
        int mid = (l + r) >> 1;
        buildTree(2 * ind, l, mid);
        buildTree(2 * ind + 1, mid + 1, r);
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    void updateUtil(int ind, int l, int r, int pos, T val) {
        if (l == r) {
            lst[pos] = val;
            Tree[ind] = val;
            return ;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) updateUtil(2 * ind, l, mid, pos, val);
        else updateUtil(2 * ind + 1, mid + 1, r, pos, val);
        Tree[ind] = myfunc(Tree[2 * ind], Tree[2 * ind + 1]);
    }
    T quaryUtil(int ind, int l, int r, int start, int end) {
        if (l >= start && r <= end)
            return Tree[ind];
        int mid = (l + r) >> 1;
        if (start > mid) return quaryUtil(2 * ind + 1, mid + 1, r, start, end);
        else if (end <= mid) return quaryUtil(2 * ind, l, mid, start, end);
        else {
            T a = quaryUtil(2 * ind + 1, mid + 1, r, mid + 1, end);
            T b = quaryUtil(2 * ind, l, mid, start, mid);
            return myfunc(a, b);
        }
    }
    void update(int pos, T val) {
        updateUtil(1, 0, n - 1, pos, val);
        return ;
    }
    T quary(int l, int r) {
        T ans = quaryUtil(1, 0, n - 1, l, r);
        return ans;
    }
};
struct element {
    int value, leader, index;
};
template <typename T, class func = function<T(const T &, const T &)>>
class HeavyLight {
public:
    T *level, *subSize, n, Log, ind = 0, lead = 0;
    vector<T> *Graph;
    T *NodeValues, **Table, *decompArr;
    func myfunc;
    struct element *Nodeimf;
    segmentTree<T> myTree;
    HeavyLight(T size, vector<T> Tree[], T Values[], const func & F) : n(size), myfunc(F) {
        Log = ceil(log2(size)) + 1;
        level = new T[size + 1];
        decompArr = new T[size + 1];
        NodeValues = new T[size + 1];
        Nodeimf = new struct element[size + 1];
        subSize = new T[size + 1];
        Graph = new vector<T>[size + 1];
        Table = new T* [size + 1];
        for (T i = 0; i <= size; i++) {
            level[i] = 0, subSize[i] = 0;
            Graph[i] = Tree[i], NodeValues[i] = Values[i];
            Table[i] = new T[Log];
        }
        preDFS(0, 0); 
        Decomposition(0, 0);
        myTree.proceed(ind, decompArr, myfunc);
    }
    void preDFS(T node, T par = 0) {
        Table[node][0] = par;
        for (T i = 1; i < Log; i++)
            Table[node][i] = Table[Table[node][i - 1]][i - 1];
        for (auto & child : Graph[node]) {
            if (child == par) continue;
            level[child] = level[node] + 1;
            preDFS(child, node);
            subSize[node] += subSize[child];
        }
        subSize[node] += 1;
    }
    T LCA(T u, T v) {
        if (level[u] < level[v]) swap(u, v);
        for (T i = Log - 1; i >= 0; i--) {
            if (level[u] - pow(2, i) >= level[v])
                u = Table[u][i];
        }
        if (u == v) return u;
        for (T i = Log - 1; i >= 0; i--) {
            if (Table[u][i] != Table[v][i])
                u = Table[u][i], v = Table[v][i];
        }
        return Table[u][0];
    }
    void Decomposition(T node, T par) {
        decompArr[ind] = (NodeValues[node]);
        Nodeimf[node] = {NodeValues[node], lead, ind++};
        T maxnode = -1, maxweight = 0;
        for (T & child : Graph[node]) {
            if (child == par) continue;
            if (subSize[child] > maxweight)
                maxweight = subSize[child], maxnode = child;
        }
        if (maxnode != -1) Decomposition(maxnode, node);
        for (T & child : Graph[node]) {
            if (child == par || child == maxnode) continue;
            lead = child;
            Decomposition(child, node);
        }
    }
    T queryUtill(T node, T granpa) {
        if (Nodeimf[node].leader == Nodeimf[granpa].leader)
            return myTree.quary(Nodeimf[granpa].index, Nodeimf[node].index);
        T ans = myTree.quary(Nodeimf[Nodeimf[node].leader].index, Nodeimf[node].index);
        node = Table[Nodeimf[node].leader][0];
        return myfunc(ans, queryUtill(node, granpa));
    }
    void update(T node, T val) {
        myTree.update(Nodeimf[node].index, val);
        Nodeimf[node].value = val;
        Search.clear();
    }
    T qyery(T u, T v) {
        if (u > v) swap(u, v);
        if (Search.find(make_pair(u, v)) != Search.end())
            return Search[make_pair(u, v)];
        T granpa = LCA(u, v);
        T ans1 = queryUtill(u, granpa), ans2 = queryUtill(v, granpa);
        Search[make_pair(u, v)] = max(ans1, ans2);
        return myfunc(ans1, ans2);
    }
};
int main(int argc, char const *argv[])
{
    boost;
    int n, u, v, q, ind = 0; 
    cin >> n >> q;
    int values[n], answers[q];
    for (int i = 0; i < n; i++) cin >> values[i];
    vector<int> graph[n + 1];
    for (int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    HeavyLight<int> cpheard(n, graph, values, [&](int a, int b) { return max(a, b); });
    while (q--) {
        int flage, pos, val, a, b; cin >> flage;
        cin >> pos >> val;
        if (flage == 1) cpheard.update(pos - 1, val);
        else answers[ind++] = (cpheard.qyery(pos - 1, val - 1));
    }
    for (int i = 0; i < ind; i++) cout << answers[i] << " ";
    return 0;
}
