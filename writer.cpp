#include "writer.h"

#include <iostream>
#include <climits>

Writer::Writer(std::ostream& os) : stream_(os) {
    current_pos_ = 0;
}

void Writer::WriteBit(bool bit) {
    if (current_pos_ == CHAR_BIT) {
        WriteByte();
        current_pos_ = 0;
    }
    current_byte_.push_back(bit);
    ++current_pos_;
}

Writer::~Writer() {
    while (current_pos_ < CHAR_BIT) {
        WriteBit(false);
    }
    WriteByte();
}

void Writer::WriteByte() {
    unsigned char current_char = 0;
    for (size_t i = 0; i < CHAR_BIT; ++i) {
        if (current_byte_[i]) {
            current_char += (1 << i);
        }
    }
    current_byte_.clear();
    stream_ << current_char;
}

void Writer::WriterBits(int16_t symbol, size_t number_of_bits) {
    for (size_t i = 0; i < number_of_bits; ++i) {
        WriteBit((symbol & 1) == 1);
        symbol >>= 1;
    }
}
