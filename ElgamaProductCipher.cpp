include <iostream>
#include <set>
#include <cmath>
using namespace std;

// Function to calculate power modulo p (base^exp % p)
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to calculate the generator (primitive root) modulo p
long long find_generator(long long p) {
    set<long long> num;
    long long g;
    long long check = 0;

    for (long long j = 2; j < p; j++) {
        num.clear();
        long long siz = 0;
        for (long long i = 1; i < p; i++) {
            siz++;
            long long x = mod_exp(j, i, p);
            num.insert(x);
            if (siz != num.size()) {
                break;
            }
            if (siz == p - 1) {
                g = j;
                check = 1;
                break;
            }
        }
        if (check) break;
    }

    return check ? g : -1;
}

// Structure for ciphertext
struct Cipher {
    long long c1, c2;
};

// Encrypt message using ElGamal
Cipher elgamal_encrypt(long long m, long long p, long long g, long long y, long long k) {
    Cipher C;
    C.c1 = mod_exp(g, k, p);
    C.c2 = (m * mod_exp(y, k, p)) % p;
    return C;
}

// Decrypt message
long long elgamal_decrypt(Cipher C, long long p, long long x) {
    long long s = mod_exp(C.c1, x, p);
    long long s_inv = mod_exp(s, p - 2, p); // Fermat’s theorem for modular inverse
    return (C.c2 * s_inv) % p;
}

// Product Cipher: combines two ciphertexts
Cipher productCipher(Cipher A, Cipher B, long long p) {
    Cipher P;
    P.c1 = (A.c1 * B.c1) % p;
    P.c2 = (A.c2 * B.c2) % p;
    return P;
}

int main() {
    long long p = 23;  // Prime modulus
    long long g = find_generator(p);  // Find primitive root

    if (g == -1) {
        cout << "No generator found.\n";
        return 0;
    }

    cout << "Prime (p): " << p << "\nGenerator (g): " << g << endl;

    long long x = 6;  // Private key
    long long y = mod_exp(g, x, p);  // Public key

    cout << "Public Key: (p=" << p << ", g=" << g << ", y=" << y << ")\n";
    cout << "Private Key: " << x << "\n";

    // Two messages
    long long m1 = 5, m2 = 7;
    long long k1 = 3, k2 = 4;

    Cipher C1 = elgamal_encrypt(m1, p, g, y, k1);
    Cipher C2 = elgamal_encrypt(m2, p, g, y, k2);

    cout << "\nCiphertext 1: (c1=" << C1.c1 << ", c2=" << C1.c2 << ")";
    cout << "\nCiphertext 2: (c1=" << C2.c1 << ", c2=" << C2.c2 << ")\n";

    // Product Cipher
    Cipher Cprod = productCipher(C1, C2, p);
    long long decryptedProd = elgamal_decrypt(Cprod, p, x);

    cout << "\n--- ElGamal Product Cipher ---\n";
    cout << "Combined Ciphertext: (c1=" << Cprod.c1 << ", c2=" << Cprod.c2 << ")\n";
    cout << "Decrypted Product Message: " << decryptedProd
         << " (Expected " << (m1 * m2) % p << ")\n";

    return 0;
}
