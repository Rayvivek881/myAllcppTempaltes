#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
void multiply(int F[2][2], int M[2][2])
{
	int x = ((F[0][0] * M[0][0]) % mod + (F[0][1] * M[1][0]) % mod) % mod;
	int y = ((F[0][0] * M[0][1]) % mod + (F[0][1] * M[1][1]) % mod) % mod;
	int z = ((F[1][0] * M[0][0]) % mod + (F[1][1] * M[1][0]) % mod) % mod;
	int w = ((F[1][0] * M[0][1]) % mod + (F[1][1] * M[1][1]) % mod) % mod;
	F[0][0] = x, F[0][1] = y, F[1][0] = z, F[1][1] = w;
}
void power(int F[2][2], int n)
{
	if (n == 0 || n == 1) return;
	int M[2][2] = {{1, 1}, {1, 0}};
	power(F, n / 2);
	multiply(F, F);
	if (n % 2 != 0) multiply(F, M);
}
int fib(int n)
{
	int F[2][2] = {{1, 1}, {1, 0}};
	if (n == 0) return 0;
	power(F, n - 1);
	return F[0][0];
}
int main()
{
	for (int i = 0; i < 20; i++) cout << fib(i) << " ";
	return 0;
}
