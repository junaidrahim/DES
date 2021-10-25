#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <bitset>
#include <vector>
#include <sstream>

#include "./src/argh.h"

#include "src/round_key.h"
#include "src/DES.h"
#include "src/argh.h"

std::vector<std::string> encrypt(const std::string& key, const std::string& plain_text) {
    auto keys = RoundKey::generate_keys(key);
    auto des = DES(keys);
    std::string encrypted_cipher_text = des.run(plain_text);

    std::vector<std::string> encrypted_bytes;

    for(int i = 0; i < plain_text.size(); i += 8) {
        std::cout << encrypted_cipher_text.substr(i, 8) << std::endl;
        encrypted_bytes.push_back(encrypted_cipher_text.substr(i, 8));
    }

    return encrypted_bytes;
}

std::vector<std::string> decrypt(const std::string& key, const std::string& encrypted_text) {
    auto keys = RoundKey::generate_keys(key);
    auto des = DES(keys);
    des.reverse_keys();
    std::string decrypted_cipher_text = des.run(encrypted_text);

    std::vector<std::string> decrypted_bytes;

    for(int i = 0; i < encrypted_text.size(); i += 8) {
        std::cout << decrypted_cipher_text.substr(i, 8) << std::endl;
        decrypted_bytes.push_back(decrypted_cipher_text.substr(i, 8));
    }

    return decrypted_bytes;
}

int main(int argc, char** argv) {
    std::string mode = "none";
    std::string in_file, out_file;

    argh::parser cmdl(argv);

    cmdl({"-f", "--file"}) >> in_file;
    cmdl({"-o", "--output"}) >> out_file;

    if(cmdl[{"-v", "--version"}]) {
        std::cout << "ver1.0" << std::endl;
        exit(0);
    }

    if (cmdl[{"-e", "--encrypt-mode"}]) {
        mode = "encrypt";
    }

    if (cmdl[{"-d", "--decrypt-mode"}]) {
        mode = "decrypt";
    }


    if(cmdl[{"-h", "--help"}]) {
        std::cout << "-v, --version        Display program version info and exit." << std::endl;
        std::cout << "-f, --file TEXT      Takes a file as an input." << std::endl;
        std::cout << "-o, --output TEXT    Writes the output to the specified file." << std::endl;
        std::cout << "-e, --encrypt-mode   Runs in encrypt mode." << std::endl;
        std::cout << "-d, --decrypt-mode   Runs in decrypt mode." << std::endl;
        std::cout << "--help, -h           show help" << std::endl;
        exit(0);
    }

    if(in_file == "" || out_file == "") {
        std::cout << "files not provided use -h or --help for more info" << std::endl;
        exit(0);
    }

    std::string key{"0111000101110111011001010111001001110100011110010111010101101001"}, input_string;


    std::ifstream fin;
    std::ofstream fout;

    std::tuple<std::string, std::string> result;

    fin.open(in_file);
    fout.open(out_file);

    if(fin) {
        std::ostringstream ss;
        ss << fin.rdbuf();
        input_string = ss.str();
    }

    std::vector<std::bitset<8>> bit_set_vec;
    for(std::size_t i = 0; i < input_string.size(); i++) {
        bit_set_vec.push_back(std::bitset<8>(input_string.c_str()[i]));
    }

    if(bit_set_vec.size() % 8) {
        int padding = 8 - bit_set_vec.size() % 8;
        for (int i = 0; i < padding; i++) {
            bit_set_vec.push_back(std::bitset<8>());
        }
    }

    if (mode == "encrypt") {
        std::string plaintext_buffered;
        std::vector<std::string> encrypted_bytes;

        for(int i = 0; i < bit_set_vec.size(); i++) {
            plaintext_buffered = plaintext_buffered + bit_set_vec[i].to_string();

            if(plaintext_buffered.size() == 64) {
                std::cout << plaintext_buffered << "sent to cipher" << std::endl;
                encrypted_bytes = encrypt(key, plaintext_buffered);
                for(int j = 0; j < encrypted_bytes.size(); j++) {
                    std::bitset<8> enc_char(encrypted_bytes[j]);
                    unsigned long x = enc_char.to_ulong();
                    unsigned char c =  static_cast<unsigned char>(x);
                    fout << c;
                }

                plaintext_buffered = "";
            }
        }
    } else if (mode == "decrypt") {
        std::string encrypted_text_buffered;
        std::vector<std::string> decrypted_bytes;

        for(int i = 0; i < bit_set_vec.size(); i++) {
            encrypted_text_buffered = encrypted_text_buffered + bit_set_vec[i].to_string();

            if(encrypted_text_buffered.size() == 64) {
                std::cout << encrypted_text_buffered << "sent to cipher" << std::endl;
                decrypted_bytes = decrypt(key, encrypted_text_buffered);
                for(int j = 0; j < decrypted_bytes.size(); j++) {
                    std::bitset<8> enc_char(decrypted_bytes[j]);
                    unsigned long x = enc_char.to_ulong();
                    unsigned char c =  static_cast<unsigned char>(x);
                    fout << c;
                }

                encrypted_text_buffered = "";
            }
        }
    } else {
        std::cout << "No mode selected. Checkout --help to get more info" << std::endl;
    }

    fout << std::endl;

    fout.close();
    fin.close();
}