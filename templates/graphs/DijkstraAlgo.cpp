#include <bits/stdc++.h>
using namespace std;
void Dijkstra(vector<pair<int, int>> adj[], vector<int> & ans, int src) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    que.push({0, src}), ans[src] = 0;
    while (!que.empty()) {
        int u = que.top().second;
        que.pop();
        for (auto child : adj[u]) {
            int v = child.first, weight = child.second;
            if (ans[v] > ans[u] + weight) {
                ans[v] = ans[u] + weight;
                que.push({ans[v], v});
            }
        }
    }
}
void sortestPath(int src) {
    queue<int> que;
    path[src] = 0; que.push(src);
    while (!que.empty()) {
        int node = que.front();
        que.pop();
        for (int child : Graph[node]) {
            if (path[child] != inf) continue;
            path[child] = path[node] + 1;
            que.push(child);
        }
    }
}
int main(int argc, char const *argv[])
{
    int n, m; cin >> n >> m;
    vector<pair<int, int>> adj[n];
    vector<int> ans(n, INT32_MAX);
    for(int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    Dijkstra(adj, ans, 0);
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    return 0;
}
