#pragma once

#include <fstream>
#include <vector>

class Writer {
public:
    explicit Writer(std::ostream& os);
    ~Writer();
    void WriteBit(bool bit);
    void WriterBits(int16_t symbol, size_t number_of_bits);

private:
    std::vector<bool> current_byte_;
    size_t current_pos_;
    std::ostream& stream_;
    void WriteByte();
};
