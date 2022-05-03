#pragma once

#include <map>
#include <set>
#include <vector>

#include "util.h"
#include "vertex.h"

class Trie {
public:
    explicit Trie(const std::map<int16_t, size_t>& symbols_count);
    explicit Trie(std::vector<Cipher>& table);
    std::map<int16_t, size_t> FindWordLengths();
    std::pair<bool, int16_t> Get();
    void Move(bool right);

private:
    std::map<int16_t, size_t> table_;
    std::shared_ptr<Vertex> root_ = nullptr;
    std::shared_ptr<Vertex> current_ = nullptr;
    void Dfs(const std::shared_ptr<Vertex>& vertex, size_t word_length);
    void AddVertex(const std::shared_ptr<Vertex>& vertex, std::vector<bool>& code, size_t pos, int16_t symbol);
};
