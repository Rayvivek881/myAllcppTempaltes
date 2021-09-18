ll factorialNumInverse[N + 1], naturalNumInverse[N + 1], fact[N + 1];
void nCrPreComputation()
{
    naturalNumInverse[0] = naturalNumInverse[1] = 1;
    fora(i, 2, N)
        naturalNumInverse[i] = naturalNumInverse[MOD % i] * (MOD - MOD / i) % MOD;
    factorialNumInverse[0] = factorialNumInverse[1] = 1;
    fora(i, 2, N)
        factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % MOD;
    fact[0] = 1;
    fora(i, 1, N) fact[i] = (fact[i - 1] * i) % MOD;
}
ll nCrMod(ll N, ll R)
{
    ll ans = ((fact[N] * factorialNumInverse[R]) % MOD * factorialNumInverse[N - R])% MOD;
    return ans;
}
