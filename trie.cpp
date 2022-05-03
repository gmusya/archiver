#include "trie.h"

#include "priority_queue.h"

std::map<int16_t, size_t> Trie::FindWordLengths() {
    size_t word_length = 0;
    Dfs(root_, word_length);
    return table_;
}

void Trie::Dfs(const std::shared_ptr<Vertex>& vertex, size_t word_length) {
    if (!vertex->left_kid) {
        table_[vertex->symbol] = word_length;
    } else {
        Dfs(vertex->left_kid, word_length + 1);
        Dfs(vertex->right_kid, word_length + 1);
    }
}

Trie::Trie(const std::map<int16_t, size_t>& symbols_count) {
    PriorityQueue vertices_to_merge;
    for (auto& now : symbols_count) {
        vertices_to_merge.Insert(std::make_shared<Vertex>(now.first, now.second));
    }
    while (!vertices_to_merge.IsTrivial()) {
        auto left = vertices_to_merge.Top();
        vertices_to_merge.Pop();
        auto right = vertices_to_merge.Top();
        vertices_to_merge.Pop();
        vertices_to_merge.Insert(std::make_shared<Vertex>(left, right));
    }
    root_ = vertices_to_merge.Top();
}

void Trie::AddVertex(const std::shared_ptr<Vertex>& vertex, std::vector<bool>& code, size_t pos, int16_t symbol) {
    if (pos == code.size()) {
        vertex->symbol = symbol;
        vertex->number = 1;
    } else if (!code[pos]) {
        if (!vertex->left_kid) {
            vertex->left_kid = std::make_shared<Vertex>();
        }
        AddVertex(vertex->left_kid, code, pos + 1, symbol);
    } else {
        if (!vertex->right_kid) {
            vertex->right_kid = std::make_shared<Vertex>();
        }
        AddVertex(vertex->right_kid, code, pos + 1, symbol);
    }
}

Trie::Trie(std::vector<Cipher>& table) {
    root_ = std::make_shared<Vertex>();
    for (auto& now : table) {
        AddVertex(root_, now.word, 0, now.symbol);
    }
    current_ = root_;
}

std::pair<bool, int16_t> Trie::Get() {
    if (!current_ || !current_->number) {
        return std::make_pair(false, 0);
    } else {
        return std::make_pair(true, current_->symbol);
    }
}

void Trie::Move(bool right) {
    if (current_->number) {
        current_ = root_;
    }
    if (right) {
        current_ = current_->right_kid;
    } else {
        current_ = current_->left_kid;
    }
    if (!current_) {
        throw std::runtime_error("Current vertex in trie is nullptr");
    }
}
