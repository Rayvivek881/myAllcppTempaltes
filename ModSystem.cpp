#include <bits/stdc++.h>
const int MOD = 1000000007;
using ll = long long;
int norm(int x) 
{
    if (x < 0) x += MOD;
    if (x >= MOD) x -= MOD;
    return x;
}
template<class T>
T power(T a, int b) 
{
    T res = 1;
    for (; b; b /= 2, a *= a) 
    {
        if (b % 2)
            res *= a;
    }
    return res;
}
struct modll {
    ll x;
    modll(ll x = 0) : x(norm(x)) {}
    ll val() const {
        return x;
    }
    modll operator-() const {
        return modll(norm(MOD - x));
    }
    modll inv() const {
        assert(x != 0);
        return power(*this, MOD - 2);
    }
    modll &operator*=(const modll &rhs) {
        x = ll(x) * rhs.x % MOD;
        return *this;
    }
    modll &operator+=(const modll &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    modll &operator-=(const modll &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    modll &operator/=(const modll &rhs) {
        return *this *= rhs.inv();
    }
    friend modll operator*(const modll &lhs, const modll &rhs) {
        modll res = lhs;
        res *= rhs;
        return res;
    }
    friend modll operator+(const modll &lhs, const modll &rhs) {
        modll res = lhs;
        res += rhs;
        return res;
    }
    friend modll operator-(const modll &lhs, const modll &rhs) {
        modll res = lhs;
        res -= rhs;
        return res;
    }
    friend modll operator/(const modll &lhs, const modll &rhs) {
        modll res = lhs;
        res /= rhs;
        return res;
    }
};
