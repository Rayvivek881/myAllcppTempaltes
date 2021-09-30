int primes[N], dp[N] = {0};
void FactorizationSevie() {
    for (int i = 1; i < N; i++) {
        primes[i] = i;
        if (i % 2 == 0) primes[i] = 2;
    }
    for (int i = 3; i * i < N; i++) {
        if (primes[i] != i) continue;
        for (int j = i * i; j < N; j += i)
            if (primes[j] == j) primes[j] = i;
    }
}
