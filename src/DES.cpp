#include <iostream>
#include <string>
#include <cmath>
#include "DES.h"

DES::DES(const std::array<std::string, 16> &round_keys) {
    this->round_keys = round_keys;
}

std::string DES::decimal_to_binary(uint64_t decimal) {
    std::string binary;
    while(decimal != 0) {
        binary.insert(0, (decimal % 2 == 0 ? "0" : "1"));
        decimal = decimal/2;
    }

    while(binary.length() < 4){
        binary.insert(0, "0");
    }

    return binary;
}

uint64_t DES::binary_to_decimal(const std::string& binary) {
    return std::stoull(binary, nullptr, 2);
}

std::string DES::Xor(const std::string &a, const std::string &b) {
    std::string result;
    size_t size = b.size();

    for(int i = 0; i < size; i++){
        if(a[i] != b[i]){
            result += "1";
        }
        else{
            result += "0";
        }
    }
    return result;
}

std::string DES::run(const std::string& plain_text) {
    std::string perm;
    for(auto i: DES::initial_permutation){
        perm += plain_text[i-1];
    }

    std::string left = perm.substr(0, 32);
    std::string right = perm.substr(32, 32);

    for(int i=0; i<16; i++) {
        std::string right_expanded;
        // 3.1. The right half of the plain text is expanded
        for(int j = 0; j < 48; j++) {
            right_expanded += right[DES::expansion_table[j]-1];
        };  // 3.3. The result is xored with a key

        std::string xored = DES::Xor(round_keys[i], right_expanded);
        std::string res;

        // 3.4. The result is divided into 8 equal parts and passed
        // through 8 substitution boxes. After passing through a
        // substituion box, each box is reduces from 6 to 4 bits.
        for(int k=0;k<8; k++){
            // Finding row and column indices to lookup the
            // substituition box
            std::string row1= xored.substr(k*6,1) + xored.substr(k*6 + 5,1);
            auto row = DES::binary_to_decimal(row1);
            std::string col1 = xored.substr(k*6 + 1,1) + xored.substr(k*6 + 2,1) + xored.substr(k*6 + 3,1) + xored.substr(k*6 + 4,1);;
            auto col = DES::binary_to_decimal(col1);
            uint64_t val = DES::substitution_boxes[i][row][col];
            res += DES::decimal_to_binary(val);
        }
        // 3.5. Another permutation is applied
        std::string perm2;
        for(int l = 0; l < 32; l++){
            perm2 += res[permutation_tab[l]-1];
        }
        // 3.6. The result is xored with the left half
        xored = Xor(perm2, left);
        // 3.7. The left and the right parts of the plain text are swapped
        left = xored;
        if(i < 15){
            std::string temp = right;
            right = xored;
            left = temp;
        }
    }
    // 4. The halves of the plain text are applied
    std::string combined_text = left + right;
    std::string ciphertext;
    // The inverse of the initial permuttaion is applied
    for(int i = 0; i < 64; i++){
        ciphertext+= combined_text[inverse_permutation[i]-1];
    }
    //And we finally get the cipher text
    return ciphertext;
}
