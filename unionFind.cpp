#include <bits/stdc++.h>
using namespace std;
template <typename mydata>
class UnionFind
{
public:
    int n;
    vector<mydata> parent, rank;
    UnionFind(int size) : n(size) 
    {
        parent.resize(size);
        rank.assign(size, 0);
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }
    mydata find(mydata x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void Union(mydata a, mydata b)
    {
        mydata aset = find(a), bset = find(b);
        if (aset == bset) return ;
        if (rank[aset] < rank[bset])
            parent[aset] = bset;
        else if (rank[aset] > rank[bset])
            parent[bset] = aset;
        else
            parent[bset] = aset, rank[aset]++;
    }
};
int main(int argc, char const *argv[])
{
    int n, q;
    cin >> n >> q;
    UnionFind<int> obj(n);
    for (int i = 0; i < q; i++)
    {
        int f, a, b;
        cin >> f;
        cin >> a >> b;
        if (f == 1)
            obj.Union(a, b);
        else
            cout << (obj.find(a) == obj.find(b)) << endl;
    }
    return 0;
}
