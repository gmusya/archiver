#include "vertex.h"

Vertex::Vertex(int16_t symbol1, size_t number1) : symbol(symbol1), number(number1) {
}

Vertex::Vertex(const std::shared_ptr<Vertex>& left, const std::shared_ptr<Vertex>& right) {
    number = left->number + right->number;
    left_kid = left;
    right_kid = right;
}