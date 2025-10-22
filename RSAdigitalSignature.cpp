#include <iostream>
using namespace std;

// Modular exponentiation: computes (base^exp) % mod efficiently
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

// Combined modular inverse using iterative Extended Euclidean Algorithm
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

int main() {
    // Step 1: Generate RSA keys
    long long p = 17, q = 11;
    long long n = p * q;             // modulus
    long long phi = (p - 1) * (q - 1); // Euler's totient
    long long e = 7;                 // public key exponent
    long long d = modInverse(e, phi); // private key exponent

    cout << "Public Key (e,n): (" << e << "," << n << ")\n";
    cout << "Private Key (d,n): (" << d << "," << n << ")\n";

    // Step 2: Message to sign
    long long msg = 9;
    cout << "Message: " << msg << endl;

    // Step 3: Generate digital signature using private key
    long long signature = modExp(msg, d, n);
    cout << "Digital Signature: " << signature << endl;

    // Step 4: Verify signature using public key
    long long verified = modExp(signature, e, n);
    cout << "Verification Result: " << verified << endl;

    if (verified == msg)
        cout << "Signature is VALID\n";
    else
        cout << "Signature is INVALID\n";

    return 0;
}
