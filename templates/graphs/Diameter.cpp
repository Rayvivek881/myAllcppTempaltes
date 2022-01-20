void LenProcess(int node, int par, vector<int> Graph[], vector<int> & len) {
    int val = 0;
    for (auto & child : Graph[node]) {
        if (child == par) continue;
        LenProcess(child, node, Graph, len);
        val = max(val, len[child]);
    }
    len[node] = val + 1;
}
vector<int> Diameter(int root, vector<int> Graph[], int n) {
    vector<int> len(n + 1, 0), result;
    vector<int> vis(n + 1, 0), sta = { root };
    LenProcess(root, 0, Graph, len);
    while (!sta.empty()) {
        int node = sta.back(), val = 0;
        vis[node] = 1;
        sta.pop_back(), result.push_back(node);
        for (auto & child : Graph[node]) {
            if (len[child] >= len[val] && vis[child] == 0) val = child;
        }
        if (val != 0) sta.push_back(val);
    }
    root = result.back();
    len.assign(n + 1, 0), result.clear();
    LenProcess(root, 0, Graph, len);
    sta.push_back(root), vis.assign(n + 1, 0);
    while (!sta.empty()) {
        int node = sta.back(), val = 0;
        vis[node] = 1;
        sta.pop_back(), result.push_back(node);
        for (auto & child : Graph[node]) {
            if (len[child] >= len[val] && vis[child] == 0) val = child;
        }
        if (val != 0) sta.push_back(val);
    }
    return result;
}
