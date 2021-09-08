#include <bits/stdc++.h>
using namespace std;
vector<int> suffix_array_construction(string s) {
    s += "$";
    int n = s.size(), alphabet = 256, classes = 1;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0, classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    p.erase(p.begin());
    return p;
}
vector<int> lcp_construction(string const& s, vector<int> const& suffix_array) {
    int n = s.size(), k = 0;
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[suffix_array[i]] = i;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suffix_array[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }
    return lcp;
}
int main(int argc, char const *argv[]) {
    string str1 = "banana";
    vector<int> lst = suffix_array_construction(str1);
    for (int i = 0; i < lst.size(); i++) cout << lst[i] << " ";
    cout << endl;
    vector<int> temp = lcp_construction(str1, lst);
    for (int i = 0; i < temp.size(); i++) cout << temp[i] << " ";
    return 0;
}
