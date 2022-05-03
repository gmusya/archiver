#pragma once

#include <map>
#include <vector>

#include "reader.h"
#include "util.h"

class Decoder {
public:
    Decoder() = default;
    void Decode(Reader& reader, bool& is_end, char* folder_name);
    struct SymbolInformation {
        size_t cnt;
        int16_t symbol;
    };

private:
    size_t alphabet_size_{};
    std::vector<Cipher> GetTable(Reader& reader);
    void GetSymbols(Reader& reader, std::vector<SymbolInformation>& res) const;
    std::vector<int16_t> GetSizes(Reader& reader) const;
};
