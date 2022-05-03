#include "priority_queue.h"

void PriorityQueue::Pop() {
    root_ = Node::Merge(root_->left_kid, root_->right_kid);
}

std::shared_ptr<Vertex> PriorityQueue::Top() {
    return root_->vertex;
}

void PriorityQueue::Insert(const std::shared_ptr<Vertex>& vertex) {
    std::shared_ptr<Node> node = std::make_shared<Node>(vertex);
    root_ = Node::Merge(root_, node);
}

bool PriorityQueue::IsTrivial() {
    if (!root_) {
        return true;
    }
    return !(root_->left_kid || root_->right_kid);
}
