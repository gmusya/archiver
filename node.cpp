#include "node.h"

#include <random>

std::mt19937 rnd(0);

std::shared_ptr<Node> Node::Merge(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2) {
    if (!node1) {
        return node2;
    }
    if (!node2) {
        return node1;
    }
    if (node2->vertex->number < node1->vertex->number) {
        Swap(node1, node2);
    }
    if (rnd() & 1) {
        Swap(node1->left_kid, node1->right_kid);
    }
    node1->left_kid = Merge(node1->left_kid, node2);
    return node1;
}

Node::Node(std::shared_ptr<Vertex> vertex1) {
    vertex = std::move(vertex1);
    left_kid = nullptr;
    right_kid = nullptr;
}

void Node::Swap(std::shared_ptr<Node>& node1, std::shared_ptr<Node>& node2) {
    std::shared_ptr<Node> node3 = node1;
    node1 = node2;
    node2 = node3;
}
