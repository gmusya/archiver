#include "encoder.h"

#include <algorithm>
#include <fstream>

namespace {
    void AddAlphabetSizeToAnswer(int16_t alphabet_size, Writer& writer) {
        writer.WriterBits(alphabet_size, 9);
    }

    void AddSymbolToAnswer(int16_t symbol, Writer& writer) {
        writer.WriterBits(symbol, 9);
    }

    void AddVectorToAnswer(const std::vector<bool>& word, Writer& writer) {
        for (bool bit : word) {
            writer.WriteBit(bit);
        }
    }

    void AddLengthsToAnswer(const std::vector<int16_t>& cnt, Writer& writer) {
        for (size_t x = 1; x < cnt.size(); ++x) {
            AddSymbolToAnswer(cnt[x], writer);
        }
    }
}// namespace


std::vector<Cipher> MakeHuffmanCodeCanonical(const std::map<int16_t, size_t>& table) {
    if (table.empty()) {
        return {};
    }
    std::vector<std::pair<size_t, int16_t>> lengths_of_codes;
    lengths_of_codes.reserve(table.size());
    for (auto& now : table) {
        lengths_of_codes.emplace_back(now.second, now.first);
    }
    std::sort(lengths_of_codes.begin(), lengths_of_codes.end());
    std::vector<bool> current_code(lengths_of_codes[0].first);
    std::vector<Cipher> result(lengths_of_codes.size());
    for (size_t i = 0; i < lengths_of_codes.size(); ++i) {
        result[i] = Cipher(lengths_of_codes[i].second, current_code);
        std::reverse(result[i].word.begin(), result[i].word.end());
        if (i + 1 < lengths_of_codes.size()) {
            VectorInc(current_code);
            for (size_t j = lengths_of_codes[i].first; j < lengths_of_codes[i + 1].first; ++j) {
                current_code.insert(current_code.begin(), false);
            }
        }
    }
    return result;
}

void Encoder::AddFileName(Writer& writer) {
    for (int16_t symbol : file_name_) {
        AddVectorToAnswer(symbol_to_vector_[symbol], writer);
    }
}

void Encoder::AddFile(Writer& writer) {
    std::ifstream in(file_name_, std::ios::binary);
    Reader reader(in);
    int16_t symbol;
    while (!reader.Ended()) {
        symbol = reader.ReadBits(8);
        if (reader.Ended()) {
            break;
        }
        AddVectorToAnswer(symbol_to_vector_[symbol], writer);
    }
}

std::vector<int16_t> Encoder::CountLengths(const std::vector<Cipher>& table) {
    std::vector<int16_t> cnt(table.size() + 1);
    for (auto& now : table) {
        ++cnt[now.word.size()];
    }
    while (!cnt.back()) {
        cnt.pop_back();
    }
    return cnt;
}

void Encoder::Encode(bool last, Writer& writer) {
    CountSymbols();
    CountSymbols(file_name_);
    Trie trie(cnt_);
    std::vector<Cipher> table = MakeHuffmanCodeCanonical(trie.FindWordLengths());
    for (auto& now : table) {
        symbol_to_vector_[now.symbol] = now.word;
    }
    AddAlphabetSizeToAnswer(static_cast<int16_t>(table.size()), writer);
    for (auto& now : table) {
        AddSymbolToAnswer(now.symbol, writer);
    }
    std::vector<int16_t> cnt = CountLengths(table);
    AddLengthsToAnswer(cnt, writer);
    AddFileName(writer);
    AddVectorToAnswer(symbol_to_vector_[FILENAME_END], writer);
    AddFile(writer);
    AddVectorToAnswer(symbol_to_vector_[last ? ARCHIVE_END : ONE_MORE_FILE], writer);
}

void Encoder::CountSymbols() {
    std::ifstream in(file_name_, std::ios::binary);
    Reader reader(in);
    int16_t symbol;
    while (!reader.Ended()) {
        symbol = reader.ReadBits(8);
        if (reader.Ended()) {
            break;
        }
        ++cnt_[symbol];
    }
}

void Encoder::CountSymbols(const std::string& file) {
    for (unsigned char symbol : file) {
        ++cnt_[static_cast<int16_t>(symbol)];
    }
}

Encoder::Encoder(const std::string& file_name) {
    file_name_ = file_name;
    cnt_[FILENAME_END] = 1;
    cnt_[ONE_MORE_FILE] = 1;
    cnt_[ARCHIVE_END] = 1;
}
