#include <iostream>
#include <string>
using namespace std;

int main() {
    string plaintext = "HELLO";
    string key = "XMCKL";
    string cipher = "", decrypted = "";

    for (int i = 0; i < plaintext.size(); i++)
        cipher += (plaintext[i] ^ key[i]);
    for (int i = 0; i < plaintext.size(); i++)
        decrypted += (cipher[i] ^ key[i]);

    cout << "Plaintext: " << plaintext << endl;
    cout << "Ciphertext (XOR values): ";
    for (char c : cipher) cout << int(c) << " ";
    cout << "\nDecrypted: " << decrypted << endl;
}
