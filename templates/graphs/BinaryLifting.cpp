vector<int> Graph[200005];
int n, *depth;
class BinaryLifting {
    vector<vector<int>> Table;
    int Log;
    void answer(int node, int par = -1) {
        Table[node][0] = par;
        for (int i = 1; i < Log; i++) {
            if (depth[node] >= (1 << i))
                Table[node][i] = Table[Table[node][i - 1]][i - 1];
        }
        for (auto & child : Graph[node]) {
            if (child == par) continue;
            depth[child] = depth[node] + 1;
            answer(child, node);
        }
    }
public:
    BinaryLifting() {
        Log = ceil(log2(n)) + 2;
        Table.assign(n + 1, vector<int>(Log));
        depth = new int [n + 1], depth[1] = 0;
        answer(1, -1);
    }
    int kthAnsester(int node, int k) {
        if (depth[node] < k) return -1;
        for (int i = Log - 1; i >= 0; i--)
            if (k & (1 << i)) node = Table[node][i];
        return node;
    }
    int FindLca(int a, int b) {
        if (depth[a] >= depth[b]) swap(a, b);
        int k = abs(depth[a] - depth[b]);
        for (int i = Log - 1; i >= 0; i--)
            if (k & (1 << i)) b = Table[b][i];
        if (a == b) return a;
        for (int i = Log - 1; i >= 0; i--) {
            if (Table[a][i] != Table[b][i])
                a = Table[a][i], b = Table[b][i];
        }
        return Table[a][0];
    }
};
