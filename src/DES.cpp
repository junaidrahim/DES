#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

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
    int decimal = 0;
    int counter = 0;
    int size = binary.length();
    for(int i = size-1; i >= 0; i--)
    {
        if(binary[i] == '1'){
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
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
        for(int j = 0; j < 48; j++) {
            right_expanded += right[DES::expansion_table[j]-1];
        };

        std::string xored = DES::Xor(DES::round_keys[i], right_expanded);
        std::string res;

        for(int k=0;k<8; k++){
            std::string row1= xored.substr(k*6,1) + xored.substr(k*6 + 5,1);
            auto row = DES::binary_to_decimal(row1);
            std::string col1 = xored.substr(k*6 + 1,1) + xored.substr(k*6 + 2,1) + xored.substr(k*6 + 3,1) + xored.substr(k*6 + 4,1);;
            auto col = DES::binary_to_decimal(col1);
            uint64_t val = DES::substitution_boxes[k][row][col];
            res += DES::decimal_to_binary(val);
        }

        std::string perm2;
        for(int l = 0; l < 32; l++){
            perm2 += res[permutation_tab[l]-1];
        }

        xored = Xor(perm2, left);
        left = xored;

        if(i < 15){
            std::string temp = right;
            right = xored;
            left = temp;
        }
    }

    std::string combined_text = left + right;
    std::string ciphertext;

    for(int i = 0; i < 64; i++){
        ciphertext+= combined_text[inverse_permutation[i]-1];
    }

    return ciphertext;
}

void DES::reverse_keys() {
    std::reverse(this->round_keys.begin(), this->round_keys.end());
}
