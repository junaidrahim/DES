#include <iostream>
#include <string>
#include "src/round_key.h"
#include "src/DES.h"

int main() {
    std::string key = "1010101010111011000010010001100000100111001101101100110011011101";
    auto keys = RoundKey::generate_keys(key);

    std::string pt = "1010101111001101111001101010101111001101000100110010010100110110";
    std::cout << "Plain text: " << pt << std::endl;
    auto des = DES(keys);
    std::string ct = des.run(pt);
    std::cout << "Ciphertext: " << ct << std::endl;
} 