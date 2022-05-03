#include "reader.h"
#include <climits>
#include <iostream>

Reader::Reader(std::istream& input_stream) : stream_(input_stream) {
    current_pos_ = CHAR_BIT;
}

bool Reader::ReadBit() {
    if (current_pos_ == CHAR_BIT) {
        ReadByte();
        current_pos_ = 0;
    }
    return current_byte_[current_pos_++];
}

int16_t Reader::ReadBits(size_t number_of_bits) {
    int16_t res = 0;
    for (size_t i = 0; i < number_of_bits; ++i) {
        if (ReadBit()) {
            res += (1 << i);
        }
    }
    return res;
}

void Reader::ReadByte() {
    if (Ended()) {
        throw std::ios_base::failure("Reading after end of file");
    }
    unsigned char current_char = stream_.get();
    current_byte_ = std::vector<bool>();
    for (size_t i = 0; i < CHAR_BIT; ++i) {
        current_byte_.push_back((current_char & 1) == 1);
        current_char >>= 1;
    }
}

bool Reader::Ended() {
    return stream_.eof();
}
