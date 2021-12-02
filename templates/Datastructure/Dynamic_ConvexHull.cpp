#include<bits/stdc++.h>
using namespace std;
const long long is_query = -(1ll << 62);
#define boost ios_base::sync_with_stdio(false); cin.tie(nullptr);
struct Line {
    long long m, c;
	mutable function<const Line*()> fun;
	bool operator<(const Line & val) const {
		if (val.c != is_query) 
            return m < val.m;
		const Line* temp = fun();
		if (!temp) return false;
		return c - temp->c < (temp->m - m) * val.m;
	}
};
//maintains upper hull to compute maximum
template<typename T>
class Dynamic_hull : public multiset<Line> {
    long long inf = LLONG_MAX;
    bool notOptimal(iterator ity) {
        iterator itz = next(ity), itx = prev(ity);
        if (ity == begin()) {
            if (itz == end()) return false;
            return ity->m == itz->m && ity->c <= itz->c;
        }
        if (itz == end()) 
            return ity->m == itx->m && ity->c <= itx->c;
        T value1 = (itx->c - ity->c), value2 = (ity->c - itz->c);
        if (ity->m == itx->m) 
            value1 = (itx->c > ity->c) ? inf: -inf;
		else value1 /= (ity->m - itx->m);
        if (itz->m == ity->m) 
            value2 = ity->c > itz->c ? inf: -inf;
		else value2 /= (itz->m - ity->m);
        return value1 >= value2;
    }
public:
    void insertLine(T m, T c) {
        auto ity = insert((Line){m, c});
        ity->fun = [=]{ return next(ity) == end() ? 0 : &*next(ity); };
        if (notOptimal(ity)) {
			erase(ity);
			return;
		}
        while(next(ity) != end() && notOptimal(next(ity))) erase(next(ity));
		while(ity != begin() && notOptimal(prev(ity))) erase(prev(ity));
    }
    T query(T x) {
		auto l = *lower_bound((Line){x, is_query});
		return l.m * x + l.c;
	}
};
int main(int argc, char const *argv[])
{
    boost;
    int n; cin >> n;
    vector<long long> a(n), b(n), dp(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    Dynamic_hull<long long> hull;
    hull.insertLine(-b[0], 0);
    for (int i = 1; i < n; i++) {
        dp[i] = -hull.query(a[i]);
        hull.insertLine(-b[i], -dp[i]);
    }
    cout << dp[n - 1];
    return 0;
}
