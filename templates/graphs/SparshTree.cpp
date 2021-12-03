struct element {
    ll u, v, weight, ind;
    bool operator<(element & other) {
        return weight < other.weight;
    }
};
template<typename T, class func = function<T(const T &, const T &)>>
class SparsTree {
	T size, Log, time = 0;
	func myfunc;
	vector<T> *lift, *Table; 
	vector<T> parWeight, depth, tin, tout;
	vector<pair<T, T>> *Tree;
	vector<element> Eadges;
public:
	SparsTree(T n, vector<element> & arr, const func & F) : size(n) {
		Log = log2(n) + 3, Eadges = arr, depth.assign(n + 1, 0);
		Table = new vector<T>[n + 1], myfunc = F;
		tin.resize(n + 1), tout.resize(n + 1);
		lift = new vector<T>[n + 1], parWeight.assign(n + 1, 0);
		Tree = new vector<pair<T, T>>[n + 1];
		for (T i = 0; i <= n; i++) {
			lift[i].assign(Log, 0), Tree[i].clear();
			Table[i].assign(Log, 0);
		}
		for (auto val : Eadges) {
			Tree[val.u].push_back({val.v, val.weight});
			Tree[val.v].push_back({val.u, val.weight});
		}
		PreDFS(1, 0);
		MainDFS(1, 0);
	}
	void PreDFS(T node, T par) {
		tin[node] = time++;
		for (auto & child : Tree[node]) {
			if (child.first == par) continue;
			depth[child.first] = depth[node] + 1;
			parWeight[child.first] = child.second;
			PreDFS(child.first, node);
		}
		tout[node] = time++;
	}
	void MainDFS(T node, T par) {
		lift[node][0] = par, Table[node][0] = parWeight[node];
		for (T i = 1; i < Log; i++) {
			lift[node][i] = lift[lift[node][i - 1]][i - 1];
			Table[node][i] = myfunc(Table[node][i - 1], 
				Table[lift[node][i - 1]][i - 1]);
		}
		for (auto & child : Tree[node]) {
			if (child.first == par) continue;
			MainDFS(child.first, node);
		}
	}
	bool is_ancestor(T u, T v) {
		if (u == 0) return true;
		if (v == 0) return false;
		return tin[u] <= tin[v] && tout[u] >= tout[v];
	}
	T findLCA(T u, T v) {
		if (is_ancestor(u, v)) return u;
		if (is_ancestor(v, u)) return v;
		for (T i = Log - 1; i >= 0; i--) {
			if (!is_ancestor(lift[u][i], v))
				u = lift[u][i];
		}
		return lift[u][0];
	}
	T query(T u, T v) {
		T lca = findLCA(u, v), ans = 0;
		if (lca != u) {
			for (T i = Log - 1; i >= 0; i--) {
				if (is_ancestor(lca, lift[u][i])) {
					ans = myfunc(ans, Table[u][i]);
					u = lift[u][i];
				}
			}
		}
		if (lca != v) {
			for (T i = Log - 1; i >= 0; i--) {
				if (is_ancestor(lca, lift[v][i])) {
					ans = myfunc(ans, Table[v][i]);
					v = lift[v][i];
				}
			}
		}
		return ans;
	}
};
