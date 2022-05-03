#pragma once

#include <cstdint>
#include <memory>

class Vertex {
public:
    Vertex(int16_t symbol1, size_t number1);
    Vertex() = default;
    Vertex(const std::shared_ptr<Vertex>& left, const std::shared_ptr<Vertex>& right);
    int16_t symbol = 0;
    size_t number = 0;
    std::shared_ptr<Vertex> left_kid = nullptr;
    std::shared_ptr<Vertex> right_kid = nullptr;
};
