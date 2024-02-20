#ifndef CRYPT
#define CRYPT

#include <string>
using namespace std;

//Function to encrypt or decrypt a string using a key value
string cryption(string text, int key) {
    string out = "";

    //Loop through each character in the string
    for (int i = 0; i < text.length(); i++) {
        //Apply the key to the character based on whether encrypting or decrypting
        if (text[i] >= 'a' && text[i] <= 'z') {
            out += (char)('a' + ((text[i] - 'a' + key%26 + 26) % 26));
        }
        else if (text[i] >= 'A' && text[i] <= 'Z') {
            out += (char)('A' + ((text[i] - 'A' + key%26 + 26) % 26));
        }
        else out += text[i];
    }

    return out;
}

#endif //crypt