#include<bits/stdc++.h>
using namespace std;
struct Line {
    long long m, c;
    Line(long long m, long long c): m(m), c(c) {}
    long long inter(Line l) {
        return (l.c - c + m - l.m) / (m - l.m);
    }
    long long Value(long long x) { return m * x + c; }
};
template<typename T> // slope is decreasing
class Convex_hull {
    deque<pair<Line, T>> que;
public:
    void insert(T m, T c) {
        Line temp = Line(m, c);
        while (!que.empty() && que.back().first.inter(temp) < que.back().second)
            que.pop_back();
        if (que.empty()) {
            que.push_back({temp, 0});
            return ;
        }
        que.push_back({temp, que.back().first.inter(temp)});
    }
    T query(T x) { // when x is in increasing
        while (que.size() > 1 && que[1].second <= x)
            que.pop_front();
        return que[0].first.Value(x);
    }
};
int main(int argc, char const *argv[])
{
    int n; cin >> n;
    vector<long long> a(n), b(n), dp(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    Convex_hull<long long> hull;
    hull.insert(b[0], dp[0]);
    for(int i = 1; i < n; i++) {
        dp[i] = hull.query(a[i]);
        hull.insert(b[i], dp[i]);
    }
    cout << dp[n - 1] << '\n';
    return 0;
}
