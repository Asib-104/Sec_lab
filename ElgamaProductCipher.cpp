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

    cout << "Public Key: (p=" << p << ", g=" << g << ", y=" << y << ")\n";

    long long msg = 10, k = 7;
    long long C1 = modExp(g, k, p);
    long long C2 = (msg * modExp(y, k, p)) % p;

    cout << "Ciphertext: (C1=" << C1 << ", C2=" << C2 << ")\n";

    long long decrypted = (C2 * modExp(C1, p - 1 - x, p)) % p;
    cout << "Decrypted Message: " << decrypted << endl;
}
