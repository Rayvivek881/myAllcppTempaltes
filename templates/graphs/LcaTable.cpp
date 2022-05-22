#include<bits/stdc++.h>
using namespace std;
int n, *inTime, *outTime, Time = 0, *depth;
vector<int> Graph[(int)2e5 + 10], searchArr;
void EularTour(int node, int par = 0) {
    searchArr.push_back(node);
    inTime[node] = Time++, depth[node] = depth[par] + 1;
    for (auto & child : Graph[node]) {
        if (child == par) continue;
        EularTour(child, node);
    }
    searchArr.push_back(node);
    outTime[node] = Time++;
}
template <typename T, class func = function<T(const T &, const T &)>>
class LcaTable {
public:
    int n, Log;
    func myfunc;
    T **Table, *arr;
    LcaTable(vector<T> & lst, const func & F) : myfunc(F) { 
        n = lst.size(), Log = ceil(log2((int)lst.size())) + 5;
        arr = new T[n + 1];
        Table = new T*[n + 1];
        for(int i = 0; i < n; i++) {
            Table[i] = new T[Log];
            arr[i] = lst[i], Table[i][0] = i;
        }
        for (int j = 1; j <= Log; j++) {
			for (int i = 0; (i + (1 << j) - 1) < n; i++)
				Table[i][j] = myfunc(Table[i][j - 1], Table[i + (1 << (j - 1))][j - 1]);
		}
    }
	T query(int l, int r) {
		int j = log2(r - l + 1);
		return myfunc(Table[l][j], Table[r - (1 << j) + 1][j]);
	}
    int FindLca(int a, int b) {
        if (inTime[a] >= inTime[b]) swap(a, b);
        return searchArr[query(inTime[a], inTime[b])];
    }
};
void SolveTestCases(int testCase) {
    int n, q; cin >> n >> q;
    for (int i = 0; i <= n; i++) Graph[i].clear();
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
    depth = new int[n + 1], searchArr.clear();
    inTime = new int[n + 1], depth[0] = 0;
    outTime = new int[n + 1], Time = 0;
    EularTour(1, 0);
    vector<int> LcaData(searchArr.size());
    for (int i = 0; i < searchArr.size(); i++) LcaData[i] = depth[searchArr[i]];
    LcaTable<int> Table(LcaData, [&](int i, int j) {
        return (LcaData[i] <= LcaData[j]) ? i : j;
    });
    while (q--) {
        int a, b; cin >> a >> b;
        cout << (Table.FindLca(a, b)) << endl;
    }
}
int main(int argc, char const *argv[])
{
    int testCase = 1;
    // cin >> testCase;
    for (int test = 0; test < testCase; test++)
        SolveTestCases(test);
    return 0;
}
