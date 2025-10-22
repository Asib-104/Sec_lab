#include <iostream>
#include <set>
using namespace std;

// Power function (a^b mod m)
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

// Function to find primitive root
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

struct Cipher {
    long long c1, c2;
};

// ElGamal encryption
Cipher elgamal_encrypt(long long m, long long p, long long g, long long y, long long k) {
    Cipher C;
    C.c1 = mod_exp(g, k, p);
    C.c2 = (m * mod_exp(y, k, p)) % p;
    return C;
}

// ElGamal decryption
long long elgamal_decrypt(Cipher C, long long p, long long x) {
    long long s = mod_exp(C.c1, x, p);
    long long s_inv = mod_exp(s, p - 2, p);
    return (C.c2 * s_inv) % p;
}

// Re-randomization: change ciphertext randomness (add new k')
Cipher rerandomize(Cipher C, long long p, long long g, long long y, long long k_prime) {
    Cipher R;
    long long r1 = mod_exp(g, k_prime, p); // g^k'
    long long r2 = mod_exp(y, k_prime, p); // y^k'
    R.c1 = (C.c1 * r1) % p;
    R.c2 = (C.c2 * r2) % p;
    return R;
}

int main() {
    long long p = 23;
    long long g = find_generator(p);

    if (g == -1) {
        cout << "No generator found.\n";
        return 0;
    }

    cout << "Prime (p): " << p << "\nGenerator (g): " << g << endl;

    long long x = 6;  // Private key
    long long y = mod_exp(g, x, p);  // Public key

    cout << "Public Key: (p=" << p << ", g=" << g << ", y=" << y << ")\n";
    cout << "Private Key: " << x << "\n";

    long long m = 9;
    long long k = 5;

    Cipher C = elgamal_encrypt(m, p, g, y, k);
    cout << "\nOriginal Ciphertext: (c1=" << C.c1 << ", c2=" << C.c2 << ")\n";

    long long k_prime = 7;
    Cipher R = rerandomize(C, p, g, y, k_prime);

    cout << "Re-randomized Ciphertext: (c1=" << R.c1 << ", c2=" << R.c2 << ")\n";

    long long dec1 = elgamal_decrypt(C, p, x);
    long long dec2 = elgamal_decrypt(R, p, x);

    cout << "\nDecrypted Original: " << dec1 << "\n";
    cout << "Decrypted Re-randomized: " << dec2 << "\n";

    return 0;
}
