#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <vector>
#include <sstream>

#include "CLI11.hpp"

#include "src/round_key.h"
#include "src/DES.h"
#include "src/argh.h"

// std::tuple <std::string, std::string> cipher_decipher(std::string*, std::string*);

std::vector<std::string> cipher_decipher(const std::string& key, const std::string& plaintext) {
    auto keys = RoundKey::generate_keys(key);

    auto des = DES(keys);
    std::string cipher_text = des.run(plaintext);
    // std::cout << std::setw(25) << "Cipher Text : " << cipher_text << std::endl;

    des.reverse_keys();
    std::string decrypted_cipher_text = des.run(cipher_text);
    // std::cout << std::setw(25) << "Decrypted Cipher Text : " << decrypted_cipher_text << std::endl;

    std::vector<std::string> encrypted_bytes;

    // std::cout << plaintext.size() << std::endl;

    for(int i = 0; i < plaintext.size(); i += 8) {
        std::cout << cipher_text.substr(i, 8) << std::endl;
        encrypted_bytes.push_back(cipher_text.substr(i, 8));
    }

    std::cout << std::endl;

    return encrypted_bytes;
}

int main(int argc, char** argv) {

    CLI::App app("DES");
    app.set_version_flag("-v,--version", std::string("1.0"));
    app.set_help_flag("-h,--help", std::string("displays this info"));
    std::string in_file, out_file;
    CLI::Option *inf = app.add_option("-f,--file", in_file, "inputfile");
    CLI::Option *outf = app.add_option("-o,--output", out_file, "outputfile");
    CLI11_PARSE(app, argc, argv);

    if(in_file == "" || out_file == "") {
        std::cout << "files not provided use -h or --help for more info" << std::endl;
        exit(0);
    }

    std::string key{"0111000101110111011001010111001001110100011110010111010101101001"}, plaintext;

    std::vector<std::bitset<8>> bit_set_vec;

    std::ifstream fin;
    std::ofstream fout;
    
    std::tuple <std::string, std::string> res;
    
    fin.open(in_file);
    fout.open(out_file);
    
    if(fin) {
        // getline(fin, plaintext);
        std::ostringstream ss;
        ss << fin.rdbuf();
        plaintext = ss.str();
    }

    for(std::size_t i = 0; i < plaintext.size(); i++) {
        bit_set_vec.push_back(std::bitset<8>(plaintext.c_str()[i]));
    }
    if(bit_set_vec.size() % 8) {
        int padding = 8 - bit_set_vec.size() % 8;
        for (int i = 0; i < padding; i++) {
            bit_set_vec.push_back(std::bitset<8>());
        }
    }
    std::string plaintext_buffered{""};
    std::vector<std::string> encrypted_bytes;
    for(int i = 0; i < bit_set_vec.size(); i++) {
        plaintext_buffered = plaintext_buffered + bit_set_vec[i].to_string();
        // std::cout << plaintext_buffered.size() << std::endl;

        if(plaintext_buffered.size() == 64) {
            std::cout << plaintext_buffered << "sent to cipher" << std::endl;
            encrypted_bytes = cipher_decipher(key, plaintext_buffered);
            for(int i = 0; i < encrypted_bytes.size(); i++) {
                std::bitset<8> enc_char(encrypted_bytes[i]);
                unsigned long x = enc_char.to_ulong();
                unsigned char c =  static_cast<unsigned char>(x);
                fout << c;
            }
            plaintext_buffered = "";
        }
    }
    fout << std::endl;

    // std::cout << "using key : " << key << " on plain text : " << plaintext << std::endl;
    // fout << "using key : " << key << " on plain text : " << plaintext << std::endl;
    // res = cipher_decipher(key, plaintext_buffered);
    // fout << "Cipher text: " << std::get<0>(res) << "\nDeciphered text: " << std::get<1>(res) << std::endl << std::endl;

    fout.close();
    fin.close();
}