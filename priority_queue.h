#pragma once

#include <cstdint>
#include <ctime>
#include <random>

#include "node.h"

class PriorityQueue {
public:
    PriorityQueue() = default;
    void Pop();
    std::shared_ptr<Vertex> Top();
    void Insert(const std::shared_ptr<Vertex>& vertex);
    bool IsTrivial();

private:
    std::shared_ptr<Node> root_ = nullptr;
};
