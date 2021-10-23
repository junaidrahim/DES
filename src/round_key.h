#ifndef DES_ROUND_KEY_H
#define DES_ROUND_KEY_H

#include <string>
#include <array>


namespace RoundKey {
    std::array<std::string, 16> generate_keys(const std::string& initial_key);
    std::string shift_left(std::string bits, uint8_t shift_by);
};


#endif //DES_ROUND_KEY_H
