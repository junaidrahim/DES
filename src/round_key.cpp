#include "round_key.h"

#include <utility>
#include <array>

std::array<std::string, 16> RoundKey::generate_keys(const std::string &initial_key) {
    // PC1 Table
    constexpr std::array<uint64_t, 56> pc1 = {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4
    };

    // PC2 Table
    constexpr std::array<uint64_t, 48> pc2 = {
            14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32
    };

    std::string permutation_key;
    for (auto i: pc1) {
        permutation_key += initial_key[i - 1];
    }

    std::string left = permutation_key.substr(0, 28);
    std::string right = permutation_key.substr(28, 28);

    std::array<std::string, 16> result;

    // Generating 16 keys
    for (int i = 0; i < 16; i++) {
        // For rounds 1, 2, 9, 16 - shifted by one.
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            left = RoundKey::shift_left(left, 1);
            right = RoundKey::shift_left(right, 1);
        }
        else {
            left = RoundKey::shift_left(left, 2);
            right = RoundKey::shift_left(right, 2);
        }

        std::string combined_key = left + right;
        std::string round_key;

        // use PC2 table to transpose key bits
        for (int j = 0; j < 48; j++) {
            round_key += combined_key[pc2[j] - 1];
        }

        result[i] = round_key;
    }

    return result;
}

std::string RoundKey::shift_left(std::string bits, uint8_t shift_by) {
    std::string shifted;
    for (auto i = 0; i < shift_by; i++) {
        for (auto j = 1; j < bits.size(); j++) {
            shifted += bits[j];
        }

        shifted += bits[0];
        bits = shifted;
        shifted = "";
    }

    return bits;
}
