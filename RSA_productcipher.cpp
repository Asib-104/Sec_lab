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

long long gcdExtended(long long a, long long b, long long &x, long long &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    long long x1, y1;
    long long g = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = gcdExtended(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

int main() {
    long long p = 17, q = 11;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 7;
    long long d = modInverse(e, phi);

    cout << "Public Key (e,n): (" << e << "," << n << ")\n";
    cout << "Private Key (d,n): (" << d << "," << n << ")\n";

    long long msg = 88;
    cout << "Plaintext: " << msg << endl;

    long long cipher = modExp(msg, e, n);
    cout << "Ciphertext: " << cipher << endl;

    long long decrypted = modExp(cipher, d, n);
    cout << "Decrypted: " << decrypted << endl;
}
