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
struct element {
    ll u, v, weight;
    bool operator<(element & other) {
        return weight < other.weight;
    }
};
vector<element> KruskalMST(vector<element> & Eadges, int n) {
    vector<element> result;
    UnionFind<int> graph(n + 1);
    sortlst(Eadges);
    for (auto & child : Eadges) {
        if (graph.find(child.u) != graph.find(child.v)) {
            result.push_back(child);
            graph.Union(child.u, child.v);
        }
    }
    return result;
}
