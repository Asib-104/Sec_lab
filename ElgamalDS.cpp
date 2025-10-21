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
    long long p = 23, g = 5, x = 6;
    long long y = modExp(g, x, p);

    cout << "Public Key: (p=" << p << ", g=" << g << ", y=" << y << ")\n";
    cout << "Private Key: x=" << x << endl;

    long long msg = 10, k = 7;
    long long r = modExp(g, k, p);
    long long s = ((msg - x * r) * modInverse(k, p-1)) % (p-1);
    if (s < 0) s += (p-1);

    cout << "Signature: (r=" << r << ", s=" << s << ")\n";

    long long v1 = (modExp(y, r, p) * modExp(r, s, p)) % p;
    long long v2 = modExp(g, msg, p);
    cout << "Verification: " << (v1 == v2 ? "Valid" : "Invalid") << endl;
}
