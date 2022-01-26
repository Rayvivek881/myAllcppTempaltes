vi isprime(N , 1), prime, SPF(N);
void manipulated_seive() {
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i < N; i++) {
        if (isprime[i])
            prime.push_back(i), SPF[i] = i;
        for (int j = 0; j < prime.size() && i * prime[j] < N && prime[j] <= SPF[i]; j++) {
            isprime[i * prime[j]] = false;
            SPF[i * prime[j]] = prime[j];
        }
    }
}
