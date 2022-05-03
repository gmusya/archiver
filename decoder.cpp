#include "decoder.h"

#include <algorithm>
#include <dir.h>
#include <iostream>

#include "trie.h"
#include "writer.h"

std::vector<Cipher> MakeHuffmanCodeCanonical(std::vector<Decoder::SymbolInformation>& lengths_of_codes) {
    std::sort(lengths_of_codes.begin(), lengths_of_codes.end(), [](Decoder::SymbolInformation& lhs, Decoder::SymbolInformation& rhs) {
        if (lhs.cnt != rhs.cnt) {
            return lhs.cnt < rhs.cnt;
        }
        return lhs.symbol < rhs.symbol;
    });
    std::vector<bool> current_code(lengths_of_codes[0].cnt);
    std::vector<Cipher> result(lengths_of_codes.size());
    for (size_t i = 0; i < lengths_of_codes.size(); ++i) {
        result[i] = Cipher(lengths_of_codes[i].symbol, current_code);
        std::reverse(result[i].word.begin(), result[i].word.end());
        if (i + 1 < lengths_of_codes.size()) {
            VectorInc(current_code);
            for (size_t j = lengths_of_codes[i].cnt; j < lengths_of_codes[i + 1].cnt; ++j) {
                current_code.insert(current_code.begin(), false);
            }
        }
    }
    return result;
}

std::string GetFileName(Reader& reader, Trie& trie) {
    std::string file_name;
    while (true) {
        trie.Move(reader.ReadBit());
        std::pair<bool, int16_t> res = trie.Get();
        if (!res.first) {
            continue;
        }
        int16_t current_symbol = res.second;
        if (current_symbol == FILENAME_END) {
            return file_name;
        } else {
            file_name += static_cast<unsigned char>(current_symbol);
        }
    }
}

void Decoder::Decode(Reader& reader, bool& is_end, char* folder_name) {
    mkdir(folder_name);
    std::vector<Cipher> table = GetTable(reader);
    Trie trie(table);
    std::vector<bool> file;
    std::string file_name = GetFileName(reader, trie);
    bool is_it_last_file;
    std::cout << file_name << " decoding started" << std::endl;
    std::ofstream out(std::string(folder_name) + std::string("/") + file_name, std::ios::binary);
    if (out.fail()) {
        throw std::ios_base::failure(std::string("Cannot write to ") + std::string(folder_name) + std::string("/") +
                                     file_name);
    }
    Writer writer(out);
    while (true) {
        trie.Move(reader.ReadBit());
        std::pair<bool, int16_t> res = trie.Get();
        if (!res.first) {
            continue;
        }
        int16_t current_symbol = res.second;
        if (current_symbol == ONE_MORE_FILE || current_symbol == ARCHIVE_END) {
            is_it_last_file = (current_symbol == ARCHIVE_END);
            break;
        } else {
            writer.WriterBits(current_symbol, 8);
        }
    }
    is_end = is_it_last_file;
    std::cout << file_name << " decoding finished" << std::endl;
}

void Decoder::GetSymbols(Reader& reader, std::vector<SymbolInformation>& res) const {
    res.resize(alphabet_size_);
    for (size_t i = 0; i < alphabet_size_; ++i) {
        res[i].symbol = reader.ReadBits(9);
    }
}

std::vector<int16_t> Decoder::GetSizes(Reader& reader) const {
    std::vector<int16_t> res;
    size_t cur_size = 0;
    while (cur_size < alphabet_size_) {
        res.push_back(reader.ReadBits(9));
        cur_size += res.back();
    }
    return res;
}

std::vector<Cipher> Decoder::GetTable(Reader& reader) {
    alphabet_size_ = reader.ReadBits(9);
    std::vector<SymbolInformation> symbols_information;
    GetSymbols(reader, symbols_information);
    std::vector<int16_t> sizes = GetSizes(reader);
    size_t first = 0;
    for (size_t i = 0; i < alphabet_size_; ++i) {
        while (sizes[first] == 0) {
            ++first;
        }
        --sizes[first];
        symbols_information[i].cnt = first + 1;
    }
    return MakeHuffmanCodeCanonical(symbols_information);
}
