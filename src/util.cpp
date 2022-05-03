#include "util.h"

const int16_t FILENAME_END = 256;
const int16_t ONE_MORE_FILE = 257;
const int16_t ARCHIVE_END = 258;

Cipher::Cipher(int16_t symbol1, const std::vector<bool>& word1) {
    symbol = symbol1;
    word = word1;
}

Cipher& Cipher::operator=(const Cipher& other) {
    if (this == &other) {
        return *this;
    }
    symbol = other.symbol;
    word = other.word;
    return *this;
}

void VectorInc(std::vector<bool>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i]) {
            vec[i] = false;
        } else {
            vec[i] = true;
            break;
        }
    }
}
