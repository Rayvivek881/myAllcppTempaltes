int Block, N = 1e6 + 10;
struct Query {
    int l, r, index;
    bool operator<(const Query & obj) {
        if(l/Block != obj.l/Block)
            return l/Block < obj.l/Block;
        return r < obj.r;
    }
};
template<typename T>
class MOsAlgo {
    T ans;
    int *lst, *Freq, n, l, r;
public:
    MOsAlgo(int arr[]) : lst(arr) {
        l = 0, r = -1, ans = 0;
        Freq = new int[N];
        for (int i = 0; i < N; i++)
            Freq[i] = 0;
    }
    void insert(int i) {
        ans -= (Freq[lst[i]] * 1ll * Freq[lst[i]] * 1ll * lst[i]);
        Freq[lst[i]]++;
        ans += (Freq[lst[i]] * 1ll * Freq[lst[i]] * 1ll * lst[i]);
    }
    void remove(int i) {
        ans -= (Freq[lst[i]] * 1ll * Freq[lst[i]] * 1ll * lst[i]);
        Freq[lst[i]]--;
        ans += (Freq[lst[i]] * 1ll * Freq[lst[i]] * 1ll * lst[i]);
    }
    T get(int i, int j) {
        while (l > i) insert(--l);
        while (r < j) insert(++r);
        while (l < i) remove(l++);
        while (r > j) remove(r--);
        return ans;
    }
};
