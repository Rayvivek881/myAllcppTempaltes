#include<bits/stdc++.h>
using namespace std;
template <typename T>
class Indexed_multiset {
    struct element {
        T Freq, sum;
        element () { Freq = sum = 0; }
    };
    int n, curr_size = 0, defaultValue = -1;
    struct element *Tree;
    map<T, int> Compres;
    inline void margeNode(element & a, element & lhs, element & rhs) {
        a.Freq = lhs.Freq + rhs.Freq, a.sum = lhs.sum + rhs.sum;
    }
    void update(int ind, int l, int r, int pos, T value, bool keep) {
        if (l == r) {
            if (keep == 1) {
                Tree[ind].Freq += 1, Tree[ind].sum += value;
                curr_size += 1;
            }
            else if (Tree[ind].Freq >= 1) {
               Tree[ind].Freq -= 1, Tree[ind].sum -= value;
               curr_size -= 1;
            }
            return ;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(2 * ind, l, mid, pos, value, keep);
        else update(2 * ind + 1, mid + 1, r, pos, value, keep);
        margeNode(Tree[ind], Tree[2 * ind], Tree[2 * ind + 1]);
    }
    T kth_element(int ind, int l, int r, int k) {
        if (Tree[ind].Freq < k)
            return defaultValue;
        if (l == r)
            return Tree[ind].sum / Tree[ind].Freq;
        int mid = (l + r) >> 1;
        if (Tree[2 * ind].Freq >= k)
            return kth_element(2 * ind, l, mid, k);
        return kth_element(2 * ind + 1, mid + 1, r, k - Tree[2 * ind].Freq);
    }
    int cnt_element(int ind, int l, int r, int k) {
        if (l == r)
            return Tree[ind].Freq;
        int mid = (l + r) >> 1;
        if (k <= mid) 
            return cnt_element(2 * ind, l, mid, k);
        return Tree[2 * ind].Freq + cnt_element(2 * ind + 1, mid + 1, r, k);
    }
    T sum_Smaller(int ind, int l, int r, int k) {
        if (l == r)
            return Tree[ind].sum;
        int mid = (l + r) >> 1;
        if (k <= mid) 
            return sum_Smaller(2 * ind, l, mid, k);
        return Tree[2 * ind].sum + sum_Smaller(2 * ind + 1, mid + 1, r, k);
    }
public:
    Indexed_multiset(map<T, int> & m) : Compres(m) {
        n = m.size() + 5;
        Tree = new struct element [4 * this->n];
    }
    int size() { return curr_size; }
    void insert(T value) { update(1, 0, n - 1, Compres[value], value, 1); }
    void erase(T value) { update(1, 0, n - 1, Compres[value], value, 0); }
    T find_by_order(int k) { return kth_element(1, 0, n - 1, k); }
    int order_of_key(T value) {
        auto it = Compres.lower_bound(value);
        if (it == Compres.begin())
            return 0;
        it = prev(it);
        return cnt_element(1, 0, n - 1, it->second);
    }
    T sum_Smaller(T value) {
        auto it = Compres.lower_bound(value);
        if (it == Compres.begin())
            return 0;
        it = prev(it);
        return sum_Smaller(1, 0, n - 1, it->second);
    }
};
int main(int argc, char const *argv[])
{
    int n, temp = 1; cin >> n;
    vector<int> lst(n);
    map<int, int> Compres;
    for (int i = 0; i < n; i++) cin >> lst[i];
    sort(lst.begin(), lst.end());
    for (int i = 0; i < n; i++) {
        if (Compres.find(lst[i]) != Compres.end())
            continue;
        Compres[lst[i]] = temp++;
    }
    Indexed_multiset<int> mset(Compres);
    for (int i = 0; i < n; i++) {
        int t, value; cin >> t >> value;
        if (t == 1) mset.insert(value);
        else if (t == 2) mset.erase(value);
        else if (t == 3) cout << mset.order_of_key(value) << endl;
        else cout << mset.find_by_order(value) << endl;
    }
    return 0;
}
