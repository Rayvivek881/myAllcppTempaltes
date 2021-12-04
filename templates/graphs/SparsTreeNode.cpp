#include<bits/stdc++.h>
using namespace std;
template<typename T, class func = function<T(const T &, const T &)>>
class SparsTree {
	int n, Log, Time = 0;
	func myfunc;
	vector<int> Values, tin, tout;
	vector<int> *Tree, *lift, *Table;
public:
	SparsTree(int n, vector<int> Graph[], vector<int> & arr, const func & F) : n(n) {
		Log = log2(n) + 3, Values = arr;
		Tree = new vector<int>[n + 1], tout.resize(n + 1);
		lift = new vector<int>[n + 1], tin.resize(n + 1);
		Table = new vector<int>[n + 1], myfunc = F;
		for (int i = 0; i <= n; i++) {
			Table[i].assign(Log, 0), lift[i].assign(Log, 0);
			Tree[i].clear();
		}
		for (int i = 0; i <= n; i++) Tree[i] = Graph[i];
		PreDFS(1, 0);
	}
	void PreDFS(int node, int par = 0) {
		Table[node][0] = Values[node];
		lift[node][0] = par, tin[node] = Time++;
		for (int i = 1; i < Log; i++) {
			lift[node][i] = lift[lift[node][i - 1]][i - 1];
			Table[node][i] = myfunc(Table[node][i - 1], Table[lift[node][i - 1]][i - 1]);
		}
		for (auto & child : Tree[node]) {
			if (child == par) continue;
			PreDFS(child, node);
		}
		tout[node] = Time++;
	}
	bool is_ancestor(T u, T v) {
		if (v == 0) return false;
		return (tin[u] <= tin[v] && tout[u] >= tout[v]) | u == 0;
	}
	int findLCA(T u, T v) {
		if (is_ancestor(u, v)) return u;
		if (is_ancestor(v, u)) return v;
		for (T i = Log - 1; i >= 0; i--) {
			if (!is_ancestor(lift[u][i], v))
				u = lift[u][i];
		}
		return lift[u][0];
	}
	int query(int u, int v) {
		int lca = findLCA(u, v), ans = 0;
		for (int i = Log - 1; i >= 0; i--) {
			if (is_ancestor(lca, lift[u][i])) {
				ans = myfunc(ans, Table[u][i]);
				u = lift[u][i];
			}
			if (is_ancestor(lca, lift[v][i])) {
				ans = myfunc(ans, Table[v][i]);
				v = lift[v][i];
			}
		}
		return myfunc(ans, Values[lca]);
	}
};
int main(int argc, char const *argv[])
{
	int n; cin >> n;
	vector<int> Graph[n + 1], arr(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v;
		Graph[u].push_back(v);
		Graph[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) cin >> arr[i];
	SparsTree<int> myDsa(n, Graph, arr, [&](int a, int b) { return max(a, b); });
	cout << myDsa.query(3, 7);
	return 0;
}
