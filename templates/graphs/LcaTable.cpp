#include<bits/stdc++.h>
using namespace std;
int n, *depth, Time = 0;
vector<int> Graph[300005];
class LcaTable {
    int Log, **Table, *lst, *inTime, *outTime;
    vector<int> searchArr;
    void EularTour(int node, int par = 0) {
        searchArr.push_back(node);
        inTime[node] = Time++, depth[node] = depth[par] + 1;
        for (auto & child : Graph[node]) {
            if (child == par) continue;
            EularTour(child, node);
            searchArr.push_back(node);
        }
        outTime[node] = Time++;
    }
    int marge(int i, int j) {
        return (lst[i] <= lst[j]) ? i : j;
    }
    int query(int l, int r) {
        int j = log2(r - l + 1);
        return marge(Table[l][j], Table[r - (1 << j) + 1][j]);
    }
public:
    LcaTable() {
        depth = new int [n + 1], depth[0] = 0, Time = 0;
        outTime = new int [n + 1], searchArr.clear();
        inTime = new int [n + 1], EularTour(1, 0);
        lst = new int [searchArr.size() + 1], Table = new int * [searchArr.size() + 1];
        Log = ceil(log2((int)searchArr.size())) + 2;
        for (int i = 0; i < searchArr.size(); i++) {
            lst[i] = depth[searchArr[i]];
            Table[i] = new int [Log + 1], Table[i][0] = i;
        }
        for (int j = 1; j < Log; j++) {
            for (int i = 0; (i + (1 << j) - 1) < searchArr.size(); i++)
                Table[i][j] = marge(Table[i][j - 1], Table[i + (1 << (j - 1))][j - 1]);
        }
    }
    int FindLca(int a, int b) {
        if (inTime[a] >= inTime[b]) swap(a, b);
        return searchArr[query(inTime[a], inTime[b])];
    }
};
int main(int argc, char const *argv[])
{
    int m; cin >> n >> m;
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    LcaTable table;
    while (m--) {
        int a, b; cin >> a >> b;
        cout << (depth[a] + depth[b] - 2 * depth[table.FindLca(a, b)]) << "\n";
    }
    return 0;
}
