#pragma once

#include <vector>

#include "reader.h"
#include "trie.h"
#include "writer.h"

class Encoder {
public:
    explicit Encoder(const std::string& file_name);
    void Encode(bool last, Writer& writer);

private:
    std::string file_name_;
    std::map<int16_t, size_t> cnt_;
    std::map<int16_t, std::vector<bool>> symbol_to_vector_;
    void CountSymbols();
    void CountSymbols(const std::string& file);
    static std::vector<int16_t> CountLengths(const std::vector<Cipher>& table);
    void AddFileName(Writer& writer);
    void AddFile(Writer& writer);
};
