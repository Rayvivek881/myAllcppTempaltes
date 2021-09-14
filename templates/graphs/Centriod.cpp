#include <bits/stdc++.h>
using namespace std;
vector<int> Centroid(const vector<int> g[], int n) {
    vector<int> centroid, sz(n);
    function<void (int, int)> dfs = [&](int u, int prev) {
        sz[u] = 1;
        bool is_centroid = true;
        for (auto v : g[u]) if (v != prev) {
                dfs(v, u);
                sz[u] += sz[v];
                if (sz[v] > n / 2) is_centroid = false;
        }
        if (n - sz[u] > n / 2) is_centroid = false;
        if (is_centroid) centroid.push_back(u);
    };
    dfs(0, -1);
    return centroid;
}
int main(int argc, char const *argv[])
{
    int n; cin >> n;
    vector<int> Graph[n];
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        Graph[u - 1].push_back(v - 1);
        Graph[v - 1].push_back(u - 1);
    }
    cout << Centroid(Graph, n)[0] + 1 << "\n";
    return 0;
}
