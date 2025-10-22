#include <iostream>
#include <vector>
using namespace std;

// Iterative modular inverse (combines gcdExtended and modInverse)
long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1, q, t;
    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;
    return x1;
}

// Modular exponentiation
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

// Compute gcd
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    // Step 1: Choose primes
    long long p = 17, q = 11;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    // Step 2: Generate public key e
    long long e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) break; // e must be coprime with phi
    }

    // Step 3: Generate private key d (modular inverse)
    long long d = modInverse(e, phi);

    cout << "n = " << n << ", phi = " << phi << endl;
    cout << "Public Key (e,n): (" << e << "," << n << ")\n";
    cout << "Private Key (d,n): (" << d << "," << n << ")\n";

    // Step 4: Find multiple private keys
    cout << "Other possible private keys (d + k*phi):\n";
    for(int k = 1; k <= 5; k++) { // first 5 multiples
        cout << d + k * phi << " ";
    }
    cout << endl;

    // Step 5: Encrypt and decrypt
    long long msg = 88;
    long long cipher = modExp(msg, e, n);
    long long decrypted = modExp(cipher, d, n);

    cout << "Plaintext: " << msg << endl;
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
