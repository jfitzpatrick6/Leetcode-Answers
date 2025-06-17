#define MAX 100005
#define MOD 1000000007

long long fact[MAX];
long long ifact[MAX];

long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = result * base % mod;
        base = base * base % mod;
        exp /= 2;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAX; i++)
        fact[i] = (fact[i - 1] * i) % MOD;

    ifact[MAX - 1] = modpow(fact[MAX - 1], MOD - 2, MOD);
    for (int i = MAX - 2; i >= 0; i--)
        ifact[i] = (ifact[i + 1] * (i + 1)) % MOD;
}

int countGoodArrays(int n, int m, int k) {
    precompute();
    long long part1 = m;
    long long part2 = modpow(m - 1, n - 1 - k, MOD);
    long long comb = fact[n - 1] * ifact[k] % MOD * ifact[n - 1 - k] % MOD;

    long long result = part1 * part2 % MOD * comb % MOD;
    return (int)result;
}
