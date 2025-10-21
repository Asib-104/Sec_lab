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
    long long n = 77, e = 7;
    long long known_plain = 5;
    long long known_cipher = modExp(known_plain, e, n);
    cout << "Known (Plain, Cipher): (" << known_plain << ", " << known_cipher << ")\n";

    long long target_plain = 10;
    long long target_cipher = modExp(target_plain, e, n);
    cout << "Target Cipher: " << target_cipher << endl;
}
