#pragma once

#include <cstdint>
#include <vector>

extern const int16_t FILENAME_END;
extern const int16_t ONE_MORE_FILE;
extern const int16_t ARCHIVE_END;

struct Cipher {
    Cipher(int16_t symbol1, const std::vector<bool>& word1);
    Cipher() = default;
    int16_t symbol = 0;
    std::vector<bool> word;
    Cipher& operator=(const Cipher& other);
};

void VectorInc(std::vector<bool>& vector);