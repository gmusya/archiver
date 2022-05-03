#pragma once

#include <istream>
#include <string>
#include <string_view>
#include <vector>

class Reader {
public:
    explicit Reader(std::istream& input_stream);
    bool Ended();
    bool ReadBit();
    int16_t ReadBits(size_t number_of_bits);

private:
    std::istream& stream_;
    std::vector<bool> current_byte_;
    size_t current_pos_;
    void ReadByte();
};
