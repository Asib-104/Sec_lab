#include <iostream>
using namespace std;

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    long long p = 23, g = 5, x = 6;
    long long y = modExp(g, x, p);

    long long msg = 10, k1 = 7;
    long long C1 = modExp(g, k1, p);
    long long C2 = (msg * modExp(y, k1, p)) % p;

    cout << "Original Cipher: (" << C1 << ", " << C2 << ")\n";

    long long k2 = 5;
    long long R1 = (C1 * modExp(g, k2, p)) % p;
    long long R2 = (C2 * modExp(y, k2, p)) % p;

    cout << "Re-randomized Cipher: (" << R1 << ", " << R2 << ")\n";
}
