#include <iostream>
#include <string>
#include <iomanip>

#include "src/round_key.h"
#include "src/DES.h"
#include "src/argh.h"

int main(int argc, char** argv) {
    std::string key = "1010101010111011000010010001100000100111001101101100110011011101";
    auto keys = RoundKey::generate_keys(key);

    std::string plain_text = "1010101111001101111001101010101111001101000100110010010100110110";
    std::cout << std::setw(25) << "Plain Text: " << plain_text << std::endl;

    auto des = DES(keys);
    std::string cipher_text = des.run(plain_text);
    std::cout << std::setw(25) << "Cipher Text: " << cipher_text << std::endl;

    des.reverse_keys();
    std::string decrypted_cipher_text = des.run(cipher_text);
    std::cout << std::setw(25) << "Decrypted Cipher Text: " << decrypted_cipher_text << std::endl;
}