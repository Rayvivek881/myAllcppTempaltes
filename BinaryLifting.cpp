#include <bits/stdc++.h>
using namespace std;
template <typename data>
class BinearyLifting
{
public:
    int n, Log;
    vector<vector<data>> Table, Graph;
    vector<data> lavel;
    BinearyLifting(int size, vector<vector<data>> & Tree) : n(size), Graph(Tree)
    {
        lavel.assign(size, 0);
        Table.resize(size), Log = ceil(log2(size)) + 1;
        for (int i = 0; i < size; i++)
            Table[i].resize(Log);
        PreDFS(0, 0);
    }
    void PreDFS(data node, data par)
    {
        Table[node][0] = par;
        for (int i = 1; i < Log; i++)
            Table[node][i] = Table[Table[node][i - 1]][i - 1];
        for (auto child : Graph[node])
        {
            if (child == par) continue;
            lavel[child] = lavel[node] + 1;
            PreDFS(child, node);
        }
    }
    data LCA(data u, data v)
    {
        if (lavel[u] < lavel[v]) swap(u, v);
        for (int i = Log - 1; i >= 0; i--)
        {
            if (lavel[u] - pow(2, i) >= lavel[v])
                u = Table[u][i];
        }
        if (u == v) return u;
        for (int i = Log - 1; i >= 0; i--)
        {
            if (Table[u][i] != Table[v][i])
                u = Table[u][i], v = Table[v][i];
        }
        return Table[u][0];
    }
    data kthAnsester(data node, int k)
    {
        for (int i = 0; i < Log; i++)
        {
            if (k & (1 << i))
            {
                if ((1 << i) > lavel[node]) return -1;
                node = Table[node][i];
            }
        }
        return node;
    }
};
int main(int argc, char const *argv[])
{
    int n; cin >> n;
    vector<vector<int>> Tree(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        Tree[u - 1].push_back(v - 1);
        Tree[v - 1].push_back(u - 1);
    }
    BinearyLifting<int> obj(n, Tree);
    cout << (obj.kthAnsester(8, 8));
    return 0; 
}
