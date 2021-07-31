ll factorialNumInverse[N + 1], naturalNumInverse[N + 1], fact[N + 1];
void nCrPreComputation()
{
    naturalNumInverse[0] = naturalNumInverse[1] = 1;
    fora(i, 2, N)
        naturalNumInverse[i] = naturalNumInverse[mod % i] * (mod - mod / i) % mod;
    factorialNumInverse[0] = factorialNumInverse[1] = 1;
    fora(i, 2, N)
        factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % mod;
    fact[0] = 1;
    fora(i, 1, N) fact[i] = (fact[i - 1] * i) % mod;
}
ll nCrMod(ll N, ll R)
{
    ll ans = ((fact[N] * factorialNumInverse[R]) % mod * factorialNumInverse[N - R])% mod;
    return ans;
}
ll answer(ll n, ll x)
{
    ll res = 1;
    while (n > 0)
    {
        if (n & 1) res = (res * x) % MOD;
        n  = n >> 1;
        x = (x * x) % MOD;
    }
    return res;
}
