#pragma once

#include <cstdint>

#include "vertex.h"

class Node {
public:
    explicit Node(std::shared_ptr<Vertex> vertex);
    static std::shared_ptr<Node> Merge(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);
    std::shared_ptr<Vertex> vertex;
    std::shared_ptr<Node> left_kid = nullptr;
    std::shared_ptr<Node> right_kid = nullptr;

private:
    static void Swap(std::shared_ptr<Node>& node1, std::shared_ptr<Node>& node2);
};
