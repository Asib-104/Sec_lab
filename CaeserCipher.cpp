#include <iostream>
#include <string>
using namespace std;

int main() {
    string plaintext = "HELLO";
    int shift = 3;
    string cipher = "", decrypted = "";

    for (char c : plaintext)
        cipher += char((c - 'A' + shift) % 26 + 'A');
    for (char c : cipher)
        decrypted += char((c - 'A' - shift + 26) % 26 + 'A');

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext: " << cipher << endl;
    cout << "Decrypted: " << decrypted << endl;
}
